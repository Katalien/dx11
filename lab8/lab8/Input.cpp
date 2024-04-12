#include "input.h"
#include <fstream>

void Input::Init(HINSTANCE hinstance, HWND hwnd) {
    float x = 0.0f;
    float y = 0.0f;

    prevCursor.x = static_cast<LONG>(x);
    prevCursor.y = static_cast<LONG>(y);
    curCursor.x = static_cast<LONG>(x);
    curCursor.y = static_cast<LONG>(y);
}


XMFLOAT3 Input::ReadMouse() {
    POINT cursor;

    if (GetCursorPos(&cursor)) {
        ScreenToClient(hwnd, &cursor);
        if (cursor.x == curCursor.x && cursor.y == curCursor.y) {
            return XMFLOAT3(0.0f, 0.0f, 0.0f);
        }

        prevCursor = curCursor;
        curCursor = cursor;
        GetKeyboardState(keyboardState_);

        if (keyboardState_[VK_LBUTTON] & 0x80) {
            return  XMFLOAT3(
                (curCursor.x - prevCursor.x) / 100.0f,
                (curCursor.y - prevCursor.y) / 100.0f,
                0.0f);
        }
        if (keyboardState_[VK_UP] & 0x80) {
            return  XMFLOAT3(0.0f, 0.0f, -1.0f);
        }
        if (keyboardState_[VK_DOWN] & 0x80) {
            return  XMFLOAT3(0.0f, 0.0f, 1.0f);
        }
        else {
            return XMFLOAT3(0.0f, 0.0f, 0.0f);
        }
    }
}
