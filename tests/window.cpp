// Copyright (C) 2020-2021 Max Burns
// See LICENSE for more information
// wlpp   - tests/window.cpp
// Author - chez4 10/11/2020

#include <memory>

#include <wlpp/win32/win32_connection.hpp>
#include <wlpp/win32/win32_window.hpp>

int main()
{
    std::shared_ptr<wlpp::win32_connection> server = std::make_shared<wlpp::win32_connection>();

    wlpp::win32_window window(server, "Test Window");

    window.show();
    while (!server->has_closed()) {
        server->poll_events();
    }
    window.hide();

    return 0;
}
