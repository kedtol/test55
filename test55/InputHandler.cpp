#include "InputHandler.h"

InputHandler::InputHandler()
{
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
