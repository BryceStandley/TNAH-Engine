#pragma once
class Renderer
{
public:
	~Renderer() { Terminate(); }
	virtual void Render() {};
	virtual bool Init() { return false; };
	virtual void Update() {};
	virtual void Terminate() {};
};

