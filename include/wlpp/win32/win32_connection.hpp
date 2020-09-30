/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WIN32_CONNECTION_HPP
#define WLPP_WIN32_CONNECTION_HPP

#include <windef.h>

#include <wlpp/connection.hpp>

namespace wlpp {

class win32_connection : connection {
private:
    HINSTANCE inst;

public:
    win32_connection();

    void poll_events() const override;

    void wait_events() const override;
};

}

#endif //WLPP_WIN32_CONNECTION_HPP
