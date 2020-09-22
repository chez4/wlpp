/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/window_api_error.hpp>

#include <exception>
#include <string>

namespace wlpp {

window_api_error::window_api_error(std::string message)
    : std::exception()
    , desc(std::move(message))
{
}

const char *window_api_error::what() const noexcept
{
    return desc.c_str();
}

}
