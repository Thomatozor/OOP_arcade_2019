/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include <string>
#include <chrono>
#include "Element.hpp"
#include "IBehavior.hpp"
#include "SpriteManager.hpp"

class Entity {
    public:
        Entity(std::vector<arcade::Element> &map);
        Entity(
            Point direction,
            Point position,
            arcade::Element &element,
            std::vector<arcade::Element> &map
        );

        Point getDirection(void) const;
        const Point &getPosition(void) const;
        bool isAlive(void) const;
        const arcade::Element &getElement(void) const;

        void setDirection(Point direction);
        void setPosition(const Point &position);
        void setStatus(bool isAlive);
        void setElement(arcade::Element &element);

        bool canMove(Point offset);
        virtual void move(void);

    protected:
        bool _isAlive;
        Point _direction;
        Point _position;
        arcade::Element _element;
        std::vector<arcade::Element> &_map;
        SpriteManager _spriteManager;
        std::chrono::time_point<std::chrono::system_clock> _prevMove;
};

#endif /* !ENTITY_HPP_ */
