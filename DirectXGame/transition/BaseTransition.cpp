#include "BaseTransition.h"

BaseTransition::BaseTransition()
{
}

BaseTransition::~BaseTransition()
{
}

void BaseTransition::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon = dxCommon;
	this->input = input;
}

void BaseTransition::Update()
{
}

void BaseTransition::Draw()
{
}

void BaseTransition::Start()
{
}
