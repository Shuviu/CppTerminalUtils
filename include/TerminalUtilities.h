#ifndef TERMINALUTILITIES_LIBRARY_H
#define TERMINALUTILITIES_LIBRARY_H

#include "TerminalUtilities.h"
#include <string>

class Console {
    public:
        // Writes text to the std output
        static void StdWrite(const std::string& str);

        // Writes text to the std output and starts a new line
        static void StdWriteLine(const std::string& str);

        // Reads a single Keystroke from the std input
        // Returns the ASCII index of that char
        // If control character (e.g. arrow keys) the index will be returned as negative value
        // Returns -1 for any error
        static int StdReadKey();

        // Sets the cursor the provided position
        static void SetCursor(int row, int col);

        // Sets the console color to the provided color code
        // Note that the ANSI Color codes for both font- and background color have to be used
        static void SetColor(int colorCode);

        // Resets font- and background color to the default values
        static void ResetColor();

        // Clears the console using ANSII escape codes
        // Not recommended as it more or less just pushes the text upwards
        // Keeps color settings though
        static void StdClear();

        // Fully resets the console using system commands
        // Recommended way to clear the screen
        static void StdReset();
};
#endif //TERMINALUTILITIES_LIBRARY_H