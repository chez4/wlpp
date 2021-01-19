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
concept connectable = requires(const T &t) { { t.send() } -> std::same_as<void>; };

/**
 * Abstract connection to underlying window API.
 *
 * Acts as an "interface" to derived platform-specific implementations using
 * concepts.
 *
 * @note This class is only to be used for the platform-specific subclasses.
 *
 * @see xcb_connection
 */
template<class T>
class connection {
protected:
    connection() requires(connectable<T>) = default;

public:
    connection(const connection &) = delete;

    connection(connection &&) = delete;

    connection &operator=(connection) = delete;
};

}

#endif // WLPP_CONNECTION_HPP
