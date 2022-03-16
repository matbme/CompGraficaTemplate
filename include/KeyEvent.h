#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <array>

class KeyEvent {
public:
    KeyEvent ();
    ~KeyEvent ();

    enum KeyStatus {
        UNPRESSED, PRESSED, LOCKED
    };

    static std::array <KeyStatus, 1024> keys;
};

#endif
