//
// Created by hector on 01/11/22.
//

#include "Input.h"

std::unique_ptr<Input> Input::_instance;

Input::Input() {
}

Input::~Input() {}

bool Input::isPressed(Input::Key key) const{
    return _keys[key];
}

void Input::press(Input::Key key) {
    _keys[key] = true;
}

void Input::unpress(Input::Key key) {
    _keys[key] = false;
}

Input& Input::getInstance() {
    if (!_instance)
        _instance = std::make_unique<Input>();
    return *_instance;
}


