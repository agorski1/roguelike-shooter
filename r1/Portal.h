#pragma once
#include "AnimatedNode.h"

class Portal : public AnimatedNode
{
public:
	Portal(const sf::Texture& texture);
	virtual unsigned int getCategory() const;
	void setActive(bool active);
	bool isActive() const;
	void printHello() const;

private:
	bool mActive;
};

