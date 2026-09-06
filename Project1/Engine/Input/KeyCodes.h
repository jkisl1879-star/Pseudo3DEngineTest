//KeyCodes.h
#pragma once

namespace Engine {
    enum class KeyCode {
        None = 0,

        A = 'a', B = 'b', C = 'c', D = 'd', E = 'e',
        F = 'f', G = 'g', H = 'h', I = 'i', J = 'j',
        K = 'k', L = 'l', M = 'm', N = 'n', O = 'o',
        P = 'p', Q = 'q', R = 'r', S = 's', T = 't',
        U = 'u', V = 'v', W = 'w', X = 'x', Y = 'y', Z = 'z',

        Num0 = '0', Num1 = '1', Num2 = '2', Num3 = '3',
        Num4 = '4', Num5 = '5', Num6 = '6', Num7 = '7',
        Num8 = '8', Num9 = '9',

        Space = ' ',
        Enter = '\r',
        Escape = 27,
        Backspace = '\b',
        Tab = '\t',

        Up = 72,
        Down = 80,
        Left = 75,
        Right = 77
    };
}