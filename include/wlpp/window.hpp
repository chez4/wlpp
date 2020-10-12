/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WINDOW_HPP
#define WLPP_WINDOW_HPP

#include <string>

#include <cstdint>

namespace wlpp {

class window {
protected:
    bool quit;

public:
    window();

    virtual ~window() = default;

    virtual void set_title(const std::string &) const = 0;

    virtual void show() const = 0;

    virtual void hide() const = 0;

    virtual bool has_closed() const = 0;

    // TODO: Documentation

    virtual void key_press_event(std::uint8_t, std::uint16_t, std::uint16_t) = 0;

    virtual void key_release_event(std::uint8_t, std::uint16_t, std::uint16_t) = 0;

    virtual void button_press_event(std::uint8_t, std::uint16_t, std::uint16_t) = 0;

    virtual void button_release_event(std::uint8_t, std::uint16_t, std::uint16_t) = 0;

    virtual void motion_notify_event(std::uint8_t, std::uint16_t, std::uint16_t) = 0;

    virtual void enter_notify_event(std::uint16_t, std::uint16_t) = 0;

    virtual void leave_notify_event(std::uint16_t, std::uint16_t) = 0;

    virtual void focus_in_event() = 0;

    virtual void focus_out_event() = 0;

    virtual void expose_event(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t) = 0;

    virtual void visibility_notify_event() = 0;

    virtual void create_notify_event(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t) = 0;

    virtual void destroy_notify_event() = 0;

    virtual void unmap_notify_event() = 0;

    virtual void map_notify_event() = 0;

    virtual void reparent_notify_event(std::uint16_t, std::uint16_t) = 0;

    virtual void configure_notify_event(std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t) = 0;

    virtual void resize_request_event(std::uint16_t, std::uint16_t) = 0;

    virtual void selection_clear_event() = 0;

    virtual void selection_request_event() = 0;

    virtual void selection_notify_event() = 0;

    virtual void colormap_notify_event() = 0;

    virtual void client_message_event() = 0;
};

}

#endif //WLPP_WINDOW_HPP
