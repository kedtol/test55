#pragma once
class InputHandler 
{

    bool rawStateList[12];
    bool keyStateList[12];

public:
    InputHandler();

    void buttonPressed(int button, bool released);

    bool isButtonPressed( int button);

    bool isButtonHold(int button) const;

};