// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/window_error.cpp
// Author - chez4 16/02/2021

#include <wlpp/window_error.hpp>

#include <string>
#include <utility>

namespace wlpp {

window_error::window_error(std::string desc)
    : desc(std::move(desc))
{
}

const char *window_error::what() const noexcept
{
    return desc.c_str();
}

}
