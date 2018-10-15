#pragma once

#include <cstdint>

struct Position
{
	int32_t X;
	int32_t Y;
};

struct Size
{
	int32_t Height;
	int32_t Width;
};


enum class Facing
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

