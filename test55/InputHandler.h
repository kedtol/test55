#pragma once
#include <SDL.h>

class InputHandler 
{
    int mouse_x;
    int mouse_y;
    bool rawStateList[12];
    bool keyStateList[12];

public:
    InputHandler();

    void buttonPressed(int button, bool released);

    bool isButtonPressed( int button);

    bool isButtonHold(int button) const;

    void recordMouse();

    int getMouse_x() const { return mouse_x; }
    int getMouse_y() const { return mouse_y; }

};