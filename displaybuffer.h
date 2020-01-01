#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#include <vector>
#include <string>
#include <sstream>
#include "ncurseswdef.h"
#include "logger.h"

using namespace std;

class DisplayBuffer {

protected:
    // Vector may be a bad choice due to need for insertions,
    // but I'm not sure which structure would be optimal.
    vector <string> buffer;
    // for storing coordinates of cursor
    NcursesCoordW cursor;
    // object for splitting strings
    istringstream iss;
    Logger logger("displaybuffer.log");

public:
    DisplayBuffer();
    ~DisplayBuffer();
    int CursorSync();
    void BufferSetX(int);
    void BufferSetY(int);
    void BufferLoadString(string);
    int BufferGetX();
    int BufferGetY();
    NcursesCoordW BufferGetCursor();
    void BufferSetCursor(NcursesCoordW);
    void BufferIncX(int by = 1);
    void BufferIncY(int by = 1);
    void BufferDecX(int by = 1);
    void BufferDecY(int by = 1);
    void BufferInsert(string);
};

#endif // DISPLAYBUFFER_H
