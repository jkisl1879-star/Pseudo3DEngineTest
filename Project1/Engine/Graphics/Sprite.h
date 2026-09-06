#pragma once
#include <vector>
#include <string>
#include "Graphics/Color.h"

namespace Engine {
    struct Sprite {
        int width, height;
        std::vector<wchar_t> chars;
        std::vector<WORD> colors;

        Sprite(int w = 1, int h = 1) : width(w), height(h) {
            chars.resize(static_cast<size_t>(w * h), L' ');
            colors.resize(static_cast<size_t>(w * h), static_cast<WORD>(Color::White));
        }

        void SetPixel(int x, int y, wchar_t ch, WORD color = static_cast<WORD>(Color::White)) {
            if (x < 0 || y < 0 || x >= width || y >= height) return;
            int idx = y * width + x;
            chars[idx] = ch;
            colors[idx] = color;
        }

        wchar_t GetChar(int x, int y) const {
            if (x < 0 || y < 0 || x >= width || y >= height) return L' ';
            return chars[static_cast<size_t>(y * width + x)];
        }

        WORD GetColor(int x, int y) const {
            if (x < 0 || y < 0 || x >= width || y >= height) return static_cast<WORD>(Color::White);
            return colors[static_cast<size_t>(y * width + x)];
        }

        static Sprite FromString(const std::vector<std::wstring>& lines, WORD color = static_cast<WORD>(Color::White)) {
            if (lines.empty()) return Sprite(1, 1);

            int h = static_cast<int>(lines.size());
            int w = static_cast<int>(lines[0].size());
            Sprite sprite(w, h);

            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w && x < static_cast<int>(lines[y].size()); ++x) {
                    sprite.SetPixel(x, y, lines[y][x], color);
                }
            }
            return sprite;
        }
    };
}