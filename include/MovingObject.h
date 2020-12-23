#pragma once
#include "GameObject.h"
class MovingObject : public GameObject
{
public:

	MovingObject();
	

	MovingObject(
		const sf::Vector2f location = sf::Vector2f(0, 0),
		const sf::Vector2f size = sf::Vector2f(0, 0),
		int state = 0,
		const sf::Sprite& (*)(char) = nullptr);

	virtual void fall();

private:
	
};