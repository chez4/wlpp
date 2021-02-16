// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - include/wlpp/window_error.hpp
// Author - chez4 16/02/2021

#ifndef WLPP_WINDOW_ERROR_HPP
#define WLPP_WINDOW_ERROR_HPP

#include <exception>
#include <string>

namespace wlpp {

/**
 * Exception thrown when a window enters an exceptional state.
 *
 * @see window
 */
class window_error : public std::exception {
private:
    const std::string desc;

public:
    /**
     * Constructs exception.
     *
     * @param[in] desc Description of error.
     */
    explicit window_error(std::string desc);

    const char *what() const noexcept override;
};

}

#endif // WLPP_WINDOW_ERROR_HPP
