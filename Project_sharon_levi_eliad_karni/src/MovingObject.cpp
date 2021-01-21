/*
   This file conatains all methods of the base class MovingObject.
*/
//============================= include section ==============================
#include "MovingObject.h"
#include "Board.h"
#include "Ladder.h"
#include "Wall.h"
#include "Rod.h"
#include "Door.h"
#include "Macros.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
//============================= public section ===============================
//==================== Constructors & distructors section ====================
MovingObject::MovingObject(const sf::Vector2f& location,
	const sf::Vector2f& size,
	char objectType)
	: GameObject(location, size, objectType, true), m_isTrapped(false),
	m_initialLoc(location), m_lookingState(WALK_RIGHT), 
	m_trappingWall(nullptr){}
//============================== gets section ================================
sf::Vector2f MovingObject::getInitialLoc()const { 
	return this->m_initialLoc; 
}
//============================================================================
int MovingObject::getLookState()const { return this->m_lookingState; }
//============================================================================
const Wall& MovingObject::getTrappingWall()const { 
	return *this->m_trappingWall;
}
//============================ methods section ===============================
/*
* this function handle in spacial moves cases of each character:
* falling down & get into traps.
*/
bool MovingObject::physicsTurn(const sf::Time& deltaTime, Board& board) {
	//handle traping wall communication
	if (this->m_isTrapped) {
		if (!this->m_trappingWall->getTrappingState() ||
			!(this->m_trappingWall->CollidesWith(*this))) {
			this->setState(FALLING);
			this->getUntrapped();
		}
	}
	//the character is falling ?
	if (this->isFalling(board)) {
		this->setState(FALLING);
		moveDown(deltaTime, board);
		return true;
	}
	return false;
}
//============================================================================
/*
* this function handle the case of user pressed on up button. 
* the function set the new location only if the wanted move is possible.
*/
void MovingObject::moveUp(const sf::Time& deltaTime, Board& board){
	sf::Vector2f movement(0, -1);
	movement *= (MOVEMENT_SPEED * deltaTime.asSeconds());
	StaticObject* object = board.getContent(this->getAbove() + movement);

	if (board.isMovePossible(this->getAbove() + movement)) {
		if (object != nullptr)
			object->handleCollision(*this, movement);
		else if (this->getState() != RODDING) {
			if (dynamic_cast <Ladder*> (board.getContent(this->getBelow())) ||
				dynamic_cast <Ladder*> (board.getContent(this->getCenter())))
				this->nullMovement(movement);
			else
				setState(STAND);
		}
	}
	this->updateAnimation(deltaTime);
}
//============================================================================
/*
* this function handle the case of user pressed on down button or if the 
* character is falling down.
* the function set the new location only if the wanted move is possible.
*/
void MovingObject::moveDown(const sf::Time& deltaTime, Board&  board){
	sf::Vector2f movement(0, 1);
	movement *= (MOVEMENT_SPEED * deltaTime.asSeconds());
	StaticObject* object = board.getContent(this->getBelow() + movement);
	if (board.isMovePossible(this->getBelow() +  movement)) {
		if(object != nullptr)
			object->handleCollision(*this, movement);
		else {
			this->nullMovement(movement);
			this->setState(FALLING);
		}
	}
	this->updateAnimation(deltaTime);
}
//============================================================================
/*
* this function handle the case of user pressed on left button.
* the function set the new location only if the wanted move is possible.
*/
void MovingObject::moveLeft(const sf::Time& deltaTime, Board& board){
	sf::Vector2f movement(-1, 0);
	movement *= (MOVEMENT_SPEED * deltaTime.asSeconds());
	StaticObject* object = board.getContent(this->getLeft() + movement),
		*center = board.getContent(this->getCenter()),
		* bot = board.getContent(this->getLocation() + 
			sf::Vector2f(0,this->getSize().y));

	if (board.isMovePossible(this->getRight() + movement)) {
		if (object != nullptr)
			object->handleCollision(*this, movement);
		else {
			if (dynamic_cast <Wall*> (bot))
				this->setLocation({ 0, (bot->getLocation() -
					(this->getLocation() + this->getSize())).y });
			this->nullMovement(movement);
			if (center == nullptr || dynamic_cast <Door*> (center))
				this->setState(RUNNING);
		}
		this->setLookState(WALK_LEFT);
	}
	this->updateAnimation(deltaTime);
}
//============================================================================
/*
* this function handle the case of user pressed on right button.
* the function set the new location only if the wanted move is possible.
*/
void MovingObject::moveRight(const sf::Time& deltaTime, Board& board){
	sf::Vector2f movement(1, 0);
	movement *= (MOVEMENT_SPEED * deltaTime.asSeconds());
	StaticObject *object = board.getContent(this->getRight() + movement),
		*center = board.getContent(this->getCenter()),
		*bot = board.getContent(this->getLocation() + this->getSize());
	if (board.isMovePossible(this->getRight() + movement)) {
		if (object != nullptr)
			object->handleCollision(*this, movement);
		else {
			if (dynamic_cast <Wall*> (bot)) {
				this->setLocation({ 0, (bot->getLocation() -
					(this->getLocation() + this->getSize())).y });
			}
			this->nullMovement(movement);
			if(center == nullptr || dynamic_cast <Door*> (center))
				this->setState(RUNNING);
		}
		this->setLookState(WALK_RIGHT);
	}
	this->updateAnimation(deltaTime);
}
//============================================================================
void MovingObject::getTrapped(Wall* trappingWall) {
	this->m_isTrapped = true;
	trappingWall->changeTrapMode(true);
	this->m_trappingWall = trappingWall;
}
//============================================================================
/*This method change the state of the object to untrapped after the wall 
finish to be digged. The new location of the object is above this wall.*/
void MovingObject::getUntrapped() {
	this->m_isTrapped = false;
	this->m_trappingWall->changeTrapMode(false);
	if (!this->m_trappingWall->isDigged() && this->m_trappingWall
		->CollidesWith(*this))
		this->setLocation({ 0, (this->m_trappingWall->getLocation() -
					(this->getLocation() + this->getSize())).y });
	this->m_trappingWall = nullptr;
}
//============================================================================
bool MovingObject::getTrapState()const { return this->m_isTrapped; }
//============================================================================
/*
* this function check if the character is in a middle of falling down.
* it checks all the cases of fallings.
*/
bool MovingObject::isFalling(const Board& board){
	if (this->getState() != CLIMBING && this->getState() != RODDING) {
		if (dynamic_cast <const Ladder*> (board.getContent
		(this->getCenter())) ||
			dynamic_cast <const Ladder*> 
			(board.getContent(this->getBelow())))
			return false;
		if (dynamic_cast <const Wall*> (board.getContent
		(this->getBelow()))) {
			if (((const Wall*)board.getContent(this->getBelow()))
				->isDigged() &&
				(!((const Wall*)board.getContent(this->getBelow()))
				->getTrappingState())|| board.getContent(this->getBelow())
				== this->m_trappingWall)
				return true;
			return false;
		}
		if (board.isMovePossible(this->getBelow())) {
			return true;
		}
		if ((this->getState() == FALLING || this->getState() == RUNNING)
			&& board.getContent(this->getBelow()) == nullptr)
			return true;
	}
	return false;
}
//============================================================================
/*
* this function return the character to his initial state.
*/
void MovingObject::reset(){
	this->GameObject::reset();
	this->setLocation(sf::Vector2f(this->m_initialLoc.x - 
		this->getLocation().x,
		this->m_initialLoc.y - this->getLocation().y));
	if(this->m_isTrapped)
		this->getUntrapped();
}
//============================ private section ===============================
//============================== sets section ================================
/*
* this function get a new location and set this location in the object 
* location
*/
void MovingObject::setLocation(const sf::Vector2f& movement){
	this->GameObject::setLocation(movement);
}
//============================================================================
/*
* the function change the direction that the character looking to.
*/
void MovingObject::setLookState(int state) {
	if (this->m_lookingState != state) {
		this->m_lookingState = state;
		this->flipSprite();
	}
}
//============================================================================
/*
* This function using in double dispatch method to handle colision
* between a moving object to a ladder object.
*/
void MovingObject::handleCollision(const Ladder& obj,
	const sf::Vector2f& movement) {
	this->setState(CLIMBING);
	if (movement.y != 0)
		this->setLocation({ obj.getLocation().x - this->getLocation().x,
			movement.y });
	else
		this->setLocation(movement);
}
//============================================================================
/*
* This function using in double dispatch method to handle colision
* between a moving object to a wall object.
*/
void MovingObject::handleCollision(Wall& obj,
	const sf::Vector2f& movement) {
	if (obj.isDigged() && movement.y > 0) {
		this->setLocation(sf::Vector2f(obj.getLocation().x
			- this->getLocation().x, movement.y));
		this->getTrapped(&obj);
	}
	else if ((this->getLocation()+this->getSize()).y < obj.getLocation().y){
		this->setLocation({ movement.x, (obj.getLocation() - 
			(this->getLocation() + this->getSize())).y });
	}
	if(this->getState() == RUNNING || this->getState() == FALLING)
		this->setState(STAND);
}
//============================================================================
/*
* This function using in double dispatch method to handle colision
* between a moving object to a rod object.
*/
void MovingObject::handleCollision(const Rod& obj,
	const sf::Vector2f& movement) {
	if (RODDING && movement.y < 0) {
		this->setState(FALLING);
	}
	else{
		float aaa = movement.x, bbb = obj.getLocation().y
			- this->getLocation().y;
			this->setLocation({ movement.x, obj.getLocation().y
				- this->getLocation().y });
		this->setState(RODDING);
		return;
	}
}
//============================================================================
/*
* This is a generic function using in double dispatch method to handle colision 
* between a moving object to static object on the board.
*/
void MovingObject::handleCollision(const StaticObject& obj,
	const sf::Vector2f& movement) {
	this->nullMovement(movement);
}
//============================================================================
/*
* This method set a new location to the moving object 
*/
void MovingObject::nullMovement(const sf::Vector2f& movement) {
	this->setLocation(movement);
}
//============================================================================
/*
* This method is set state and updating animation clock if needed.
*/
void MovingObject::setState(int state) {
	if (this->getState() != state)
		this->resetAnimationTime();
	this->GameObject::setState(state);
}