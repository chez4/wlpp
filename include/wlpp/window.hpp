// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/window.hpp
// Author - chez4 18/09/2020

#ifndef WLPP_WINDOW_HPP
#define WLPP_WINDOW_HPP

#include <concepts>

namespace wlpp {

/**
 * Constrains type to act as window object using underlying window API.
 *
 * @tparam T Type that will be constrained.
 *
 * @see window
 */
template<typename T>
concept is_window = requires(const T &t) {
    { t.show() } -> std::same_as<void>;
    { t.hide() } -> std::same_as<void>;
};

/**
 * Abstract window object using underlying window API.
 *
 * Acts as an "interface" to derived platform-specific implementations using
 * concepts.
 *
 * @note This class is only to be used for the platform-specific subclasses.
 *
 * @see win32_connection
 * @see xcb_connection
 */
template<class T>
class window {
protected:
    window() requires(is_window<T>) = default;

public:
    window(const window &) = delete;

    window(window &&) = delete;

    window &operator=(window) = delete;
};

}

#endif //WLPP_WINDOW_HPP
