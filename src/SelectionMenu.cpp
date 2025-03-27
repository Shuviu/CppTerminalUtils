//
// Created by shuviu on 2/26/25.
//

#include "include/SelectionMenu.h"
#include <iostream>
#include "TerminalUtilities.h"

SelectionMenu::SelectionMenu(std::vector<Option> *optionsPtr,
                            const char cursorChar,
                            const int cursorGap,
                            const int keyNextOption,
                            const int keyPrevOption,
                            const int keyReturnOption) {

    SelectionMenu::options = optionsPtr;
    SelectionMenu::cursorChar = cursorChar;
    SelectionMenu::cursorGap = cursorGap;
    SelectionMenu::keyNextOption = keyNextOption;
    SelectionMenu::keyPrevOption = keyPrevOption;
    SelectionMenu::keyReturnOption = keyReturnOption;
}


int SelectionMenu::Start() {
    // Init the base selection menu
    for (const auto& option: *options) {
        RenderOption(&option);
    }
    RenderCursor();

    // Fetch the selected option
    while (CheckInput() == -1) {
        RenderCursor();
    }

    return currHighlightIndex;
}

// Render a single option to the screen
void SelectionMenu::RenderOption(const Option* optionPtr) const {
    Console::SetCursor(std::get<0>(optionPtr->pos), std::get<1>(optionPtr->pos) + ( 1 + cursorGap ) );
    std::cout << optionPtr->prompt;

}

// Rerender the cursor to the current highlight option
void SelectionMenu::RenderCursor() const {
    // Remove old cursor if necessary
    if (prevHighlightIndex >= 0) {
        const std::tuple<int, int> oldPos = options->operator[](prevHighlightIndex).pos;
        Console::SetCursor(std::get<0>(oldPos), std::get<1>(oldPos));
        std::cout << ' ' << std::flush;
    }

    // Render the new cursor
    const std::tuple<int, int> newPos = options->operator[](currHighlightIndex).pos;
    Console::SetCursor(std::get<0>(newPos), std::get<1>(newPos));
    std::cout << cursorChar << std::flush;
}

// Check for user input and handle arrow movement + submission
// Returns either the arrays index for a selected option
// Or -1 for a cursor movement or random keys
int SelectionMenu::CheckInput() {
    if (const int key = Console::StdReadKey(); key == keyReturnOption) {
        // Returns Index of currently selected option
        return currHighlightIndex;
    }
    else if (key == keyNextOption) {
        // Moves cursor to next option / position
        if (currHighlightIndex + 1 < options->size()) {
            prevHighlightIndex = currHighlightIndex;
            currHighlightIndex += 1;
        }
    }
    else if (key == keyPrevOption) {
        // Moves cursor to previous option / position
        if (currHighlightIndex - 1 >= 0) {
            prevHighlightIndex = currHighlightIndex;
            currHighlightIndex -= 1;
        }
    }

    return -1;
}