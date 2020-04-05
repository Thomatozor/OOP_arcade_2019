/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** snake
*/

#include <iostream>
#include "Snake.hpp"

Snake::Snake(std::vector<arcade::Element> &map):
    _position({5, 5}), _size(1), _map(map), _alive(true)
{
    _elements.push_back({pathSprite, arcade::GREEN, _position, arcade::Rect{{0, 0}, {0,0}}});
    _elements.push_back({pathSprite, arcade::GREEN, {_position.x - 1, _position.y}, arcade::Rect{{0, 0}, {0, 0}}});
    _elements.push_back({pathSprite, arcade::GREEN, {_position.x - 2, _position.y}, arcade::Rect{{0, 0}, {0, 0}}});
    _elements.push_back({pathSprite, arcade::GREEN, {_position.x - 3, _position.y}, arcade::Rect{{0, 0}, {0, 0}}});
    _elements.push_back({pathSprite, arcade::GREEN, {_position.x - 3, _position.y}, arcade::Rect{{0, 0}, {0, 0}}});
}

Snake::~Snake()
{}

std::vector<arcade::Element> const& Snake::getElements() const
{
    return (_elements);
}

void Snake::Move()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::duration<double> laps = now - _prevMove;

    if (laps.count() >= 0.12) {
        if (!canMove(Point{_direction.x, _direction.y})) {
            return;
        }
        if (_direction.x != 0 || _direction.y != 0) {
            moveTail();
        }
        _position.x += _direction.x;
        _position.y += _direction.y;
        _elements[0].position.x = _position.x;
        _elements[0].position.y = _position.y;
        _prevMove = now;
    }
}

void Snake::setDirection(Point const &direction)
{
    if (!canMove(Point{direction.x, direction.y}))
        return;
    _direction = direction;
}

bool Snake::canMove(Point offset)
{
    Point aTop = {_position.x + offset.x, _position.y + offset.y};
    Point aBottom = {_position.x + offset.x + 1.0f, _position.y + offset.y + 1.0f};
    Point bTop;
    Point bBottom;

    for (auto it = _map.begin(); it != _map.end(); it++) {
        bTop = {it->position.x, it->position.y};
        bBottom = {it->position.x + 1.0, it->position.y + 1.0};
        if (aTop.x < bBottom.x && aBottom.x > bTop.x && aTop.y < bBottom.y && aBottom.y > bTop.y) {
            return (false);
        }
    }
    return (true);
}

void Snake::addTail()
{
    _elements.push_back({pathSprite, arcade::GREEN, _lastTailPos, arcade::Rect{{0, 0}, {0, 0}}});
}

void Snake::moveTail()
{
    Point posSave;
    Point prevPos = _elements[0].position;

    for (auto it = _elements.begin(); it != _elements.end(); it++) {
        posSave = it->position;
        it->position = prevPos;
        prevPos = posSave;
    }
    _lastTailPos = posSave;
}
