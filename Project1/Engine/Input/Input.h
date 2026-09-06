#pragma once
#include <conio.h>
#include <windows.h>
#include <unordered_map>
#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

namespace Engine {
    class Input {
    private:
        std::unordered_map<KeyCode, bool> keyStates;
        std::unordered_map<KeyCode, bool> keyPressed;
        KeyCode lastKey = KeyCode::None;

        std::unordered_map<MouseButton, bool> mouseStates;
        std::unordered_map<MouseButton, bool> mousePressed;
        int mouseX = 0;
        int mouseY = 0;
        int mouseDeltaX = 0;
        int mouseDeltaY = 0;
        int mouseWheelDelta = 0;
        bool mouseCaptured = false;
        POINT lastMousePos = { 0, 0 };

        HWND hwnd = nullptr;

        void UpdateMousePosition() {
            if (!hwnd) return;

            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            mouseDeltaX = pt.x - lastMousePos.x;
            mouseDeltaY = pt.y - lastMousePos.y;

            if (mouseCaptured) {
                mouseX = pt.x;
                mouseY = pt.y;
            }

            lastMousePos = pt;
        }

    public:
        Input() {
            hwnd = GetConsoleWindow();
            GetCursorPos(&lastMousePos);
            ScreenToClient(hwnd, &lastMousePos);
            mouseX = lastMousePos.x;
            mouseY = lastMousePos.y;
        }

        void Update() {
            keyPressed.clear();

            for (int k = 'A'; k <= 'Z'; ++k) {
                bool state = (GetAsyncKeyState(k) & 0x8000) != 0;
                KeyCode code = static_cast<KeyCode>(tolower(k));
                if (state && !keyStates[code]) {
                    keyPressed[code] = true;
                }
                keyStates[code] = state;
            }

            if (_kbhit()) {
                int ch = _getch();
                if (ch == 224 || ch == 0) {
                    ch = _getch();
                    lastKey = static_cast<KeyCode>(ch);
                }
                else {
                    lastKey = static_cast<KeyCode>(ch);
                }
            }

            mousePressed.clear();
            mouseWheelDelta = 0;

            MouseButton buttons[] = {
                MouseButton::Left,
                MouseButton::Right,
                MouseButton::Middle
            };

            for (auto btn : buttons) {
                int vKey = 0;
                switch (btn) {
                case MouseButton::Left: vKey = VK_LBUTTON; break;
                case MouseButton::Right: vKey = VK_RBUTTON; break;
                case MouseButton::Middle: vKey = VK_MBUTTON; break;
                default: continue;
                }

                bool state = (GetAsyncKeyState(vKey) & 0x8000) != 0;
                if (state && !mouseStates[btn]) {
                    mousePressed[btn] = true;
                }
                mouseStates[btn] = state;
            }

            UpdateMousePosition();

            short wheelDelta = 0;
            if (hwnd) {
                MSG msg;
                while (PeekMessage(&msg, hwnd, WM_MOUSEWHEEL, WM_MOUSEWHEEL, PM_REMOVE)) {
                    if (msg.message == WM_MOUSEWHEEL) {
                        wheelDelta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
                        mouseWheelDelta += wheelDelta;
                    }
                }
            }
        }

        bool IsKeyDown(KeyCode key) const {
            auto it = keyStates.find(key);
            return it != keyStates.end() && it->second;
        }

        bool IsKeyPressed(KeyCode key) const {
            auto it = keyPressed.find(key);
            return it != keyPressed.end() && it->second;
        }

        bool IsKeyUp(KeyCode key) const {
            auto it = keyStates.find(key);
            return it == keyStates.end() || !it->second;
        }

        bool IsMouseDown(MouseButton button) const {
            auto it = mouseStates.find(button);
            return it != mouseStates.end() && it->second;
        }

        bool IsMousePressed(MouseButton button) const {
            auto it = mousePressed.find(button);
            return it != mousePressed.end() && it->second;
        }

        bool IsMouseUp(MouseButton button) const {
            auto it = mouseStates.find(button);
            return it == mouseStates.end() || !it->second;
        }

        int GetMouseX() const { return mouseX; }
        int GetMouseY() const { return mouseY; }
        int GetMouseDeltaX() const { return mouseDeltaX; }
        int GetMouseDeltaY() const { return mouseDeltaY; }
        int GetMouseWheelDelta() const { return mouseWheelDelta; }

        void SetMouseCapture(bool capture) {
            mouseCaptured = capture;
            if (capture) {
                SetCapture(hwnd);
                ShowCursor(FALSE);
            }
            else {
                ReleaseCapture();
                ShowCursor(TRUE);
            }
        }

        bool IsMouseCaptured() const { return mouseCaptured; }

        KeyCode GetLastKey() const { return lastKey; }
    };
}