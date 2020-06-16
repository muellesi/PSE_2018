///////////////////////////////////////////////////////////
//  FindMarkerModule.h
//  Implementation of the Class FindMarkerModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_055CFCE7_85D3_4cb8_8282_3B988849E4EA__INCLUDED_)
#define EA_055CFCE7_85D3_4cb8_8282_3B988849E4EA__INCLUDED_

#include "DriveCommandPublisher.h"
#include "DataProcessModule.h"

class FindMarkerModule : public DriveCommandPublisher, public DataProcessModule
{

public:
	FindMarkerModule();
	virtual ~FindMarkerModule();

	void abort();
	virtual void processData();
	void searchBlocking();

};
#endif // !defined(EA_055CFCE7_85D3_4cb8_8282_3B988849E4EA__INCLUDED_)
