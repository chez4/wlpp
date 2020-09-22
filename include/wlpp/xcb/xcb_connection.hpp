#ifndef WLPP_XCB_CONNECTION_HPP
#define WLPP_XCB_CONNECTION_HPP

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/xcb/xcb_screen.hpp>

namespace wlpp {

class xcb_connection {
private:
    xcb_connection_t *connection;
    int *screen_pref;

    const xcb_setup_t *setup;

public:
    xcb_connection();

    ~xcb_connection();

    xcb_connection(const xcb_connection &) = delete;

    xcb_connection(xcb_connection &&) noexcept;

    xcb_connection &operator=(xcb_connection);

    friend void swap(xcb_connection &, xcb_connection &);

    xcb_connection_t *get() const;

    std::uint32_t generate_id() const;

    xcb_screen get_screen(int) const;
};

}

#endif //WLPP_XCB_CONNECTION_HPP
