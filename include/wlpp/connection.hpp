/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

/**
 * \file connection.hpp
 *
 * Header containing definition of abstract connection class.
 *
 * \see win32/win32_connection.hpp
 * \see xcb/xcb_connection.hpp
 *
 * \author Max Burns
 * \date 29/09/20
 */

#ifndef WLPP_CONNECTION_HPP
#define WLPP_CONNECTION_HPP

#include <memory>
#include <vector>

#include <wlpp/window.hpp>

namespace wlpp {

/**
 * Abstract class connection provides an interface to the window API.
 *
 * \details This class is to be inherited by an API-specific derived class, and cannot
 * be instantiated on it's own.
 */
class connection {
protected:
    std::vector<window *> windows;

public:
    virtual ~connection() = default;

    /**
     * Registers the window pointer to the event handler of this
     * class
     *
     * \details This function adds the passed in window to the list of window
     * pointers held by the class. When polling or waiting for events, the
     * event handler of a registered window may be called.
     *
     * \warning Do not pass a window pointer that is already registered.
     *
     * \param [in] wind window pointer to be registered.
     */
    virtual void register_window(window *wind) = 0;

    /**
     * Unregisters the window pointer to the event handler of this
     * class.
     *
     * \details This function removes the passed in window to the list of
     * window pointers held by the class.
     *
     * \warning Do not pass a window pointer that is already unregistered.
     *
     * \param [in] wind window pointer to be unregistered.
     */
    virtual void unregister_window(window *) = 0;

    /**
     * Executes the event handler for an event that may be at the front
     * of the event queue, and do nothing otherwise.
     *
     * \details This function will handle any connection or window events that
     * may be available at the front of the event queue. If no event is
     * available, the function will do nothing. If the event is associated with
     * a registered window, the event handler of that window will be called.
     */
    virtual void poll_events() const = 0;

    /**
     * Executes the event handler for an event that may be at the front
     * of the event queue, and wait otherwise.
     *
     * \details This function will handle any connection or window events that
     * may be available at the front of the event queue. If no event is
     * available, the function will wait for an event. If the event is
     * associated with a registered window, the event handler of that window
     * will be called.
     */
    virtual void wait_events() const = 0;
};

}

#endif //WLPP_CONNECTION_HPP
