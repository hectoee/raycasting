//
// Created by hector on 31/10/22.
//

#include "App.h"


std::unique_ptr<World> App::_world;

App::App() {
    _running = true;
    _world = std::make_unique<World>();
}

App::~App() {}

int App::onExecute() {
    if(onInit() == false) {
        return -1;
    }

    SDL_Event Event;

    Uint32 tick = 40; // 40 ms
    Uint32 oldTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    while(_running) {
        if (((currentTime = SDL_GetTicks()) - oldTime) < tick) {
            continue;
        }
        oldTime = currentTime;
        while(SDL_PollEvent(&Event)) {
            onEvent(&Event);
        }

        onLoop();

        onRender();

    }


    onCleanup();

    return 0;
}

bool App::onInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 ){
        return false;
    }

    const Renderer & renderer = Renderer::getInstance();
    Input::getInstance();

    if (renderer.getSDLWindow() == NULL)
        return false;
    if (renderer.getSDLRenderer() == NULL)
        return false;

    std::cout << "starting..." << std::endl;

    return true;
}

void App::onEvent(SDL_Event* event) {
    Input& input = Input::getInstance();
    switch (event->type) {
        case SDL_QUIT:
            exit();
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == 'z')
                input.press(Input::Z);
            if (event->key.keysym.sym == 'q')
                input.press(Input::Q);
            if (event->key.keysym.sym == 's')
                input.press(Input::S);
            if (event->key.keysym.sym == 'd')
                input.press(Input::D);
            break;
        case SDL_KEYUP:
            if (event->key.keysym.sym == 'z')
                input.unpress(Input::Z);
            if (event->key.keysym.sym == 'q')
                input.unpress(Input::Q);
            if (event->key.keysym.sym == 's')
                input.unpress(Input::S);
            if (event->key.keysym.sym == 'd')
                input.unpress(Input::D);
            break;
        default:
            break;
    }
}

void App::onLoop() {
    const Input& input = Input::getInstance();
    if (input.isPressed(Input::Z))
        _world->moveUP();
    if (input.isPressed(Input::Q))
        _world->turnLEFT();
    if (input.isPressed(Input::S))
        _world->moveDOWN();
    if (input.isPressed(Input::D))
        _world->turnRIGHT();
}

void App::onRender() {
    const Renderer & renderer = Renderer::getInstance();
    renderer.clear();

    _world->render();

    renderer.renderPresent();
}

void App::onCleanup() {
    SDL_Quit();
    std::cout << "cleanup app" <<std::endl;
}

void App::exit() {
    std::cout << "exiting..." << std::endl;
    _running = false;
}