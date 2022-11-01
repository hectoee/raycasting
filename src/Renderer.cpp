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

void Renderer::clear() const {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
}

void Renderer::renderPresent() const {
    SDL_RenderPresent(_renderer);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, Color& c) const {
    SDL_SetRenderDrawColor(_renderer, c[0], c[1], c[2], SDL_ALPHA_OPAQUE);
    if (SDL_RenderDrawLine(_renderer, x1, y1, x2, y2) < 0) {
        std::cout << "Error when drawing line" << std::endl;
        exit(-1);
    }
}

void Renderer::drawSquare(int x, int y, int height, Color& c) const {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = height;
    rect.h = height;

    SDL_SetRenderDrawColor(_renderer, c[0], c[1], c[2], SDL_ALPHA_OPAQUE);
    if( SDL_RenderDrawRect(_renderer, &rect) < 0) {
        std::cout << "Error when drawing rect" << std::endl;
        exit(-1);
    }
}