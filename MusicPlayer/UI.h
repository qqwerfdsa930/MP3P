#ifndef UI_H
#define HI_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "windows.h"
#include <conio.h>

#ifndef _NO_CONSOLE_DEFS
#define _NO_CONSOLE_DEFS
namespace Console
{
    enum Color
    {
        BlackWhite = 15, WhiteBlack = 240
    };
    struct Position
    {
        int x, y;
    };
    enum Direction
    {
        Left, Right, Up, Down
    };
    const Console::Color DefaultColor = BlackWhite;
}

class UI
{
public:
    UI();
    ~UI();
    void write(const std::string& in);
    void write(const std::string& in, const Console::Position& pos);
    void write(const std::string& in, const Console::Position& pos, const Console::Color& color);
    void moveCursor(const Console::Position& pos);
    void moveCursorBack();
    void getxy(int& x, int& y);

private:
    Console::Position prevPos;
    HANDLE hConsole;
    void setOutputColor(const Console::Color& color);
    static bool writeLock;
    bool upperLock;



};
#endif

#endif // UI_H
