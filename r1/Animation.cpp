#include "Animation.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "DataTables.h"
#include <iostream>

namespace
{
    const std::vector<AnimationData> Table = initializeAnimationData();
}

Animation::Animation(EntityType entityType)
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

Animation::Animation(const sf::Texture& texture, EntityType entityType)
    : Animation(entityType)
{
    setTexture(texture);
}

void Animation::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

const sf::Texture* Animation::getTexture() const
{
    return mSprite.getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
    mFrameSize = frameSize;
}

sf::Vector2i Animation::getFrameSize() const
{
    return mFrameSize;
}

void Animation::setDuration(sf::Time duration)
{
    mDuration = duration;
}

sf::Time Animation::getDuration() const
{
    return mDuration;
}

void Animation::setRepeating(bool flag)
{
    mRepeat = flag;
}

bool Animation::isRepeating() const
{
    return mRepeat;
}

void Animation::restart()
{
    mCurrentFrame = 0;
    mElapsedTime = sf::Time::Zero;
}

bool Animation::isFinished() const
{
    return !mRepeat && mCurrentFrame >= getNumFramesForRow(mCurrentType);
}

void Animation::setAnimationType(AnimationType type)
{
    if (mCurrentType != type)
    {
        mCurrentType = type;
        restart();
    }
}

AnimationType Animation::getAnimationType() const
{
    return mCurrentType;
}

void Animation::setNumFramesForRow(AnimationType type, int numFrames)
{
    mFrameCountMap[type] = numFrames;
}

int Animation::getNumFramesForRow(AnimationType type) const
{
    auto it = mFrameCountMap.find(type);
    if (it != mFrameCountMap.end())
        return it->second;

    return 1;
}

void Animation::update(sf::Time dt)
{
    // Aktualizujemy czas, który upłynął od ostatniej zmiany klatki
    mElapsedTime += dt;

    // Obliczamy czas trwania jednej klatki
    int numFrames = getNumFramesForRow(mCurrentType);
    if (numFrames <= 0) return;

    sf::Time frameTime = mDuration / static_cast<float>(numFrames);

    // Jeśli upłynął czas na zmianę klatki
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


void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
}

sf::FloatRect Animation::getLocalBounds() const
{
    return sf::FloatRect(sf::Vector2f(), sf::Vector2f(mFrameSize));
}

sf::FloatRect Animation::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}
