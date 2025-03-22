#pragma once
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Text.hpp"
#include "Component.h"
#include "ResourceIdentifiers.h"

#include <memory>
#include <string>

namespace sf
{
	class RenderTarget;
}


namespace GUI
{
	class Label : public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;

		Label(const std::string& text, const FontHolder& fonts);

		virtual bool isSelectable() const;
		virtual void handleEvent(const sf::Event& event);

		void setText(const std::string& text);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		sf::Text mText;
	};
}