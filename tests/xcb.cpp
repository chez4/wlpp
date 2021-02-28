// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - tests/xcb.cpp
// Author - chez4 27/02/2021

#include <memory>

#include <wlpp/xcb/xcb_connection.hpp>
#include <wlpp/xcb/xcb_window.hpp>

int main()
{
    std::shared_ptr<wlpp::xcb_connection> server = std::make_shared<wlpp::xcb_connection>();

    wlpp::xcb_window window(server, "Test Window");

    window.show();
    server->send();
    while (!server->has_closed()) {
        server->poll_events();
    }
    window.hide();
    server->send();

    return 0;
}
