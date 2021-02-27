// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/connection.hpp
// Author - chez4 18/09/2020

#ifndef WLPP_CONNECTION_HPP
#define WLPP_CONNECTION_HPP

#include <concepts>

namespace wlpp {

/**
 * Constrains type to implement connection to underlying window API.
 *
 * @tparam T Type that will be constrained.
 *
 * @see connection
 */
template<typename T>
concept is_connection = requires(const T &t) {
    { t.send() } -> std::same_as<void>;
    { t.wait_events() } -> std::same_as<void>;
    { t.poll_events() } -> std::same_as<void>;
    { t.has_closed() } -> std::same_as<bool>;
};

/**
 * Abstract connection to underlying window API.
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
class connection {
protected:
    connection() requires(is_connection<T>) = default;

public:
    connection(const connection &) = delete;

    connection(connection &&) = delete;

    connection &operator=(connection) = delete;
};

}

#endif // WLPP_CONNECTION_HPP
