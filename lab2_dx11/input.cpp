#include "input.h"
#include <fstream>

HRESULT Input::Init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight) {
    HRESULT hr = S_OK;
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
    if (SUCCEEDED(hr)) {
        hr = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
    }

   
    if (SUCCEEDED(hr)) {
        hr = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
    }

    if (SUCCEEDED(hr)) {
        hr = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    }

    if (SUCCEEDED(hr)) {
        hr = m_keyboard->Acquire();
    }

    if (SUCCEEDED(hr)) {
        hr = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
    }

    if (SUCCEEDED(hr)) {
        hr = m_mouse->SetDataFormat(&c_dfDIMouse);
    }

    if (SUCCEEDED(hr)) {
        hr = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    }

    if (SUCCEEDED(hr)) {
        hr = m_mouse->Acquire();
    }

    POINT point;
    float x = 0.0f;
    float y = 0.0f;

    deltaCursor.x = static_cast<LONG>(x);
    deltaCursor.y = static_cast<LONG>(y);
    return hr;

}

void Input::Resize(int screenWidth, int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}

bool Input::Frame() {
    return ReadMouse();
}


bool Input::ReadMouse() {
    POINT cursor;
    
    if (GetCursorPos(&cursor) ) {
        ScreenToClient(hwnd, &cursor);
        std::ofstream outputFile("check_coords.txt");
        outputFile << "read mouse" << std::endl;
        if (cursor.x == curCursor.x && cursor.y == curCursor.y) {
            return true;
        }
        
        CountDelta(cursor);
        prevCursor = curCursor;
        curCursor = cursor;
        return true;
    }
    else {
        return false;
    }

}


XMFLOAT3 Input::IsMouseUsed() {
    XMFLOAT3 mouseDelta = XMFLOAT3(
        curCursor.x - prevCursor.x,
        curCursor.y - prevCursor.y,
        0.0f);

    BYTE keyState[256];
    GetKeyboardState(keyState);

    if (keyState[VK_UP] & 0x80) {
        mouseDelta.z = 1.0f;
        return mouseDelta;
    }

    if (keyState[VK_DOWN] & 0x80) {
        mouseDelta.z = -1.0f;
        return mouseDelta;
    }

    if (keyState[VK_LBUTTON] & 0x80)
        return mouseDelta;
    return XMFLOAT3(0.0f, 0.0f, 0.0f);
};



void Input::CountDelta(POINT const& cursor) {
    float deltaX = cursor.x - curCursor.x;
    float deltaY = cursor.y - curCursor.y;
    POINT delta = { deltaX, deltaY };
    deltaCursor = delta;
}

XMFLOAT3 Input::PointToXMFLOAT3(POINT const& cursor) {
    return { float(cursor.x), float(cursor.y), 0.0f };
}