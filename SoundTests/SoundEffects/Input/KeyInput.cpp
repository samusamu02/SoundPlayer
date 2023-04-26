#include <DxLib.h>
#include "KeyInput.h"

KeyInput::KeyInput()
{
	inputTbl_ = 
	{
		{InputID::Up,KEY_INPUT_UP},
		{InputID::Down,KEY_INPUT_DOWN},
		{InputID::Right,KEY_INPUT_RIGHT},
		{InputID::Space,KEY_INPUT_SPACE}
	};

	for (auto id : InputID())
	{

		cntData_.try_emplace(id, TrgBool{ 0,0 });
	}
	ringBuf_ =ringBuf_->Create(10);
	startBuf_ = ringBuf_;
}

KeyInput::~KeyInput()
{
}

void KeyInput::Update(void)
{
	GetHitKeyStateAll(keyData_.data());

	for (auto id : InputID())
	{
		cntData_[id][static_cast<int>(Trg::Old)] = cntData_[id][static_cast<int>(Trg::Now)];
		cntData_[id][static_cast<int>(Trg::Now)] = keyData_[inputTbl_[id]];
	}
}
