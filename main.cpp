/*
 * main.cpp
 * TODO: add code to extract leftclick/rightclick/middleclick down/up state from mouse.
 * TODO: add DisplayBuffer instance to inside of NcursesWrapper. Get it to integrate with ncw -- e.g., have wrapper functions for all major DisplayBuffer functions used.
            (or maybe just set it up to be accessible from the outside?)
 */

#include <iostream>
#include <sstream>
#include <vector>

// I've been told it's important to have ncurses AFTER sstream
#include "ncurseswrapper.h"
using namespace std;

bool pressed = true;
bool debug = false;
string debug_str;

NcursesWrapper ncw;

string buffer_string = "this is test line #1\n\
this is test line #2\n\
this is test line #3\n";
int i = 0;
string inp_as_str;
int main()
{
	i += 2;
    ncw.BufferLoadString(buffer_string);

    ncw.Print();
    ncw.EnableMouseMode();
    while (true) {
        ncw.EventCheck();
        if (ncw.IsEventMouse()) {
            if (ncw.MouseLeftPress()) {
                ncw.BufferSetCursor(ncw.GetMousePos());
                ncw.CursorSync();
            }
         } else {
            if (ncw.GetKey() == ncursesw_keys_esc) break;
            else if (ncw.GetKey() == ncursesw_keys_up) ncw.BufferIncY();
            else if (ncw.GetKey() == ncursesw_keys_down) ncw.BufferDecY();
            else if (ncw.GetKey() == ncursesw_keys_left) ncw.BufferIncX();
            else if (ncw.GetKey() == ncursesw_keys_right) ncw.BufferDecX();
            else {
                // TODO:
                // * Add logic for splitting line into multiple lines in the event of

                // * switch from vector storage to some kind of linked list for more optimal dynamic memory reorganization.
                // * consider custom linked list implementation for string for better insert() command

                inp_as_str = ncw.GetKey();
                ncw.BufferInsert(inp_as_str);
                ncw.BufferIncX();
                ncw.ClearWindow();
                ncw.Print();
            }
            ncw.CursorSync();
        }
    }
}
