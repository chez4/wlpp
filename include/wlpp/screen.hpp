#ifndef WLPP_SCREEN_HPP
#define WLPP_SCREEN_HPP

#include <xcb/xcb.h>

namespace wlpp {

class screen {
    xcb_screen_t *p_screen;

public:
    screen();
};

}

#endif //WLPP_SCREEN_HPP
