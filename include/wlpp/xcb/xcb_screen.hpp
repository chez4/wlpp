/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_XCB_SCREEN_HPP
#define WLPP_XCB_SCREEN_HPP

#include <xcb/xcb.h>

namespace wlpp {

class xcb_screen {
private:
    xcb_screen_t screen;

public:
    explicit xcb_screen(const xcb_screen_t &);

    xcb_window_t get_parent_window() const;

    xcb_visualid_t get_parent_visual() const;
};

}

#endif //WLPP_XCB_SCREEN_HPP
