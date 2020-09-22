/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WINDOW_API_ERROR_HPP
#define WLPP_WINDOW_API_ERROR_HPP

#include <exception>
#include <string>

namespace wlpp {

class window_api_error : public std::exception {
private:
    const std::string desc;

public:
    explicit window_api_error(std::string);

    const char *what() const noexcept override;
};

}

#endif //WLPP_WINDOW_API_ERROR_HPP
