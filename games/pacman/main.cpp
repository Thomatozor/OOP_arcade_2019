/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include <dlfcn.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

using namespace std;

bool checkQuit(vector<arcade::inputs> inputs)
{
    if (inputs.size() == 0)
        return (false);
    for (auto it = inputs.begin(); it != inputs.end(); it++) {
        if (*it == arcade::QUIT)
            return (true);
    }
    return (false);
}

chrono::duration<double> getElapsedTime(
    chrono::time_point<chrono::system_clock> start,
    chrono::time_point<chrono::system_clock> end
)
{
    chrono::duration<double> elapsedSeconds = end - start;

    return (elapsedSeconds);
}

int main(void)
{
    void *graphHandle = dlopen("./../../lib/SFML/lib_arcade_sfml.so", RTLD_LAZY);
    void *gameHandle = dlopen("./lib_arcade_pacman.so", RTLD_LAZY);

    arcade::inputs key = arcade::PAUSE;

    arcade::IDisplayModule *(*fptr)();
    arcade::IDisplayModule *displayModule;

    arcade::IGameModule *(*fptr2)();
    arcade::IGameModule *gameModule;

    fptr = (arcade::IDisplayModule *(*)()) dlsym(graphHandle, "createObject");

    fptr2 = (arcade::IGameModule *(*)()) dlsym(gameHandle, "createGame");

    displayModule = fptr();

    gameModule = fptr2();

    chrono::time_point<chrono::system_clock> now;
    chrono::time_point<chrono::system_clock> last = chrono::system_clock::now();

    gameModule->initGame();

    while (checkQuit(displayModule->getInputs()) != true) {
        now = chrono::system_clock::now();
        if (getElapsedTime(last, now).count() > 0.5) {
            std::vector<arcade::Element> elements = gameModule->getElements();
            displayModule->display(elements);
            last = chrono::system_clock::now();
        }
    }

    delete(displayModule);
    delete(gameModule);
    dlclose(graphHandle);
    dlclose(gameHandle);
    return (0);
}