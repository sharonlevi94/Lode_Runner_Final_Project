//============================= include section ==============================
#include "Wall.h"
#include "Utilities.h"
#include "Board.h"
//============================= public section ===============================
//==================== Constructors & distructors section ====================
Wall::Wall(const sf::Vector2f location,
		const sf::Vector2f& size )
	: StaticObject(location, size, WALL_T), m_digState(STAND)
{}
//============================== gets section ================================
//============================ methods section ===============================
//============================================================================
void Wall::dig() { this->m_digState = DIGGED; }
//============================================================================
void Wall::unDig() { this->m_digState = STAND; }
//============================================================================
void Wall::playTurn(const sf::Time& deltaTime,const Board& board) {}
//============================ private section ===============================
//============================== gets section ================================
//============================ methods section ===============================