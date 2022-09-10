#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

static const float PI = 3.141592654f;	// π
static float3 N;

// Schlickによる近似
// f0とf90の値を(1 - cosine)の５乗でlerpする
// f0 : 光が垂直に入射したときの反射率
// f90 : 光が平行に入射したときの反射率
// cosine : ２ベクトルのなす角のコサイン
float SchlickFresnel(float f0, float f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}

float3 SchlickFresnel3(float3 f0, float3 f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}

// ディズニーのフレネル計算
float3 DisneyFresnel(float LdotH, float3 baseColor)
{
	// F項
	// 輝度
	float luminance = 0.3f * baseColor.r + 0.6f * baseColor.g + 0.1f * baseColor.b;
	// 色合い
	float3 tintColor = baseColor / luminance;
	// 非金属の鏡面反射色を計算
	float3 nonMetalColor = 0.5 * 0.08f * tintColor;
	// metalnessによる色補間　金属の場合はベースカラー
	float3 specularColor = lerp(nonMetalColor, baseColor, 0.5);
	// NdotHの割合でSchlickFresnel補間
	return SchlickFresnel3(specularColor, float3(1, 1, 1), LdotH);
}

// UE4のGGX分布
// alpha : roughnessの２乗
// NdotH : 法線とハーフベクトルの内積
float DistributionGGx(float alpha, float NdotH)
{
	float alpha2 = alpha * alpha;
	float t = NdotH * NdotH * (alpha2 - 1.0f) + 1.0f;
	return alpha2 / (PI * t * t);
}

// UE4のSmithモデル
float GeometricSmith(float cosine)
{
	float k = (0 + 1.0f);

	k = k * k / 8.0f;

	return cosine / (cosine * (1.0f - k) + k);
}

// 描画反射の計算
float3 CookTorranceSpecular(float NdotL, float NdotV, float NdotH, float LdotH, float3 baseColor)
{
	// D項(分布：Distribution)
	float Ds = DistributionGGx(0.5 * 0.5, NdotH);

	// F項(フレネル：Fresnel)
	float3 Fs = DisneyFresnel(LdotH, baseColor);

	// G項(幾何減衰：Geometry attenuation)
	//float Gs = 1.0f;
	float Gs = GeometricSmith(NdotL) * GeometricSmith(NdotV);

	// m項(分母)
	float m = 4.0f * NdotL * NdotV;

	// 合成して鏡面反射の色を得る
	return Ds * Fs * Gs / m;
}

// 双方向反射分布関数
float3 BRDF(float3 L, float3 V, float3 baseColor)
{
	L = normalize(L);

	// 法線とライトの内積
	float NdotL = dot(N, L);
	// 法線とカメラ方向の内積
	float NdotV = dot(N, V);
	// どちらかが90度以上であれば
	//if (NdotV < 0 || NdotL < -0) { return float3(0, 0, 0); }

	/*if (NdotL < 0) { return (baseColor - baseColor * abs(NdotL)) * 0.05; }*/
	if (NdotV < 0 || NdotL < -0) { return (1.0 - smoothstep(0, -0.2, NdotL) * baseColor) * 0.1; }

	// ライト方向とカメラ方向の中間
	float3 H = normalize(L + V);
	// 法線とハーフベクトルの内積
	float NdotH = dot(N, H);
	// ライトとハーフベクトルの内積
	float LdotH = dot(L, H);

	// 拡散反射率
	float diffuseReflectance = 1.0f / PI;

	// 入射角が90度の場合の拡散反射率
	float energyBias = 0.5f * 0.5;
	float Fd90 = energyBias + 2 * LdotH * LdotH * 0.5;
	// 入っていく時の拡散反射率
	float FL = SchlickFresnel(1.0f, Fd90, NdotL);
	// 出ていく時の拡散反射率
	float FV = SchlickFresnel(1.0f, Fd90, NdotV);
	// 入って出ていくまでの拡散反射率
	float energyFactor = lerp(1.0f, 1.0f / 1.51f, 0.5);
	float Fd = FL * FV * energyFactor;

	// 拡散反射項
	float3 diffuseColor = diffuseReflectance * Fd * baseColor * (1 - 0.5);

	// 鏡面反射項
	float3 specularColor = CookTorranceSpecular(NdotL, NdotV, NdotH, LdotH, baseColor);

	return diffuseColor + specularColor;
}

float4 Diffuse(float3 normal, float3 lightPos, float3 baseColor)
{
	return max(0, dot(normalize(normal), normalize(lightPos))) * float4(baseColor, 1);
}

float4 main(VSOutput input) : SV_TARGET
{
	// テクスチャマッピング
	//float4 texcolor = tex.Sample(smp, input.uv);
		
	//// 光沢度
	//const float shininess = 4.0f;
	//// 頂点から視点への方向ベクトル
	//float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	//// 環境反射光
	//float3 ambient = m_ambient;

	//// シェーディングによる色
	//float4 shadecolor = float4(ambientColor * ambient, m_alpha);

	//for (int i = 0; i < DIRLIGHT_NUM; i++) {
	//	if (dirLights[i].active) {
	//		// ライトに向かうベクトルと法線の内積
	//		float3 dotlightnormal = dot(dirLights[i].lightv, input.normal);
	//		// 反射光ベクトル
	//		float3 reflect = normalize(-dirLights[i].lightv + 2 * dotlightnormal * input.normal);
	//		// 拡散反射光
	//		float3 diffuse = dotlightnormal * m_diffuse;
	//		// 鏡面反射光
	//		float3 specular = pow(saturate(dot(reflect, eyedir)), shininess) * m_specular;

	//		// 全て加算する
	//		shadecolor.rgb += (diffuse + specular) * dirLights[i].lightcolor;
	//	}
	//}

	//// シェーディングによる色で描画
	//return shadecolor/* * texcolor*/;

	// 面の情報をstatic変数に代入し、関数から参照できるようにする
	N = input.normal;
	// 最終的なRGB
	float4 finalRGB = float4(0, 0, 0, 0);
	// 頂点から視点への方向ベクトル
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);
	float3 lightdirMain = (float3(-5, 10, -10) - input.worldpos.xyz);
	float4 baseColor = tex.Sample(smp, input.uv);

	// diffuseを計算しBRDFの結果とライト色を合成
	// メインライト
	float4 diffuseColor = Diffuse(input.normal, float3(-5, 10, -10), baseColor.xyz);
	finalRGB += (float4(BRDF(lightdirMain, eyedir, baseColor.xyz), 1));


	return float4(finalRGB.xyz, 1.0) + baseColor * 0.7;
}