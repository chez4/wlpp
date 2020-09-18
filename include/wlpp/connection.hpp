#ifndef WLPP_CONNECTION_HPP
#define WLPP_CONNECTION_HPP

#include <cstdint>

#include <xcb/xcb.h>

#include "screen.hpp"

namespace wlpp {

class connection {
    xcb_connection_t *p_connection;
    int *p_screen_pref;

    const xcb_setup_t *p_setup;

public:
    connection();

    ~connection();

    connection(const connection &) = delete;

    connection(connection &&) noexcept;

    connection &operator=(connection);

    friend void swap(connection &, connection &);

    std::uint32_t generate_id() const;

    screen get_screen(int) const;
};

}

#endif //WLPP_CONNECTION_HPP
