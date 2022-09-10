#pragma once
#include "Camera.h"
#include "Input.h"
#include "Audio.h"
#include "Sprite.h"
#include <array>

class OptionGS
{
public:
	OptionGS(Input* input, Camera* camera, Audio* audio);
	~OptionGS();

	void Initialize();
	void Update();
	void Draw();

	void ChangeIsOption();
	bool GetIsOption() { return isOption; }

private:
	Input* input = nullptr;
	Camera* camera = nullptr;
	Audio* audio = nullptr;

	// �ݒ�pUI
	Sprite* option_base = nullptr;
	std::array<Sprite*, 3> option_bar = { nullptr, nullptr, nullptr };
	std::array<float, 3> bar_ratio = { 0,0,0 };

	// �I�v�V��������
	bool isOption = false;

	// �ݒ荀��
	float fov = 0;
	float sensi = 0;

	// �w��p
	DirectX::XMFLOAT2 mousePos;

};

