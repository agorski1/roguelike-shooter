#include "Portal.h"
#include "Category.h"
#include <iostream>

Portal::Portal(const sf::Texture& texture)
    : AnimatedNode(texture)
    , mActive(true)
{
}

unsigned int Portal::getCategory() const
{
    return Category::Portal;
}

void Portal::setActive(bool active)
{
    mActive = active;
}

bool Portal::isActive() const
{
    return mActive;
}

void Portal::printHello() const
{
    std::cout << "Hello from Portal!" << std::endl;
}


