#pragma once
class Input
{
	bool MouseLeftButtonPressed, MouseRightButtonPressed;
	bool KeyboardReturnKeyPressed;

public:
	Input();

	void ResetKeys();
	bool isMouseLeftButtonPressed();
	void setMouseLeftButtonPressed();

	bool isMouseRightButtonPressed();
	void setMouseRightButtonPressed();

	bool isKeyboardReturnKeyPressed();
	void setKeyboardReturnKeyPressed();
};

