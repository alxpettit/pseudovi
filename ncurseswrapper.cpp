/*
 * ncurseswrapper.cpp
 */

#include <cstdio>
//#include <sstream>
// I've been told it's important to have ncurses AFTER sstream
#include <ncurses.h>
#include "ncurseswrapper.h"

using namespace std;

NcursesWrapper::NcursesWrapper() {
    my_window = initscr();
    clear(); // Um... clear things, I guess?

    // Set terminal mode to prevent echoing-by-default,
    // so as to allow us to choose whether or not to echo specific chars (e.g. ESC)
    noecho();
    raw(); // Disable line buffering and allow capture of special key sequences (e.g., Ctrl+D)
}

NcursesWrapper::~NcursesWrapper() {
    if (mouse_mode) printf("\033[?1003l\n");
    endwin();
}

void NcursesWrapper::print(string output) {
    printw(output.c_str());
}

void NcursesWrapper::refresh() {
    refresh();
}


int NcursesWrapper::add_string(string str) {
    return waddstr(my_window, str.c_str());
}

int NcursesWrapper::add_char(int c) {
    return waddch(my_window, c);
}

void NcursesWrapper::EnableMouseMode() {
    // Necessary for getting events with KEY_MOUSE
    keypad(my_window, TRUE);
    // Don't mask any mouse events
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    printf("\033[?1003h\n");
    mouse_mode = true;
}

int NcursesWrapper::EventCheck() {
    c = wgetch(my_window);
    if (c == ERR) key_event = ncursesw_events::error;
    else if (c == KEY_MOUSE) {
        if (getmouse(&mouse_event) == OK) {
            key_event = ncursesw_events::mouse;
        }
    } else {
        key_event = ncursesw_events::key;
    }
    return c;
}

bool NcursesWrapper::IsEventError() {
    return key_event == ncursesw_events::error;
}

bool NcursesWrapper::IsEventMouse() {
    return key_event == ncursesw_events::mouse;
}

WINDOW* NcursesWrapper::GetWindowHandler() {
    return my_window;
}

int NcursesWrapper::GetKey() {
    return c;
}

int NcursesWrapper::GetMouseX() {
    return mouse_event.x;
}

int NcursesWrapper::GetMouseY() {
    return mouse_event.y;
}

int NcursesWrapper::ClearWindow() {
    wmove(my_window, 0, 0);
    return wclrtoeol(my_window);
}

NcursesCoordW NcursesWrapper::GetMousePos(){
    return {mouse_event.x, mouse_event.y};
}

bool NcursesWrapper::MouseLeftPress() {
    // I tried to use the built in bitmasks, but it didn't work.
    // Need to also detect when we get 0x00000002 followed rapidly by a 0x00000001
    return (mouse_event.bstate == 0x00000004);
}

bool NcursesWrapper::MouseRightPress() {
    return false;
}

bool NcursesWrapper::MouseMiddlePress() {
    return false;
}

MEVENT NcursesWrapper::GetMouseEvent() {
    return mouse_event;
}

/* Note! Flipped X and Y (because intuition) */
int NcursesWrapper::CursorSync() {
    return wmove(my_window, cursor.y, cursor.x);
}

void NcursesWrapper::Print() {
    for (auto line : buffer) {
        add_string(line);
        add_char('\n');
    }
}
