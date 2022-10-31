//
// Created by hector on 31/10/22.
//

#include "App.h"
#include "Renderer.h"
#include <iostream>
#include "FileReader.h"

std::unique_ptr<World> App::_world;

App::App() {
    _running = true;
}

App::~App() {}

int App::onExecute() {
    if(onInit() == false) {
        return -1;
    }

    SDL_Event Event;


    while(_running) {
        while(SDL_PollEvent(&Event)) {
            onEvent(&Event);
        }

        //onLoop();

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

    if (renderer.getSDLWindow() == NULL)
        return false;
    if (renderer.getSDLRenderer() == NULL)
        return false;

    std::cout << "starting..." << std::endl;

    return true;
}

void App::onEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_QUIT:
            exit();
            break;
    }
}

void App::onRender() {
    const Renderer & rend = Renderer::getInstance();
}

void App::onCleanup() {
    SDL_Quit();
    std::cout << "cleanup app" <<std::endl;
}

void App::exit() {
    std::cout << "exiting..." << std::endl;
    _running = false;
}

World & App::getWorld() {
    if (!_world)
        _world = std::make_unique<World>();
    return *_world;
}


