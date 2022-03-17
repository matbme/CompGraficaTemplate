#include "KeyEvent.h"

KeyEvent::KeyEvent () {}
KeyEvent::~KeyEvent () {}

std::array <KeyEvent::KeyStatus, 1024> KeyEvent::keys = { KeyEvent::KeyStatus::UNPRESSED };
