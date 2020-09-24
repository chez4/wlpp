/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_XCB_WINDOW_HPP
#define WLPP_XCB_WINDOW_HPP

#include <memory>

#include <cstdint>

#include <xcb/xcb.h>

#include <wlpp/window.hpp>
#include <wlpp/xcb/xcb_connection.hpp>
#include <wlpp/xcb/xcb_screen.hpp>

namespace wlpp {

class xcb_window : public window {
private:
    xcb_window_t wind;

    std::shared_ptr<xcb_connection> server;

    template <typename T>
    void change_property(const xcb_atom_enum_t &property, const xcb_atom_enum_t &type, T data) const
    {
        xcb_change_property(server->get(), XCB_PROP_MODE_REPLACE, wind, property, type, 8, sizeof(T), data);
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

    void show() const override;

    void hide() const override;
};

}

#endif //WLPP_XCB_WINDOW_HPP
