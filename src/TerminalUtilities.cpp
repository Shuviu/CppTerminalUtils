#include "TerminalUtilities.h"

#include <iostream>

#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>
#include <iomanip>
#include <ostream>
#include <termios.h>
#include <unistd.h>

void Console::StdWrite(const std::string& str) {
    std::cout << str;
}

void Console::StdWriteLine(const std::string& str) {
    std::cout << str << std::endl;
}


int Console::StdReadKey() {
    int c{};
    try {
        struct termios oldt{}, newt{};
        // save current terminal settings
        tcgetattr(STDIN_FILENO, &oldt);
        // change new settings to not echo and don't use any char buffer
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        // Update terminal settings
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        // get first keypress
        c = getchar();

        // if control char, fetch the second character to get the actual key pressed
        if (c == 27) {
            c = getchar();
            c = -getchar();
        }

        // Reset terminal to old settings
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
    return c;
}

void Console::SetCursor(const int row, const int col) {
    std::cout << "\033[" << row << ";" << col << "H" << std::flush;
}


void Console::StdClear() {
    std::cout << "\033[H\033[2J" << std::flush;
}

void Console::SetColor(const int colorCode) {
    std::cout << "\033[1;" << colorCode << "m" << std::flush;
}

void Console::ResetColor() {
    std::cout << "\033[0m" << std::flush;
}

void Console::StdReset() {
    std::cout << "\033c" << std::flush;
}

#endif //CONSOLE_H
