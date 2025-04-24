#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include "CharacterAnimation.h"

namespace sf
{
	class Sprite;
	class Text;
}

std::string toString(sf::Keyboard::Key key);
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);
void centerOrigin(CharacterAnimation& animation);
float toRadian(float degree);
float toDegree(float radian);
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);
int randomInt(int exclusiveMax);