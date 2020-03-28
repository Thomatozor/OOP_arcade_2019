/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** LibCacaDisplay
*/

#include <iostream>
#include "LibCacaDisplay.hpp"

extern "C" LibCacaDisplay *createObject()
{
    return (new LibCacaDisplay);
}

LibCacaDisplay::LibCacaDisplay() :
    _display(caca_create_display(NULL)), _canvas(caca_get_canvas(_display))
{}

LibCacaDisplay::~LibCacaDisplay()
{
    caca_free_display(_display);
}

void LibCacaDisplay::display(std::vector<arcade::Element> &elements)
{
    caca_clear_canvas(_canvas);
    for (auto it = elements.begin(); it != elements.end(); it++) {
        setColor(it->color);
        caca_fill_box(_canvas, it->position.x * 2, it->position.y * 2, 2, 2, (uint32_t)0x00002588);
        caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
    }
    caca_refresh_display(_display);
}

std::vector<arcade::Inputs> LibCacaDisplay::getInputs(void)
{
    std::vector<arcade::Inputs> inputs;
    caca_event_t ev;
    caca_event_type type;

    caca_get_event(_display, CACA_EVENT_KEY_PRESS | CACA_EVENT_QUIT, &ev, 10000);
    type = caca_get_event_type(&ev);
    if (type == CACA_EVENT_QUIT) {
        inputs.push_back(arcade::QUIT);
        return (inputs);
    }
    inputs.push_back(getInput(ev));
    return (inputs);
}

arcade::Inputs LibCacaDisplay::getInput(caca_event_t &ev)
{
    int key;

    key = caca_get_event_key_ch(&ev);
    if (key == 'q')
        return (arcade::QUIT);
    for (int i = 0; i < 4; i++) {
        if (key == inputsPair[i].second) {
            return (inputsPair[i].first);
        }
    }
    return (arcade::UNDEFINED);
}

void LibCacaDisplay::setColor(arcade::color color)
{
    for (int i = 0; i < 5; i++) {
        if (colorsPair[i].first == color) {
            caca_set_color_ansi(_canvas, colorsPair[i].second, CACA_BLACK);
        }
    }
}