/*
 *  ncurseswrapper.h
 */

#ifndef NCURSESWRAPPER_H
#define NCURSESWRAPPER_H

#include <ncurses.h>
#include <string>
#include "displaybuffer.h"

using namespace std;

class NcursesWrapper: public DisplayBuffer {
protected:
    WINDOW* my_window;
    bool mouse_mode;
    ncursesw_events key_event;
    MEVENT mouse_event;
    int c;
public:
    NcursesWrapper();
    ~NcursesWrapper();
    void print(string);
    void refresh();
    int add_string(string);
    int add_char(int);
    void EnableMouseMode();
    WINDOW* GetWindowHandler();
    int EventCheck();
    bool IsEventError();
    bool IsEventMouse();
    bool IsEventMouseError();
    bool IsEventKey();
    MEVENT GetMouseEvent();
    int GetKey();
    int GetMouseX();
    int GetMouseY();
    NcursesCoordW GetMousePos();
    bool MouseLeftPress();
    bool MouseRightPress();
    bool MouseMiddlePress();
    int MoveCursor(NcursesCoordW);
    int MoveCursor(int, int);
    int ClearWindow();
    void Print();
    int CursorSync();
};

#endif // NCURSESWRAPPER_H
