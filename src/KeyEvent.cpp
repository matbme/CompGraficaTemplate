#import "KeyEvent.h"

KeyEvent::KeyEvent () {
    keys.fill (KeyStatus::UNPRESSED);
}
