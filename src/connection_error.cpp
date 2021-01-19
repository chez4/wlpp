// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - src/connection_error.cpp
// Author - chez4 18/01/2021

#include <wlpp/connection_error.hpp>

#include <string>
#include <utility>

namespace wlpp {

connection_error::connection_error(std::string desc)
    : desc(std::move(desc))
{
}

const char *connection_error::what() const noexcept
{
    return desc.c_str();
}

}
