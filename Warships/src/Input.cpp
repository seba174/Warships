#include "stdafx.h"
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
	KeyboardBackspaceKeyPressed = false;
	ScrollMovedUp = false;
	ScrollMovedDown = false;
	inputText = NULL;
}



