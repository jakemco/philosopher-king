#pragma once
class InputManager
{
public:
	InputManager();
	~InputManager();
	virtual void passiveMotionCallback(int x, int y) = 0;
	virtual void activeMotionCallback(int x, int y) = 0;
	virtual void mouseCallback(int button, int state, int x, int y) = 0;
	virtual void keyboardCallback(unsigned char key, int x, int y) = 0;
};

