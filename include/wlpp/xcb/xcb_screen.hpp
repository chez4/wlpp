#ifndef WLPP_XCB_SCREEN_HPP
#define WLPP_XCB_SCREEN_HPP

#include <xcb/xcb.h>

namespace wlpp {

class xcb_screen {
private:
    xcb_screen_t *screen;

public:
    xcb_screen();
};

}

#endif //WLPP_XCB_SCREEN_HPP
