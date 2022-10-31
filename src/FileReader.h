//
// Created by hector on 31/10/22.
//

#ifndef RAYCASTING_FILEREADER_H
#define RAYCASTING_FILEREADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using Map = std::vector<std::vector<int>>;

class FileReader {
public:
    static Map readMap(const std::string& filePath) {
        Map v;
        char c;
        int line = 0;
        v.push_back(*(new std::vector<int>));
        std::fstream in(filePath, std::fstream::in);
        if (in.is_open()) {
            while (in.get(c)) {
                if (c == ' ') continue;
                if (c == '\n') {
                    v.push_back(*(new std::vector<int>));
                    line ++;
                }
                else v[line].push_back(c - 48);
            }
        }

        return v;
    }
};


#endif //RAYCASTING_FILEREADER_H
