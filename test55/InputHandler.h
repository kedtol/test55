#pragma once
class InputHandler 
{

    bool rawStateList[10];
    bool keyStateList[10];

public:
    InputHandler();

    void buttonPressed(int button, bool released);

    bool isButtonPressed( int button);

    bool isButtonHold(int button) const;

};