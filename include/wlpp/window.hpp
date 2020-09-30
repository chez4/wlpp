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

    virtual void show() const = 0;

    virtual void hide() const = 0;

    virtual bool has_closed() const = 0;

    virtual void key_press_event() const = 0;

    virtual void key_release_event() const = 0;

    virtual void button_press_event() const = 0;

    virtual void button_release_event() const = 0;

    virtual void motion_notify_event() const = 0;

    virtual void enter_notify_event() const = 0;

    virtual void leave_notify_event() const = 0;

    virtual void focus_in_event() const = 0;

    virtual void focus_out_event() const = 0;

    virtual void expose_event() const = 0;

    virtual void visibility_notify_event() const = 0;

    virtual void create_notify_event() const = 0;

    virtual void destroy_notify_event() const = 0;
};

}

#endif //WLPP_WINDOW_HPP
