#ifndef NCURSESWDEF_H
#define NCURSESWDEF_H

struct NcursesCoordW {
    int x;
    int y;
};

enum class ncursesw_events {null, error, mouse, mouse_error, key};
enum class ncursesw_mouse_events {null, left_pressed, left_released, right_pressed, middle_pressed};

// Could have used enum, but I thought this fit better
// Decided against using preprocessor definitions to avoid confusing error messages.
static constexpr int ncursesw_keys_esc = 27;
static constexpr int ncursesw_keys_backspace = 263;
static constexpr int ncursesw_keys_up = 258;
static constexpr int ncursesw_keys_down = 259;
static constexpr int ncursesw_keys_left = 260;
static constexpr int ncursesw_keys_right = 261;

#endif
