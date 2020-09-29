/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#include <wlpp/win32/win_32_connection.hpp>

#include <winuser.h>

namespace wlpp {

win32_connection::win32_connection()
    : inst(GetModuleHandle(nullptr))
{
}

void win32_connection::poll_events() const
{

}

void win32_connection::wait_events() const
{

}

}
