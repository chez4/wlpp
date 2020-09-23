/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_XCB_WINDOW_HPP
#define WLPP_XCB_WINDOW_HPP

#include <memory>

#include <xcb/xcb.h>

#include <wlpp/window.hpp>
#include <wlpp/xcb/xcb_connection.hpp>
#include <wlpp/xcb/xcb_screen.hpp>

namespace wlpp {

class xcb_window : public window {
private:
    xcb_window_t wind;

    std::shared_ptr<xcb_connection> server;

public:
    xcb_window(std::shared_ptr<xcb_connection>, const xcb_screen &);

    ~xcb_window();

    xcb_window(const xcb_window &) = delete;

    xcb_window(xcb_window &&) noexcept;

    xcb_window &operator=(xcb_window);

    friend void swap(xcb_window &, xcb_window &);

    xcb_window_t get() const;

    void show() const override;

    void hide() const override;
};

}

#endif //WLPP_XCB_WINDOW_HPP
