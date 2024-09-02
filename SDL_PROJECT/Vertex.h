#pragma once

struct Position
{
	float x, y;
};

struct Color
{
	unsigned char r, g, b, a;
};

struct Vertex
{
	Position position;
	Color color;
};