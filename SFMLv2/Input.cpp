#include "Input.h"



Input::Input()
{
	ResetKeys();
}

void Input::ResetKeys()
{
	MouseLeftButtonPressed = false;
	MouseRightButtonPressed = false;
	KeyboardReturnKeyPressed = false;
}

bool Input::isMouseLeftButtonPressed()
{
	return MouseLeftButtonPressed;
}

void Input::setMouseLeftButtonPressed()
{
	MouseLeftButtonPressed = true;
}

bool Input::isMouseRightButtonPressed()
{
	return  MouseRightButtonPressed;
}

void Input::setMouseRightButtonPressed()
{
	MouseRightButtonPressed = true;
}

bool Input::isKeyboardReturnKeyPressed()
{
	return  KeyboardReturnKeyPressed;
}

void Input::setKeyboardReturnKeyPressed()
{
	KeyboardReturnKeyPressed = true;
}

