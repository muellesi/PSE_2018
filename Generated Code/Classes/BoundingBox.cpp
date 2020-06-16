///////////////////////////////////////////////////////////
//  BoundingBox.cpp
//  Implementation of the Class BoundingBox
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#include "BoundingBox.h"


BoundingBox::~BoundingBox(){

}





BoundingBox::BoundingBox(){

}


BoundingBox::BoundingBox(int x, int y, int width, int height, int regionID){

}


void BoundingBox::draw(struct SDL_Surface* surface){

}


void BoundingBox::drawMarker(struct SDL_Surface* surface){

}


int BoundingBox::getArea() const {

	return 0;
}


void BoundingBox::grow(int amount){

}


bool BoundingBox::isOverlapping(const BoundingBox& other) const {

	return false;
}


void BoundingBox::join(const BoundingBox& other){

}