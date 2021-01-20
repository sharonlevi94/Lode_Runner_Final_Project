//============================= include section ==============================
#include "Coin.h"
#include "Macros.h"
#include "MovingObject.h"
//============================= public section ===============================
//==================== Constructors & distructors section ====================
Coin::Coin(const sf::Vector2f& location,
		const sf::Vector2f& size)
	:CollectableObject(location, size, COIN_T) {
	++m_coinsCounter;
}
//============================================================================
Coin::~Coin() { 
	if(!this->is_collected())
		--m_coinsCounter; 
}
//========================== statics declaretions ============================
unsigned int Coin::m_coinsCounter = 0;
//============================================================================
unsigned int Coin::getCoinsCounter() { return m_coinsCounter; }
//============================================================================
void Coin::reset() {
	if (this->is_collected())
		++m_coinsCounter;
	CollectableObject::reset();
}
//============================================================================
void Coin::collect() {
	CollectableObject::collect();
	--m_coinsCounter;
}
//============================================================================
void Coin::handleCollision(MovingObject& obj, const sf::Vector2f& movement) {
	obj.handleCollision(*this, movement);
}