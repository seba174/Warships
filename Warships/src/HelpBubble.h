#pragma once

class HelpBubble :
	public sf::Drawable
{
public:
	HelpBubble();

	void setSize(const sf::Vector2f& size) { bubble.setSize(size); }

	void setString(const std::wstring& wstring) {
		text.setString(wstring);
		setTextPosition();
	}

	void setFont(const sf::Font& font) {
		text.setFont(font);
		setTextPosition();
	}

	void setCharacterSize(unsigned size) {
		text.setCharacterSize(size);
		setTextPosition();
	}

	void setPosition(const sf::Vector2f& position);

	void setOrigin(const sf::Vector2f& origin);

	sf::Vector2f getSize() const { return bubble.getSize(); }

	void setTextColor(const sf::Color& color) { text.setFillColor(color); }

	void setBubbleColor(const sf::Color& color) { bubble.setFillColor(color); }

	void setScale(float scale);

	float getScale() const { return bubble.getScale().x; }

	sf::Color getTextColor() const { return text.getFillColor(); }

	sf::Color getBubbleColor() const { return bubble.getFillColor(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setTextPosition();

	sf::Text text;
	sf::RectangleShape bubble;
};

