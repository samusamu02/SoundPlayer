#pragma once
#include <type_traits>
//�{�^���̎��
enum class InputID
{
	Non,
	Up,
	Down,
	Right,
	Space,
	Max
};

static InputID begin(InputID){ return InputID::Up; }; 
static InputID end(InputID) { return InputID::Max; };
static InputID operator++(InputID& state) {
	return (state = static_cast<InputID>(std::underlying_type<InputID>::type(state) + 1));
};
static InputID operator*(const InputID& state) { return state; };
