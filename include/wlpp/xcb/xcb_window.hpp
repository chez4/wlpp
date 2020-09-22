/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_XCB_WINDOW_HPP
#define WLPP_XCB_WINDOW_HPP

#include <memory>

#include <xcb/xcb.h>

#include <wlpp/xcb/xcb_connection.hpp>

namespace wlpp {

class xcb_window {
private:
    xcb_window_t *p_window;

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
