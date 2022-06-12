#ifndef HOWTOPLAYWINDOW_H
#define HOWTOPLAYWINDOW_H

#include <ncurses.h>
#include <string>

/// Simple class showing content of "how_to_play"
class HowToPlayWindow {
public:
    HowToPlayWindow() = default;

    /// Shows the window
    static void showHowTo(const std::string &path);
};

#endif
