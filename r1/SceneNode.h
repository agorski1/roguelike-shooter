#pragma once
#include <memory>
#include <vector>
#include "Category.h"
#include <set>
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"


class CommandQueue;
struct Command;


class SceneNode : public sf::Transformable, public sf::Drawable,
	private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
	SceneNode(Category::Type category = Category::None);

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

	sf::Transform getWolrdTranform() const;
	sf::Vector2f getWorldPosition() const;

	void update(sf::Time dt, CommandQueue& commands);
	virtual unsigned int getCategory() const;
	void onCommand(const Command& command, sf::Time dt);
	virtual sf::FloatRect getBoundingRect() const;

	void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void removeWrecks();

	virtual bool isMarkedForRemoval() const;
	virtual bool isDestroyed() const;


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
	void updateChildern(sf::Time dt, CommandQueue& commands);


private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
	Category::Type mDefaultCategory;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);
