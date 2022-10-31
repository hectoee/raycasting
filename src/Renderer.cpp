//
// Created by hector on 31/10/22.
//

#include "Renderer.h"

std::unique_ptr<Renderer> Renderer::_instance;

Renderer::Renderer() {
    SDL_CreateWindowAndRenderer(_WIN_WIDTH, _WIN_HEIGHT,SDL_WINDOW_OPENGL, &_window, &_renderer);
    SDL_SetWindowTitle(_window, "Raycasting application");
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

const Renderer & Renderer::getInstance() {
    if (!_instance) {
        _instance = std::make_unique<Renderer>();
    }
    return * _instance;
}
