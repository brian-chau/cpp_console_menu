#include <iostream>

#include "menu.h"

Menu::Menu()
    : m_selected_option(0)
    , m_clear_when_display(true)
{

}

///////////////////////////////////////////////////////////////////////////////
//** Name:        PrintMenu                                                **//
//** Description: This method prints the menu to the screen with a certain **//
//**                color for the selected item. The source for the colors **//
//**                come from this StackOverflow answer:                   **//
//**                https://stackoverflow.com/a/54062826                   **//
//**              Copy/pasted are the codes from the answer:               **//
//**                Name            FG  BG                                 **//
//**                Black           30  40                                 **//
//**                Red             31  41                                 **//
//**                Green           32  42                                 **//
//**                Yellow          33  43                                 **//
//**                Blue            34  44                                 **//
//**                Magenta         35  45                                 **//
//**                Cyan            36  46                                 **//
//**                White           37  47                                 **//
//**                Bright Black    90  100                                **//
//**                Bright Red      91  101                                **//
//**                Bright Green    92  102                                **//
//**                Bright Yellow   93  103                                **//
//**                Bright Blue     94  104                                **//
//**                Bright Magenta  95  105                                **//
//**                Bright Cyan     96  106                                **//
//**                Bright White    97  107                                **//
///////////////////////////////////////////////////////////////////////////////
void Menu::PrintMenu() {
    if (m_clear_when_display) {
        system("clear");
    }

    for(long unsigned int i=0; i<m_options.size(); i++) {
        // Color source:
        if (i == m_selected_option) {
            printf("    \x1B[32m%s\033[0m\t\t\n", m_options[i].c_str());
        } else {
            std::cout << "    " << m_options[i] << '\n';
        }
    }
}

void Menu::AddOption(std::string option) {
    m_options.push_back(option);
}

void Menu::ClearAllOptions() {
    m_options.clear();
}

void Menu::SelectOption(int option) {
    m_selected_option = option;
}

int Menu::NumOptions() {
    // Using static_cast to avoid using C-style type casting.
    return static_cast<int>(m_options.size());
}

///////////////////////////////////////////////////////////////////////////////
//** Name:        getch                                                    **//
//** Description: This method mimics the Windows implementation of getch   **//
//**              to capture arrow key presses.                            **//
//** Return Type: int                                                      **//
//** Returns:     An integer to represent which arrow key was pressed.     **//
///////////////////////////////////////////////////////////////////////////////
int Menu::getch() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // This implementation is specific to Linux.
    // For the arrow keys, Linux creates 3 chars
    //   per arrow key. However, on Windows,
    //   the arrow keys produce a single integer.
    char c('a'),d('a'),e('a');
    std::cin.get(c);

    // Using Yoda conditionals here to avoid accidental assignments
    if ('\n' == c) {
        return ENTER;
    } else if ('\x1b' != c) {
        return 0;
    }

    std::cin.get(d);
    std::cin.get(e);

    if ('['==d) {
        switch(e) {
            case UP:
            case LEFT:
            case RIGHT:
            case DOWN:{
                if (m_clear_when_display) {
                    system("clear");
                }
                return e;
            }
        }
    }
    return 0;
}
