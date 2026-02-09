#pragma once

enum CollisionBits
{
	PLAYER = 1u << 0,
	ZOMBIE = 1u << 1,
	BULLET = 1u << 2,
	ITEM = 1u << 3,
	WALL = 1u << 4
};
