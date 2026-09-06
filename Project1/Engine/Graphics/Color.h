//Color.h
#pragma once
#include <windows.h>

namespace Engine {
    enum class Color : WORD {
        Black = 0x0000,
        DarkBlue = 0x0001,
        DarkGreen = 0x0002,
        DarkCyan = 0x0003,
        DarkRed = 0x0004,
        DarkMagenta = 0x0005,
        DarkYellow = 0x0006,
        Gray = 0x0007,
        DarkGray = 0x0008,
        Blue = 0x0009,
        Green = 0x000A,
        Cyan = 0x000B,
        Red = 0x000C,
        Magenta = 0x000D,
        Yellow = 0x000E,
        White = 0x000F
    };
}