#pragma once
#include "MovingObject.h"
#include <SFML/Graphics.hpp>

class Enemy: public MovingObject
{
public:
	using MovingObject::MovingObject;

	virtual bool isFalling(const Board&);
private:
	 
};