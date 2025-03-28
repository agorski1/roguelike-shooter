#pragma once
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class AnimationType
{
    IdleUp, IdleLeft, IdleDown, IdleRight,
    WalkUp, WalkLeft, WalkDown, WalkRight,
    Dash,
};

class Animation : public sf::Drawable, public sf::Transformable
{
public:
    enum EntityType
    {
        Player,
        Enemy,
        NPC,
        Pickup,
        EntityCount,
    };

    explicit Animation(EntityType entityType);
    explicit Animation(const TextureHolder& textures, EntityType entityType);

    void setTexture(const sf::Texture& texture);
    const sf::Texture* getTexture() const;

    void setFrameSize(sf::Vector2i frameSize);
    sf::Vector2i getFrameSize() const;

    void setDuration(sf::Time duration);
    sf::Time getDuration() const;

    void setRepeating(bool flag);
    bool isRepeating() const;

    void restart();
    bool isFinished() const;

    void setAnimationType(AnimationType type);
    AnimationType getAnimationType() const;

    void setNumFramesForRow(AnimationType type, int numFrames);
    int getNumFramesForRow(AnimationType type) const;

    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    void update(sf::Time dt);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    EntityType mEntityType;
    sf::Sprite mSprite;
    sf::Vector2i mFrameSize;
    AnimationType mCurrentType;
    int mCurrentFrame;
    sf::Time mDuration;
    sf::Time mElapsedTime;
    bool mRepeat;

    std::unordered_map<AnimationType, int> mFrameCountMap; // Przechowuje liczbę klatek dla każdego AnimationType
};

