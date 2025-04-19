#include "AnimatedNode.h"
#include "SFML/Graphics/RenderTarget.hpp"


AnimatedNode::AnimatedNode(const sf::Texture& texture)
	: mAnimation(texture)
{
}
void AnimatedNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	mAnimation.update(dt);

}

void AnimatedNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mAnimation, states);

}

sf::FloatRect AnimatedNode::getBoundingRect() const
{
	return getWorldTransform().transformRect(mAnimation.getGloablBounds());
}
