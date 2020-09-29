/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WINDOW_HPP
#define WLPP_WINDOW_HPP

namespace wlpp {

class window {
public:
    virtual ~window() = default;

    virtual void poll_events() const = 0;

    virtual void wait_events() const = 0;

    virtual void show() const = 0;

    virtual void hide() const = 0;

    virtual bool has_closed() const = 0;
};

}

#endif //WLPP_WINDOW_HPP
