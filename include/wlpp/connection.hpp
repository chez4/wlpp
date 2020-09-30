/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_CONNECTION_HPP
#define WLPP_CONNECTION_HPP

#include <memory>
#include <vector>

#include <wlpp/window.hpp>

namespace wlpp {

class connection {
protected:
    std::vector<const window *> windows;

public:
    virtual ~connection() = default;

    virtual void register_window(const window *) = 0;

    virtual void unregister_window(const window *) = 0;

    virtual void poll_events() const = 0;

    virtual void wait_events() const = 0;
};

}

#endif //WLPP_CONNECTION_HPP
