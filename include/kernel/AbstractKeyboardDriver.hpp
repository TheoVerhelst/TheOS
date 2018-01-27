#ifndef ABSTRACTKEYBOARDDRIVER_HPP
#define ABSTRACTKEYBOARDDRIVER_HPP

class AbstractKeyboardDriver
{
    public:
        virtual void pollKeyboard() = 0;
        virtual bool characterQueueEmpty() const = 0;
        virtual char getCharacter() = 0;
};

#endif // ABSTRACTKEYBOARDDRIVER_HPP
