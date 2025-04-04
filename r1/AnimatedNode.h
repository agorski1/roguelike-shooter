#pragma once
#include "SceneNode.h"
#include "Animation.h"

class AnimatedNode : public SceneNode
{
public:
	AnimatedNode(const sf::Texture& texture);

	
private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;

private:
	Animation mAnimation;

};

