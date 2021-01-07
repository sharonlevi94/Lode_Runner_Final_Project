#pragma once
#include <vector>
#include "GameObject.h"
#include "DataReader.h"
#include "EffectsHolder.h"
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
class Board
{
public:
	Board(const sf::Vector2f& location = sf::Vector2f(0, 0),
		const sf::Vector2f& size = sf::Vector2f(0, 0),
		const EffectsHolder& effects = EffectsHolder());
	~Board();

	void draw(sf::RenderWindow& window)const;
	std::vector<MovingObject*> loadNewLevel(const EffectsHolder&);
	bool is_next_lvl_exist()const;
	const GameObject* getContent(const sf::Vector2f& location)const;
	int getLevelTime()const;
	std::vector<MovingObject*> FindMovingObj();
	sf::Vector2f getlevelSize()const;
	const sf::Vector2f& getLocation() const;

private:
	std::vector<std::vector<GameObject*>> m_map;
	sf::Vector2f m_backgroundSize;
	sf::Vector2f m_levelSize;
	sf::Vector2f m_location;
	DataReader m_levelReader;
	int m_levelTime;
	sf::RectangleShape m_background;
	int m_levelNumber;

	void releaseMap();
};