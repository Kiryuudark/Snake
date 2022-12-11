#include <iostream>
#include <curses.h>

using namespace std;

int main() {

    initscr();
    printw("hello world");

    getch();
    endwin();
    return 0;
}