#pragma once
#include <vector>
#include "map.h"

class SceneBuilder
{
public:
	SceneBuilder();
	~SceneBuilder();
	void Build();
private:
	Map map_;
};

