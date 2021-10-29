#ifndef HEADERS_MENU_H
#define HEADERS_MENU_H

#include <stdlib.h>
#include <termios.h>
#include <vector>

enum { UP='A', DOWN='B', RIGHT='C', LEFT='D', ENTER='\n' };
const int STDIN_FILENO = 0;

class Menu {

public:
    Menu();

    void PrintMenu();
    void SelectOption(int option);
    void AddOption(std::string input);
    void ClearAllOptions();
    int  NumOptions();
    int  getch();           // This is an implementation to mimic the Windows implementation of getch, in order to capture arrow key presses.

private:
    // Private methods

    // Private constants

    // Private members
    std::vector<std::string> m_options;
    long unsigned int        m_selected_option;
    bool                     m_clear_when_display;
};

#endif
