#pragma once
#include "StaticObject.h"
class Wall : public StaticObject
{
public:
	Wall(const sf::Vector2f = sf::Vector2f(0,0),
		const sf::Vector2f& = sf::Vector2f(0,0));

	void playTurn(const sf::Time&,const Board&) override;
	void dig();
private:
	int m_digState;
};
