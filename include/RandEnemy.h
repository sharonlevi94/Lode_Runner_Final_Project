#pragma once
#include "Enemy.h"
#include "Board.h"
class RandEnemy : public Enemy
{
public:
	RandEnemy(const sf::Vector2f = sf::Vector2f(0, 0),
		const EffectsHolder & = EffectsHolder(),
		const sf::Vector2f & = sf::Vector2f(0, 0));

	virtual void playTurn(const Board&) override;
private:
};