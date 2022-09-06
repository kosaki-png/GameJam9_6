#pragma once

#include "CollisionPrimitive.h"

/// <summary>
/// 当たり判定ヘルパークラス
/// </summary>
class Collision
{
private:
	
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	/// <summary>
	/// 点と三角形の最近接点を求める
	/// </summary>
	/// <param name="point">点</param>
	/// <param name="triangle">三角形</param>
	/// <param name="closest">最近接点（出力用）</param>
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest);

	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphereA">球A</param>
	/// <param name="sphereB">球B</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns></returns>
	static bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR*inter = nullptr);

	/// <summary>
	/// 球と平面の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">交点（平面上の最近接点）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR*inter = nullptr);

	/// <summary>
	/// 球と法線付き三角形の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="triangle">三角形</param>
	/// <param name="inter">交点（三角形上の最近接点）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	/// レイと平面の当たり判定
	/// </summary>
	/// <param name="lay">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Plane(const Ray& lay, const Plane& plane, float*distance = nullptr, DirectX::XMVECTOR*inter = nullptr);

	/// <summary>
	/// レイと法線付き三角形の当たり判定
	/// </summary>
	/// <param name="lay">レイ</param>
	/// <param name="triangle">三角形</param>
	/// <param name="inter">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Triangle(const Ray& lay, const Triangle& triangle, float*distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	/// <summary>
	/// レイと球の当たり判定
	/// </summary>
	/// <param name="lay">レイ</param>
	/// <param name="sphere">球</param>
	/// <param name="sphere">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	static bool CheckRay2Sphere(const Ray& lay, const Sphere& sphere, float*distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	///<summary>
		/// 矩形当たり判定2D
		///</summary>
		///<param name="OBJ1Pos">一つ目のオブジェクトの位置</param>
		///<param name="OBJ2Pos">二つ目のオブジェクトの位置</param>
		///<param name="OBJ1size">一つ目のオブジェクトの大きさ</param>
		///<param name="OBJ2size">二つ目のオブジェクトの大きさ</param>
		///<returns>交差しているのか否か</returns>
	static bool CheckBox2D(const XMFLOAT2& OBJ1Pos, const XMFLOAT2& OBJ2Pos, const XMFLOAT2& OBJ1size, const XMFLOAT2& OBJ2size);

	///<summary>
	/// 矩形当たり判定3D
	///</summary>
	///<param name="OBJ1Pos">一つ目のオブジェクトの位置</param>
	///<param name="OBJ2Pos">二つ目のオブジェクトの位置</param>
	///<param name="OBJ1size">一つ目のオブジェクトの大きさ</param>
	///<param name="OBJ2size">二つ目のオブジェクトの大きさ</param>
	///<returns>交差しているのか否か</returns>
	static bool CheckBox3D(const XMFLOAT3& OBJ1Pos, const XMFLOAT3& OBJ2Pos, const XMFLOAT3& OBJ1size, const XMFLOAT3& OBJ2size);

	///<summary>
	/// 矩形当たり判定2D(サイズ変更可能)
	///</summary>
	///<param name="OBJ1Pos">一つ目のオブジェクトの位置</param>
	///<param name="OBJ2Pos">二つ目のオブジェクトの位置</param>
	///<param name="OBJ1size">一つ目のオブジェクトの大きさ</param>
	///<param name="OBJ2size">二つ目のオブジェクトの大きさ</param>
	///<param name="OBJ1colsize">一つ目のオブジェクトの当たり判定の大きさ</param>
	///<param name="OBJ2colsize">二つ目のオブジェクトの当たり判定の大きさ</param>
	///<returns>交差しているのか否か</returns>
	static bool CheckBox2D(const XMFLOAT2& OBJ1Pos, const XMFLOAT2& OBJ2Pos, const XMFLOAT2& OBJ1size, const XMFLOAT2& OBJ2size, const float OBJ1colsize, const float OBJ2colsize);

	//ほぼCheckBox2Dと変わらない
	///<summary>
	///短形同士の当たり判定(2D)
	///</summary>
	///<param name="Rect">短形</param>
	static bool IsCollidingDistance(Rect rect_a, Rect rect_b);
};