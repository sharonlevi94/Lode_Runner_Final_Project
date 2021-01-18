#pragma once
#include "Gift.h"
class ScoreGift : public Gift
{
public:
	ScoreGift(const sf::Vector2f = sf::Vector2f(0, 0),
		const sf::Vector2f & = sf::Vector2f(0, 0));
	virtual void handleColision(vector<std::unique_ptr<RandEnemy>>&,
		sf::Vector2f, GameState&) override;
private:
};
