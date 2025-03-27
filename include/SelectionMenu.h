//
// Created by shuviu on 2/26/25.
//

#ifndef SELECTIONMENU_H
#define SELECTIONMENU_H

#include <string>
#include <vector>


// Used to store a choosable option inside a SelectionMenu
// Prompt gets rendered at the provided position
// Please note that the Cursor gets rendered 1 col before the prompt
struct Option {
    std::string prompt;
    std::tuple<int, int> pos;
};

class SelectionMenu {
    public:
        // Standard constructor for the SelectionMenu
        // Note that keys have to be passed as ASCII indexes
        // Control keys (arrow keys) are passed using the negative value of the last number in the char stream. (See Console::StdReadKey for more info)
        explicit SelectionMenu(std::vector<Option>* optionsPtr, char cursorChar = '>', int cursorGap = 0, int keyNextOption = -66, int keyPrevOption = -65, int keyReturnOption = 10);
        // Function to render and execute the selection menu.
        // On successful return it returns the index of the chosen option inside the Option Vector provided
        int Start();

    private:
        // Layout params
        char cursorChar = '>';
        int cursorGap = 0;
        int keyNextOption = -66;
        int keyPrevOption = -65;
        int keyReturnOption = 10;
        // Choosable options
        std::vector<Option>* options;

        // Technicalities
        int prevHighlightIndex = -1;
        int currHighlightIndex = 0;
        void RenderOption(const Option* optionPtr) const ;
        void RenderCursor() const;
        int CheckInput();
};




#endif //SELECTIONMENU_H
