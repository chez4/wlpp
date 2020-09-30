/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_XCB_CONNECTION_HPP
#define WLPP_XCB_CONNECTION_HPP

#include <vector>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/connection.hpp>

namespace wlpp {

class xcb_screen;
class xcb_window;

class xcb_connection : connection {
private:
    xcb_connection_t *conn;
    int screen_pref;

    const xcb_setup_t *setup;

    window *find_window(xcb_window_t) const;

    void handle_event(const xcb_generic_event_t *) const;

public:
    xcb_connection();

    ~xcb_connection() override;

    xcb_connection(const xcb_connection &) = delete;

    xcb_connection(xcb_connection &&) noexcept;

    xcb_connection &operator=(xcb_connection);

    friend void swap(xcb_connection &, xcb_connection &);

    xcb_connection_t *get() const;

    void flush() const;

    std::uint32_t generate_id() const;

    xcb_screen get_screen(int) const;

    xcb_screen get_default_screen() const;

    void register_window(window *) override;

    void unregister_window(window *) override;

    void poll_events() const override;

    void wait_events() const override;

    void map_window(const xcb_window &) const;

    void unmap_window(const xcb_window &) const;
};

}

#endif //WLPP_XCB_CONNECTION_HPP
