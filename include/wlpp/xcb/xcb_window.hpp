/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_XCB_WINDOW_HPP
#define WLPP_XCB_WINDOW_HPP

#include <concepts>
#include <memory>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/window.hpp>
#include <wlpp/xcb/xcb_connection.hpp>
#include <wlpp/xcb/xcb_screen.hpp>

namespace wlpp {

template<typename T>
concept str_char = requires { std::same_as<T, char> || std::same_as<T, wchar_t> || std::same_as<T, char8_t> || std::same_as<T, char16_t> || std::same_as<T, char32_t>; };

class xcb_window : public window {
private:
    xcb_window_t wind;

    std::shared_ptr<xcb_connection> server;

    template<str_char T>
    void prepend_property(xcb_atom_enum_t property, const T *str) const
    {
        xcb_change_property(server->get(), XCB_PROP_MODE_PREPEND, wind, property, XCB_ATOM_STRING, sizeof(T) * 8, std::char_traits<T>::length(str), str);
    }

    template<str_char T>
    void replace_property(xcb_atom_enum_t property, const T *str) const
    {
        xcb_change_property(server->get(), XCB_PROP_MODE_REPLACE, wind, property, XCB_ATOM_STRING, sizeof(T) * 8, std::char_traits<T>::length(str), str);
    }

    template<str_char T>
    void append_property(xcb_atom_enum_t property, const T *str) const
    {
        xcb_change_property(server->get(), XCB_PROP_MODE_APPEND, wind, property, XCB_ATOM_STRING, sizeof(T) * 8, std::char_traits<T>::length(str), str);
    }

public:
    xcb_window(std::shared_ptr<xcb_connection>, const xcb_screen &, std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t);
    xcb_window(std::shared_ptr<xcb_connection>, const xcb_screen &, std::uint16_t, std::uint16_t, std::uint16_t, std::uint16_t);
    xcb_window(std::shared_ptr<xcb_connection>, const xcb_screen &, std::uint16_t, std::uint16_t);

    ~xcb_window();

    xcb_window(const xcb_window &) = delete;

    xcb_window(xcb_window &&) noexcept;

    xcb_window &operator=(xcb_window);

    friend void swap(xcb_window &, xcb_window &);

    xcb_window_t get() const;

    void poll_events() const override;

    void wait_events() const override;

    void show() const override;

    void hide() const override;
};

}

#endif //WLPP_XCB_WINDOW_HPP
