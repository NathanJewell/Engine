#include "Slider.hpp"

Slider::Slider(sf::Vector2f& p, const sf::Texture& bg, const sf::Texture& indicator, double M, double m, double start, const std::string& t, const unsigned int& fcharSize)
{
	textString = t;
	charSize = fcharSize;
	currentValue = start;
	background = bg;
	sliderThing = indicator;
	maxValue = M;
	minValue = m;
	position = p;
	cordScale = bg.getSize().x / (maxValue - minValue);
	
	if (!font.loadFromFile("arial.ttf"))
	{

	}

	bgSprite.setup(&bg, position, sf::Vector2f(300, 100), 0);
	slSprite.setup(&indicator, position, sf::Vector2f(300, 100), 0);

	text.setFont(font);
	text.setString(textString);
	text.setCharacterSize(charSize);
	//std::cout << cordScale;
}

//bool Slider::getEventDataBool(){}//here so its not abstract

int Slider::getEventDataInt()
{
	return currentValue;
}
void Slider::setButtonTextString(std::string newString)
{
	textString = newString;
}
std::string Slider::getButtonTextString()
{
	return textString;
}

void Slider::update(){}
void Slider::update(InputData& inpData){}//also just here to prevent error

void Slider::resetMD(){}

void Slider::update(sf::Vector2f& mousePos, bool& clicked, bool& pressed)
{
	if (pressed == true)
	{
		// std::cout << "here1" << std::endl;
		//nowClicked = !nowClicked; //toggle clicked status

		//if it is...test to see if a point is not inside the button
		if (mousePos.x < bgTLPos.x ||
			mousePos.y < bgTLPos.y ||
			mousePos.x > bgBRPos.x ||
			mousePos.y > bgBRPos.y)
		{

		}
		else
		{
			//std::cout<<cordScale<<endl<<minValue<<endl;
			//std::cout << bgTLPos.x <<endl<< bgBRPos.x<<endl;
			//std::cout <<mousePos.x - bgTLPos.x<<endl;
			//std::cout << currentValue << std::endl;
			currentValue = (mousePos.x - bgTLPos.x) / cordScale + minValue;
		}
	}
	if (currentValue > maxValue)
	{
		currentValue = maxValue;
	}
	else if (currentValue < minValue)
	{
		currentValue = minValue;
	}
}

void Slider::draw(sf::RenderWindow& window, const sf::Vector2f& drawPos)
{
	//reset BR and TL corner positions for collision

	bgTLPos = sf::Vector2f((position.x - (background.getSize().x / 2)), (position.y - (background.getSize().y / 2)));
	bgBRPos = sf::Vector2f((bgTLPos.x + (background.getSize().x)), (bgTLPos.y + (background.getSize().y)));

	bgSprite.setPosition(sf::Vector2f(position.x, position.y));
	slSprite.setPosition(sf::Vector2f(bgTLPos.x + ((currentValue - minValue)*cordScale) - sliderThing.getSize().y / 2, (bgTLPos.y + ((background.getSize().y / 2) - (sliderThing.getSize().y / 2)))));
	text.setPosition(position.x - text.getGlobalBounds().width / 2, position.y - sliderThing.getSize().y / 2 - text.getGlobalBounds().height / 2 - 10); //sets position of text
	//sliderThing->draw(sf::Vector2f(bgTLPos.x + ((currentValue - minValue)*cordScale) - sliderThing->getSize().y / 2, (bgTLPos.y + ((background->getSize().y / 2) - (sliderThing->getSize().y / 2))))); //needs to be centered

	//        ofCircle(bgTLPos, 10);
	//        ofCircle(bgBRPos, 10);


}