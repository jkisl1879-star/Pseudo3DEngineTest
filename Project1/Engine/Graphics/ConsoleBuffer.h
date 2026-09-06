#pragma once
#include <windows.h>
#include <vector>
#include "Graphics/Color.h"
#include "Graphics/Sprite.h"

namespace Engine {
    class ConsoleBuffer {
    private:
        HANDLE hConsole;
        COORD bufferSize;
        std::vector<CHAR_INFO> buffer;
        std::vector<CHAR_INFO> backBuffer;
        SMALL_RECT writeRegion;
        bool needsUpdate = true;

    public:
        ConsoleBuffer(int width, int height) {
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            if (width > 300) width = 300;
            if (height > 100) height = 100;

            bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
            buffer.resize(static_cast<size_t>(width) * height);
            backBuffer.resize(static_cast<size_t>(width) * height);
            writeRegion = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };

            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(hConsole, &cursorInfo);
            cursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(hConsole, &cursorInfo);

            SetConsoleScreenBufferSize(hConsole, bufferSize);
            SetConsoleOutputCP(CP_UTF8);

            ClearBuffers();
            Render();
        }

        void SetPixel(int x, int y, wchar_t ch, WORD color = static_cast<WORD>(Color::White)) {
            if (x < 0 || y < 0 || x >= bufferSize.X || y >= bufferSize.Y) return;
            int index = y * bufferSize.X + x;
            if (backBuffer[index].Char.UnicodeChar != ch || backBuffer[index].Attributes != color) {
                backBuffer[index].Char.UnicodeChar = ch;
                backBuffer[index].Attributes = color;
                needsUpdate = true;
            }
        }

        void DrawSprite(int x, int y, const Sprite& sprite) {
            for (int sy = 0; sy < sprite.height; ++sy) {
                for (int sx = 0; sx < sprite.width; ++sx) {
                    SetPixel(x + sx, y + sy, sprite.GetChar(sx, sy), sprite.GetColor(sx, sy));
                }
            }
        }

        void Clear(wchar_t ch = L' ', WORD color = static_cast<WORD>(Color::Black)) {
            for (auto& cell : backBuffer) {
                cell.Char.UnicodeChar = ch;
                cell.Attributes = color;
            }
            needsUpdate = true;
        }

        void ClearBuffers() {
            for (auto& cell : buffer) {
                cell.Char.UnicodeChar = L' ';
                cell.Attributes = 0x0000;
            }
            for (auto& cell : backBuffer) {
                cell.Char.UnicodeChar = L' ';
                cell.Attributes = 0x0000;
            }
            needsUpdate = true;
        }

        void Render() {
            if (needsUpdate) {
                buffer = backBuffer;
                WriteConsoleOutputW(hConsole, buffer.data(), bufferSize, { 0, 0 }, &writeRegion);
                needsUpdate = false;
            }
        }

        void ForceRender() {
            buffer = backBuffer;
            WriteConsoleOutputW(hConsole, buffer.data(), bufferSize, { 0, 0 }, &writeRegion);
            needsUpdate = false;
        }

        int GetWidth() const { return bufferSize.X; }
        int GetHeight() const { return bufferSize.Y; }
    };
}