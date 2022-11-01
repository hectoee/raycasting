//
// Created by hector on 01/11/22.
//

#ifndef RAYCASTING_INPUT_H
#define RAYCASTING_INPUT_H

#include <memory>

class Input {
private:
    bool _keys[4] = {false, false, false, false};
                    // Z     Q      S      D
    static std::unique_ptr<Input> _instance;

public:
    enum Key{
        Z = 0, Q, S, D
    };

    Input();
    virtual ~Input();
    Input(const Input&) = delete;
    Input & operator=(const Input&) = delete;

    bool isPressed(Key) const;

    void press(Key);

    void unpress(Key);

    static Input & getInstance();



};


#endif //RAYCASTING_INPUT_H
