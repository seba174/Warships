#pragma once

class Input
{
	bool MouseLeftButtonPressed, MouseRightButtonPressed;
	bool KeyboardReturnKeyPressed, KeyboardEscapeKeyPressed;

public:
	Input();

	// sets all keys and buttons to false
	void ResetKeys();

	bool isMouseLeftButtonPressed() const { return MouseLeftButtonPressed; }
	void setMouseLeftButtonPressed() { MouseLeftButtonPressed = true; }

	bool isMouseRightButtonPressed() const { return MouseRightButtonPressed; }
	void setMouseRightButtonPressed() { MouseRightButtonPressed = true; };

	bool isKeyboardReturnKeyPressed() const { return KeyboardReturnKeyPressed; }
	void setKeyboardReturnKeyPressed() {KeyboardReturnKeyPressed = true; }

	bool isKeyboardEscapeKeyPressed() const { return KeyboardEscapeKeyPressed; }
	void setKeyboardEscapeKeyPressed() { KeyboardEscapeKeyPressed = true; }
};

