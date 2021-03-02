#pragma once
class Window
{
public:
	virtual bool Init() { return false; }
	virtual void Display() {}
	virtual void Terminate() {}
private:
	~Window() { Terminate(); }
};

