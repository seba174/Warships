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
	KeyboardEscapeKeyPressed = false;
}



