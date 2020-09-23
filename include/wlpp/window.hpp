/*
 * wlpp Copyright 2020 Max Burns
 * See LICENSE for more information.
 */

#ifndef WLPP_WINDOW_HPP
#define WLPP_WINDOW_HPP

namespace wlpp {

class window {
private:

public:
    virtual void show() const = 0;

    virtual void hide() const = 0;
};

}

#endif //WLPP_WINDOW_HPP
