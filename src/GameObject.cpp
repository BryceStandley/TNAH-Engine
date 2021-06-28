#include "GameObject.h"


void GameObject::Update(float time)
{
    std::cout << "GAMEOBJECT::ERROR::UPDATE::TYPE_NOT_SET" << std::endl;
}

void GameObject::Render(View lens, float time, Renderer* gameRenderer)
{
    model.Render(lens, shader, pos, rotation, scale, rotate, time, 0, gameRenderer, false);
}

std::string GameObject::StreamValues()
{
	return GetType() + " " + GetScriptName() + " " + std::to_string(GetScale()) + " " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " " + std::to_string(pos.z) + "\n";
}