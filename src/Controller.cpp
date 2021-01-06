//============================= include section ==============================
#include "Controller.h"
#include "Menu.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
//============================= public section ===============================
//==================== Constructors & distructors section ====================
Controller::Controller() :
	m_window(sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Rod Runner",
		sf::Style::Fullscreen)),
	m_board(Board(m_window.getSize())),
	/*m_gameobjects({}),,
	m_player(nullptr),*/
	m_effects(EffectsHolder()),
	m_menu()
	/*m_gameState()*/ {
	this->m_menu = Menu(Menu(this->m_effects,
		(sf::Vector2f)this->m_window.getSize(),
		sf::Vector2f(0, 0)));
	//this->m_gameState = GameState(this->m_effects, sf::Vector2f(500, 1900));
}
//============================== gets section ================================
//============================ methods section ===============================
//============================================================================
void Controller::run() {
	while (true) {
		this->m_window.clear();
		char choose = this->runMenu();
		if (!this->m_window.isOpen() || choose == 'q')
			break;
		if (choose == 's')
			this->runGame();
		if (!this->m_window.isOpen())
			break;
	}
}
//============================================================================
char Controller::runMenu() {
	while (this->m_window.isOpen())
	{
		this->m_window.clear();
		this->m_menu.draw(this->m_window);
		this->m_window.display();
		sf::Event event{};
		while (this->m_window.waitEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				this->m_window.close();
				break;
			case sf::Event::MouseButtonReleased:
				switch (this->m_menu.handleClick(sf::Vector2f(
					(float)event.mouseButton.x, 
					(float)event.mouseButton.y))) {
				case 's':
					return 's';
				case 'q':
					return 'q';
					break;
				}
				break;
			default:
				if (this->m_menu.pointingHundle((sf::Vector2f)
					sf::Mouse::getPosition(this->m_window))) {
					this->m_menu.draw(this->m_window);
					this->m_window.display();
				}
				break;
			}

		}
	}
	return 'q';
}
//============================================================================
void Controller::runGame() {
	while (this->m_window.isOpen()){
		this->m_window.clear();
		this->m_board.draw(m_window);
		this->m_window.display();
		//boardreader
		//this->m_gameState.levelup(150);
		sf::Event event;
		while (m_window.waitEvent(event)) {
			
		}
		/*while (true){
			if (this->m_gameState.nextTurn()) {
				this->m_gameState.draw(this->m_window);
				this->m_window.display();
			}
		}*/
	}
}
//============================ private section ===============================
//============================== gets section ================================
//============================ methods section ===============================