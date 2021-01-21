// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/connection_error.hpp
// Author - chez4 18/01/2021

#ifndef WLPP_CONNECTION_ERROR_HPP
#define WLPP_CONNECTION_ERROR_HPP

#include <exception>
#include <string>

namespace wlpp {

/**
 * Exception thrown when a connection enters an exceptional state.
 *
 * @see connection
 */
class connection_error : public std::exception {
private:
    const std::string desc;

public:
    /**
     * Constructs exception.
     *
     * @param[in] desc Description of error.
     */
    explicit connection_error(std::string desc);

    const char *what() const noexcept override;
};

}

#endif // WLPP_CONNECTION_ERROR_HPP
