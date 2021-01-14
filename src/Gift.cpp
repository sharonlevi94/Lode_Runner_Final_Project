//============================= include section ==============================
#include "Gift.h"
#include "Macros.h"
//============================= public section ===============================
//==================== Constructors & distructors section ====================
Gift::Gift(const sf::Vector2f location,
	const sf::Vector2f& size)
	:CollectableObject(location, size, GIFT_T) {
	++m_giftsCounter;
}
//============================================================================
Gift::~Gift() { --m_giftsCounter; }
//========================== statics declaretions ============================
unsigned int Gift::m_giftsCounter = 0;
//============================================================================
unsigned int Gift::getGiftsCounter() { return m_giftsCounter; }
//============================================================================
void Gift::reset() {
	CollectableObject::reset();
	++m_giftsCounter;
}
//============================================================================
void Gift::collect() {
	CollectableObject::collect();
	--m_giftsCounter;
}
//============================================================================
void Gift::playTurn(const sf::Time& deltatime, const Board& board) {}
//============================== gets section ================================
//============================ methods section ===============================
//============================================================================
//============================ private section ===============================
//============================== gets section ================================
//============================ methods section ===============================