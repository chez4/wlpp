/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/xcb/xcb_connection.hpp>

#include <iostream>
#include <string>
#include <utility>

#include <cstdint>

#include <xcb/xcb.h>

#include <window_api_error.hpp>
#include <wlpp/xcb/xcb_screen.hpp>
#include <wlpp/xcb/xcb_window.hpp>

namespace wlpp {

window *xcb_connection::find_window(xcb_window_t key) const
{
    for (window *w : windows)
        if (dynamic_cast<xcb_window *>(w)->get() == key) return w;

    return nullptr;
}

void xcb_connection::handle_event(const xcb_generic_event_t *event) const
{
    if (event != nullptr) {
        switch (event->response_type & ~0x80u) {
            case XCB_KEY_PRESS: {
                std::cout << "key press" << std::endl;
                auto *real_event = (xcb_key_press_event_t *) event;
                find_window(real_event->event)->key_press_event(real_event->detail);
                break;
            }

            case XCB_KEY_RELEASE: {
                std::cout << "key release" << std::endl;
                auto *real_event = (xcb_key_release_event_t *) event;
                find_window(real_event->event)->key_release_event(real_event->detail);
                break;
            }

            case XCB_BUTTON_PRESS: {
                std::cout << "button press" << std::endl;
                auto *real_event = (xcb_button_press_event_t *) event;
                find_window(real_event->event)->button_press_event(real_event->detail);
                break;
            }

            case XCB_BUTTON_RELEASE: {
                std::cout << "button release" << std::endl;
                auto *real_event = (xcb_button_release_event_t *) event;
                find_window(real_event->event)->button_release_event(real_event->detail);
                break;
            }

            case XCB_MOTION_NOTIFY: {
                std::cout << "motion notify" << std::endl;
                auto *real_event = (xcb_motion_notify_event_t *) event;
                find_window(real_event->event)->motion_notify_event(real_event->detail);
                break;
            }

            case XCB_ENTER_NOTIFY: {
                std::cout << "enter notify" << std::endl;
                auto *real_event = (xcb_enter_notify_event_t *) event;
                find_window(real_event->event)->enter_notify_event();
                break;
            }

            case XCB_LEAVE_NOTIFY: {
                std::cout << "leave notify" << std::endl;
                auto *real_event = (xcb_leave_notify_event_t *) event;
                find_window(real_event->event)->leave_notify_event();
                break;
            }

            case XCB_FOCUS_IN: {
                std::cout << "focus in" << std::endl;
                auto *real_event = (xcb_focus_in_event_t *) event;
                find_window(real_event->event)->focus_in_event();
                break;
            }

            case XCB_FOCUS_OUT: {
                std::cout << "focus out" << std::endl;
                auto *real_event = (xcb_focus_out_event_t *) event;
                find_window(real_event->event)->focus_out_event();
                break;
            }

            case XCB_KEYMAP_NOTIFY: {
                std::cout << "keymap notify" << std::endl;
                auto *real_event = (xcb_keymap_notify_event_t *) event;
                break;
            }

            case XCB_EXPOSE: {
                std::cout << "expose" << std::endl;
                auto *real_event = (xcb_expose_event_t *) event;
                find_window(real_event->window)->expose_event(real_event->x, real_event->y, real_event->width, real_event->height);
                break;
            }

            case XCB_GRAPHICS_EXPOSURE: {
                std::cout << "key press" << std::endl;
                auto *real_event = (xcb_graphics_exposure_event_t *) event;
                break;
            }

            case XCB_NO_EXPOSURE: {
                std::cout << "no exposure" << std::endl;
                auto *real_event = (xcb_no_exposure_event_t *) event;
                break;
            }

            case XCB_VISIBILITY_NOTIFY: {
                std::cout << "visibility notify" << std::endl;
                auto *real_event = (xcb_visibility_notify_event_t *) event;
                find_window(real_event->window)->visibility_notify_event();
                break;
            }

            case XCB_CREATE_NOTIFY: {
                std::cout << "create notify" << std::endl;
                auto *real_event = (xcb_create_notify_event_t *) event;
                find_window(real_event->window)->create_notify_event(real_event->x, real_event->y, real_event->width, real_event->height);
                break;
            }

            case XCB_DESTROY_NOTIFY: {
                std::cout << "destroy_notify" << std::endl;
                auto *real_event = (xcb_destroy_notify_event_t *) event;
                find_window(real_event->window)->destroy_notify_event();
                break;
            }

            case XCB_UNMAP_NOTIFY: {
                std::cout << "unmap notify" << std::endl;
                auto *real_event = (xcb_unmap_notify_event_t *) event;
                find_window(real_event->window)->unmap_notify_event();
                break;
            }

            case XCB_MAP_NOTIFY: {
                std::cout << "map notify" << std::endl;
                auto *real_event = (xcb_map_notify_event_t *) event;
                find_window(real_event->window)->map_notify_event();
                break;
            }

            case XCB_MAP_REQUEST: {
                std::cout << "map request" << std::endl;
                auto *real_event = (xcb_map_request_event_t *) event;
                find_window(real_event->window)->map_request_event();
                break;
            }

            case XCB_REPARENT_NOTIFY: {
                std::cout << "reparent notify" << std::endl;
                auto *real_event = (xcb_reparent_notify_event_t *) event;
                find_window(real_event->window)->reparent_notify_event();
                break;
            }

            case XCB_CONFIGURE_NOTIFY: {
                std::cout << "configure notify" << std::endl;
                auto *real_event = (xcb_configure_notify_event_t *) event;
                find_window(real_event->window)->configure_notify_event(real_event->x, real_event->y, real_event->width, real_event->height);
                break;
            }

            case XCB_CONFIGURE_REQUEST: {
                std::cout << "configure request" << std::endl;
                auto *real_event = (xcb_configure_request_event_t *) event;
                find_window(real_event->window)->configure_request_event();
                break;
            }

            case XCB_GRAVITY_NOTIFY: {
                std::cout << "gravity notify" << std::endl;
                auto *real_event = (xcb_gravity_notify_event_t *) event;
                find_window(real_event->window)->gravity_notify_event();
                break;
            }

            case XCB_RESIZE_REQUEST: {
                std::cout << "resize request" << std::endl;
                auto *real_event = (xcb_resize_request_event_t *) event;
                find_window(real_event->window)->resize_request_event(real_event->width, real_event->height);
                break;
            }

            case XCB_CIRCULATE_NOTIFY: {
                std::cout << "circulate notify" << std::endl;
                auto *real_event = (xcb_circulate_notify_event_t *) event;
                find_window(real_event->window)->circulate_notify_event();
                break;
            }

            case XCB_CIRCULATE_REQUEST: {
                std::cout << "circulate request" << std::endl;
                auto *real_event = (xcb_circulate_request_event_t *) event;
                find_window(real_event->window)->circulate_request_event();
                break;
            }

            case XCB_PROPERTY_NOTIFY: {
                std::cout << "property notify" << std::endl;
                auto *real_event = (xcb_property_notify_event_t *) event;
                find_window(real_event->window)->property_notify_event();
                break;
            }

            case XCB_SELECTION_CLEAR: {
                std::cout << "selection clear" << std::endl;
                auto *real_event = (xcb_selection_clear_event_t *) event;
                find_window(real_event->owner)->selection_clear_event();
                break;
            }

            case XCB_SELECTION_REQUEST: {
                std::cout << "selection request" << std::endl;
                auto *real_event = (xcb_selection_request_event_t *) event;
                find_window(real_event->requestor)->selection_request_event();
                break;
            }

            case XCB_SELECTION_NOTIFY: {
                std::cout << "selection notify" << std::endl;
                auto *real_event = (xcb_selection_notify_event_t *) event;
                find_window(real_event->requestor)->selection_notify_event();
                break;
            }

            case XCB_COLORMAP_NOTIFY: {
                std::cout << "colormap notify" << std::endl;
                auto *real_event = (xcb_colormap_notify_event_t *) event;
                find_window(real_event->window)->colormap_notify_event();
                break;
            }

            case XCB_CLIENT_MESSAGE: {
                std::cout << "client message" << std::endl;
                auto *real_event = (xcb_client_message_event_t *) event;
                find_window(real_event->window)->client_message_event();
                break;
            }

            case XCB_MAPPING_NOTIFY: {
                std::cout << "mapping notify" << std::endl;
                auto *real_event = (xcb_mapping_notify_event_t *) event;
                break;
            }

            default:
                std::cout << "unknown" << std::endl;
                break;
        }
    }
}

xcb_connection::xcb_connection()
    : screen_pref()
{
    conn = xcb_connect(nullptr, &screen_pref);
    setup = xcb_get_setup(conn);
}

xcb_connection::~xcb_connection()
{
    if (conn != nullptr) {
        xcb_disconnect(conn);
    }
}

xcb_connection::xcb_connection(xcb_connection &&other) noexcept
    : conn(other.conn)
    , screen_pref(other.screen_pref)
    , setup(other.setup)
{
    other.conn = nullptr;
    other.setup = nullptr;
}

xcb_connection &xcb_connection::operator=(xcb_connection other)
{
    if (this != &other) swap(*this, other);
    return *this;
}

void swap(xcb_connection &a, xcb_connection &b)
{
    std::swap(a.conn, b.conn);
    std::swap(a.screen_pref, b.screen_pref);
    std::swap(a.setup, b.setup);
}

xcb_connection_t *xcb_connection::get() const
{
    return conn;
}

void xcb_connection::flush() const
{
    xcb_flush(conn);
}

std::uint32_t xcb_connection::generate_id() const
{
    return xcb_generate_id(conn);
}

xcb_screen xcb_connection::get_screen(int num) const
{
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    int screens = iter.rem;
    while (iter.rem >= 0) {
        if (num == screens - iter.rem)
            return xcb_screen(*iter.data);
        xcb_screen_next(&iter);
    }

    throw window_api_error("Requested screen \"" + std::to_string(num) + "\" was not found on X connection");
}

xcb_screen xcb_connection::get_default_screen() const
{
    return get_screen(screen_pref);
}

void xcb_connection::register_window(window *wind)
{
    windows.push_back(wind);
}

void xcb_connection::unregister_window(window *wind)
{
    std::erase(windows, wind);
}

void xcb_connection::poll_events() const
{
    xcb_generic_event_t *event = xcb_poll_for_event(conn);
    handle_event(event);
    delete event;
}

void xcb_connection::wait_events() const
{
    xcb_generic_event_t *event = xcb_wait_for_event(conn);
    handle_event(event);
    delete event;
}

void xcb_connection::map_window(const xcb_window &wind) const
{
    xcb_map_window(conn, wind.get());
}

void xcb_connection::unmap_window(const xcb_window &wind) const
{
    xcb_unmap_window(conn, wind.get());
}

}
