#pragma once

//	使用キー
enum class UseKey
{
	K_NON,
	K_LEFT,
	K_RIGHT,
	K_UP,
	K_DOWN,
	K_SPACE,
	K_ENTER,
	K_A,
	K_S,
	K_MAX
};

UseKey begin(UseKey);
UseKey end(UseKey);
UseKey operator*(UseKey key);
UseKey operator++(UseKey& key);


