///////////////////////////////////////////////////////////
//  DriveController.cpp
//  Implementation of the Class DriveController
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#include "DriveController.h"




DriveController::DriveController(){

}


DriveController::~DriveController(){

}


DriveController* DriveController::getInstance(){

	return  NULL;
}


bool DriveController::getTestMode() const {

	return false;
}


void DriveController::setTestMode(bool enable){

}


void DriveController::step(){

}


bool DriveController::updateController(int speed, int steering){

	return false;
}


bool DriveController::updateDirect(int speed, int steering){

	return false;
}


bool DriveController::updateDirectMotor(int speedLeft, int speedRight){

	return false;
}