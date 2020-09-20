#ifndef WLPP_XCB_WINDOW_HPP
#define WLPP_XCB_WINDOW_HPP

#include <memory>

#include <xcb/xcb.h>

#include "xcb_connection.hpp"

namespace wlpp {

class xcb_window {
    xcb_window_t *window;

    std::shared_ptr<xcb_connection> server;

public:
    xcb_window(std::shared_ptr<xcb_connection>);

    ~xcb_window();

    xcb_window(const xcb_window &) = delete;

    xcb_window(xcb_window &&) noexcept;

    xcb_window &operator=(xcb_window);

    friend void swap(xcb_window &, xcb_window &);
};

}

#endif //WLPP_XCB_WINDOW_HPP
