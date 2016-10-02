#pragma once
struct Map
{
	Map()
	{
		map = nullptr;
		width = 0;
		height = 0;
	}

	int* & operator[](int el) { return map[el]; }

	int** map;
	int width;
	int height;
};