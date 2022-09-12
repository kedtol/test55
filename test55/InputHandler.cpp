#include "InputHandler.h"

InputHandler::InputHandler()
{
    mouse_x = 0;
    mouse_y = 0;
    
    for (int i = 0; i < 10; i++)
    {
        rawStateList[i] = true;
        keyStateList[i] = false;
    }
}

void InputHandler::buttonPressed(int button, bool released)
{
    rawStateList[button] = released;
}

bool InputHandler::isButtonPressed(int button)
{
    if (!(rawStateList[button]))
    {
        keyStateList[button] = true;
        return false;
    }
    else
    {
        if (keyStateList[button] == false)
        {
            return false;
        }
        else
        {
            keyStateList[button] = false;
            return true;
        }

    }

}

bool InputHandler::isButtonHold(int button) const
{
    if (rawStateList[button])
    {
        return false;
    }
    else
    {
        return true;
    }

}

void InputHandler::recordMouse()
{
    SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse_x -= 512;
    mouse_y -= 384;
}
