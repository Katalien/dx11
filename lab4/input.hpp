#pragma once
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include <directxmath.h>
#include <windows.h>

using namespace DirectX;

class Input {
public:

    void Init(HINSTANCE hinstance, HWND hwnd);
    XMFLOAT3 ReadMouse();
    XMFLOAT2 testRead();

private:
    
    HWND hwnd;
    POINT curCursor;
    POINT prevCursor;
    DIMOUSESTATE mouseState_ = {};
    unsigned char keyboardState_[256];
};