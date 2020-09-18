#ifndef WLPP_WINDOW_HPP
#define WLPP_WINDOW_HPP

#include <memory>

#include <xcb/xcb.h>

#include "connection.hpp"

namespace wlpp {

class window {
    xcb_window_t *p_window;

    std::shared_ptr<connection> server;

public:
    window(std::shared_ptr<connection>);

    ~window();

    window(const window &) = delete;

    window(window &&) noexcept;

    window &operator=(window);

    friend void swap(window &, window &);
};

}

#endif //WLPP_WINDOW_HPP
