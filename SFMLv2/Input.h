#pragma once

class Input
{
	bool MouseLeftButtonPressed, MouseRightButtonPressed;
	bool KeyboardReturnKeyPressed, KeyboardEscapeKeyPressed, KeyboardBackspaceKeyPressed;
	bool ScrollMovedUp, ScrollMovedDown;
	char inputText;

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

	bool isKeyboardBackspaceKeyPressed() const { return KeyboardBackspaceKeyPressed; }
	void setKeyboardBackspaceKeyPressed() { KeyboardBackspaceKeyPressed = true; }

	bool hasScrollMovedUp() const { return ScrollMovedUp; }
	void setScrollMovedUp() { ScrollMovedUp = true; }

	bool hasScrollMovedDown() const { return ScrollMovedDown; }
	void setScrollMovedDown() { ScrollMovedDown = true; }

	char returnInputText() const { return inputText; }
	void setInputText(char newText) { inputText = newText; }
};

