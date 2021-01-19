// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - tests/window.cpp
// Author - chez4 10/11/2020

#include <wlpp/xcb/xcb_connection.hpp>

int main()
{
    wlpp::xcb_connection server;

    server.send();

    return 0;
}
