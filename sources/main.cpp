#include <iostream>
#include <memory>

#include "menu.h"

int main(int argc, char** argv){
    int  selected(0);     //Keeps track of which option is selected.
    int  numChoices(0);   //The number of choices we have.
    bool selecting(true); //True if user has not yet pressed Enter
    bool updated(false);  //True if user hits an arrow key
    char c;

    // Using std::unique_ptr to avoid the need to remember to delete the objec
    std::unique_ptr<Menu> menu(new Menu());
    for(int i=1; i<argc; i++) {
        menu->AddOption(std::string(argv[i]));
    }
    numChoices = menu->NumOptions();
    menu->PrintMenu();

    while (selecting) {
        switch ((c = menu->getch())) {
            case UP:
                if (selected > 0) {
                    --selected;
                    updated = true;
                }
                break;
            case DOWN:
                if (selected < numChoices - 1) {
                    ++selected;
                    updated = true;
                }
                break;
            case ENTER:
                selecting = false;
                break;
            default:
                break;
        }
        if (updated) {
            menu->SelectOption(selected);
            updated = false;
        }
        menu->PrintMenu();
    }

    std::cout << "Selected " << (selected + 1) << '\n';
    return 0;
}
