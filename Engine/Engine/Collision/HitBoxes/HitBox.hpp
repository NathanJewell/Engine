#pragma once
#include <SFML\Graphics.hpp>
class HitBox
{
public:
	
	enum HitBoxTypes { AABB = 0, CIRC = 1 };
	HitBox();
	~HitBox();

	void setPosition(const sf::Vector2f& pos);
	void move(const sf::Vector2f& disp);
	sf::Vector2f getPosition();

	void setType(const unsigned int & type);
	unsigned int getType();

	virtual bool isPointInside(const sf::Vector2f& point) = 0;

protected:

	sf::Vector2f position;
	

private:

	unsigned int typeID;
	bool typeSet;

	
};
