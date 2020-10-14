/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

/**
 * \file connection.hpp
 *
 * \brief Header containing definition of abstract connection class.
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
 * \brief Abstract class connection provides an interface to the window API.
 *
 * This class is to be inherited by an API-specific derived class, and cannot
 * be instantiated on it's own.
 *
 * \see win32_connection
 * \see xcb_connection
 *
 * \author Max Burns
 * \date 29/09/20
 */
class connection {
protected:
    std::vector<window *> windows;

public:
    virtual ~connection() = default;

    /**
     * \brief Registers the \ref window pointer to the event handler of this
     * class
     *
     * This function adds the passed in \ref window to the list of \ref window
     * pointers held by the class. When polling or waiting for events, the
     * event handler of a registered window may be called.
     *
     * \warning Do not pass a \ref window pointer that is already registered.
     *
     * \param[in] wind \ref window pointer to be registered.
     *
     * \see window
     * \see poll_events()
     * \see wait_events()
     *
     * \author Max Burns
     * \date 29/09/20
     */
    virtual void register_window(window *wind) = 0;

    /**
     * \brief Unregisters the \ref window pointer to the event handler of this
     * class.
     *
     * This function removes the passed in \ref window to the list of \ref
     * window pointers held by the class.
     *
     * \warning Do not pass a \ref window pointer that is already unregistered.
     *
     * \param[in] wind \ref window pointer to be unregistered.
     *
     * \see window
     * \see poll_events()
     * \see wait_events()
     *
     * \author Max Burns
     * \date 29/09/20
     */
    virtual void unregister_window(window *) = 0;

    /**
     * \brief Executes the event handler for an event that may be at the front
     * of the event queue, and do nothing otherwise.
     *
     * This function will handle any \ref connection or \ref window events that
     * may be available at the front of the event queue. If no event is
     * available, the function will do nothing. If the event is associated with
     * a registered \ref window, the event handler of that \ref window will be
     * called.
     *
     * \see register_window()
     * \see window
     *
     * \author Max Burns
     * \date 29/09/20
     */
    virtual void poll_events() const = 0;

    /**
     * \brief Executes the event handler for an event that may be at the front
     * of the event queue, and wait otherwise.
     *
     * This function will handle any \ref connection or \ref window events that
     * may be available at the front of the event queue. If no event is
     * available, the function will wait for an event. If the event is
     * associated with a registered \ref window, the event handler of that \ref
     * window will be called.
     *
     * \see register_window()
     * \see window
     *
     * \author Max Burns
     * \date 29/09/20
     */
    virtual void wait_events() const = 0;
};

}

#endif //WLPP_CONNECTION_HPP
