//============================= include section ==============================
#include "Wall.h"
//============================= public section ===============================
//==================== Constructors & distructors section ====================
//============================== gets section ================================
//============================ methods section ===============================
void Wall::draw(sf::RenderWindow& window, const sf::Texture& texture) const {
	sf::Sprite wall;
	wall.setTexture(texture);
	window.draw(wall);
}

void Wall::dig(){}
//============================ private section ===============================
//============================== gets section ================================
//============================ methods section ===============================