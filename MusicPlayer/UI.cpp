#include "UI.H"

UI::UI()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    upperLock = false;
}

UI::~UI()
{

}
bool UI::writeLock = false;

void UI::write(const std::string& in)
{
    while (writeLock && !upperLock)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    writeLock = true;
    std::cout << in;
    writeLock = upperLock = false;
}

void UI::write(const std::string& in, const Console::Position& pos)
{
    while (writeLock && !upperLock)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    writeLock = upperLock = true;
    moveCursor(pos);
    write(in);
    moveCursorBack();
}
void UI::write(const std::string& in, const Console::Position& pos, const Console::Color& color)
{
     while (writeLock && !upperLock)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    writeLock = upperLock = true;
    setOutputColor(color);
    write(in, pos);
    moveCursorBack();
    setOutputColor(Console::DefaultColor);
}

void UI::moveCursor(const Console::Position& pos)
{
    COORD point;
    point.X = pos.x, point.Y = pos.y;
    getxy(prevPos.x, prevPos.y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void UI::getxy(int &x, int &y)
{
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
}

void UI::moveCursorBack()
{
    moveCursor(prevPos);
}

void UI::setOutputColor(const Console::Color& color)
{
    SetConsoleTextAttribute(hConsole, color);
}
