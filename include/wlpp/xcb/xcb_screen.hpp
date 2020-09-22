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
    xcb_screen_t *p_screen;

public:
    xcb_screen(const xcb_screen_t &);
};

}

#endif //WLPP_XCB_SCREEN_HPP
