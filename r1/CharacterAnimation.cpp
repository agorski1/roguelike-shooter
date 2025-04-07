#include "CharacterAnimation.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "DataTables.h"
#include <iostream>

namespace
{
    const std::vector<AnimationData> Table = initializeAnimationData();
}

CharacterAnimation::CharacterAnimation(EntityType entityType)
    : mEntityType(entityType)
    , mSprite()
    , mCurrentType(AnimationType::IdleDown)
    , mCurrentFrame(0)
    , mElapsedTime(sf::Time::Zero)
    , mFrameSize(Table[mEntityType].frameSize)
    , mDuration(Table[mEntityType].duration)
    , mRepeat(Table[mEntityType].repeat)
    , mFrameCountMap(Table[mEntityType].frameCounts)
{
}

CharacterAnimation::CharacterAnimation(const TextureHolder& texture, EntityType entityType)
    : CharacterAnimation(entityType)
{
    setTexture(texture.get(Table[mEntityType].texture));
} 

void CharacterAnimation::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(sf::IntRect(
        mCurrentFrame * Table[mEntityType].frameSize.y,
        static_cast<int>(mCurrentType) * Table[mEntityType].frameSize.x,
        Table[mEntityType].frameSize.y,
        Table[mEntityType].frameSize.x));
}

const sf::Texture* CharacterAnimation::getTexture() const
{
    return mSprite.getTexture();
}

void CharacterAnimation::setFrameSize(sf::Vector2i frameSize)
{
    mFrameSize = frameSize;
}

sf::Vector2i CharacterAnimation::getFrameSize() const
{
    return mFrameSize;
}

void CharacterAnimation::setDuration(sf::Time duration)
{
    mDuration = duration;
}

sf::Time CharacterAnimation::getDuration() const
{
    return mDuration;
}

void CharacterAnimation::setRepeating(bool flag)
{
    mRepeat = flag;
}

bool CharacterAnimation::isRepeating() const
{
    return mRepeat;
}

void CharacterAnimation::restart()
{
    mCurrentFrame = 0;
    mElapsedTime = sf::Time::Zero;
}

bool CharacterAnimation::isFinished() const
{
    return !mRepeat && mCurrentFrame >= getNumFramesForRow(mCurrentType);
}

void CharacterAnimation::setAnimationType(AnimationType type)
{
    if (mCurrentType != type)
    {
        mCurrentType = type;
        restart();
    }
}

AnimationType CharacterAnimation::getAnimationType() const
{
    return mCurrentType;
}

void CharacterAnimation::setNumFramesForRow(AnimationType type, int numFrames)
{
    mFrameCountMap[type] = numFrames;
}

int CharacterAnimation::getNumFramesForRow(AnimationType type) const
{
    auto it = mFrameCountMap.find(type);
    if (it != mFrameCountMap.end())
        return it->second;

    return 1;
}

void CharacterAnimation::update(sf::Time dt)
{
    mElapsedTime += dt;

    int numFrames = getNumFramesForRow(mCurrentType);
    if (numFrames <= 0) return;

    sf::Time frameTime = mDuration / static_cast<float>(numFrames);

    while (mElapsedTime >= frameTime)
    {
        mElapsedTime -= frameTime;

        // Przechodzimy do kolejnej klatki
        if (mCurrentFrame + 1 < numFrames)
        {
            mCurrentFrame++;
        }
        else if (mRepeat) // Jeśli animacja się powtarza, wracamy do pierwszej klatki
        {
            mCurrentFrame = 0;
        }

        // Aktualizujemy teksturę, przesuwając "widok" sprite'a na odpowiednią klatkę
        int frameWidth = mFrameSize.x;
        int frameHeight = mFrameSize.y;
        mSprite.setTextureRect(sf::IntRect(mCurrentFrame * frameWidth,
            static_cast<int>(mCurrentType) * frameHeight,
            frameWidth,
            frameHeight));
    }
}


void CharacterAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

sf::FloatRect CharacterAnimation::getLocalBounds() const
{
    return sf::FloatRect(sf::Vector2f(), sf::Vector2f(mFrameSize));
}

sf::FloatRect CharacterAnimation::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}
