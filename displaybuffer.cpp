#include <sstream>
#include <iostream>
#include "displaybuffer.h"

using namespace std;

DisplayBuffer::DisplayBuffer() {

}

DisplayBuffer::~DisplayBuffer() {

}

int DisplayBuffer::CursorSync () {

}

void DisplayBuffer::BufferLoadString(string buffstr) {
    iss.clear();
    iss.str(buffstr);
    string str;

    while (getline(iss, str)) {
        buffer.push_back(str);
    }
}

void DisplayBuffer::BufferSetX(int new_x) {
    if (new_x >= buffer.size()) {
    	//logger << "new_x " << new_x << endl;
    	//logger << "new_y " << new_y << endl;
    	cursor.x = buffer[cursor.y].size() - 1;
    	//logger << "cusor.x now set to " << cursor.x << endl;
    }
    else if (new_x < 0) cursor.x = 0;
    else cursor.x = new_x;
}

void DisplayBuffer::BufferSetY(int new_y) {
    if (new_y >= buffer.size()) cursor.y = buffer.size() - 1;
    else if (new_y < 0) cursor.y = 0;
    else cursor.y = new_y;
}

int DisplayBuffer::BufferGetX() {
    return cursor.x;
}

int DisplayBuffer::BufferGetY() {
    return cursor.x;
}

void DisplayBuffer::BufferIncX(int by) {
    BufferSetX(cursor.x + by);
}

void DisplayBuffer::BufferIncY(int by) {
    BufferSetY(cursor.y + by);
}

void DisplayBuffer::BufferDecX(int by) {
    BufferSetX(cursor.x - by);
}

void DisplayBuffer::BufferDecY(int by) {
    BufferSetY(cursor.y - by);
}

void DisplayBuffer::BufferSetCursor(NcursesCoordW new_cursor) {
    BufferSetX(new_cursor.x);
    BufferSetY(new_cursor.y);
}

NcursesCoordW DisplayBuffer::BufferGetCursor() {
    return cursor;
}

void DisplayBuffer::BufferInsert(string value) {
    string & current_string = buffer[cursor.y];
    current_string.insert(cursor.x, value);
}
