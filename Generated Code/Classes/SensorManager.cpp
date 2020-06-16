///////////////////////////////////////////////////////////
//  SensorManager.cpp
//  Implementation of the Class SensorManager
//  Created on:      05-Jun-2018 14:42:06
//  Original author: student
///////////////////////////////////////////////////////////

#include "SensorManager.h"




SensorManager::SensorManager(){

}


SensorManager::~SensorManager(){

}


struct SDL_Surface* SensorManager::getDebugDisplaySurface(){

	return  NULL;
}


double SensorManager::getDepth(int x, int y){

	return 0;
}


float SensorManager::getFps(){

	return 0;
}


SensorManager* SensorManager::getInstance(){

	return  NULL;
}


std::vector<MarkerInfo> SensorManager::getMarkerList(){

	return  NULL;
}


int SensorManager::getSensorHeight(){

	return 0;
}


int SensorManager::getSensorWidth(){

	return 0;
}


bool SensorManager::runOnce(){

	return false;
}