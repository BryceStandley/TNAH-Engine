#pragma once
#include "Model.h"
class GameObject
{
public:
	Model GetModel() const { return obj; }
	void SetModel(Model m) { obj = m; }

private:
	Model obj;
	//Physics of some kind
};

