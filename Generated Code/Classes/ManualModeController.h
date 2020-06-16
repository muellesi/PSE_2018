///////////////////////////////////////////////////////////
//  ManualModeController.h
//  Implementation of the Class ManualModeController
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_39300704_4F13_482b_8C83_392CF5C94C8C__INCLUDED_)
#define EA_39300704_4F13_482b_8C83_392CF5C94C8C__INCLUDED_

#include "DriveCommandHandler.h"
#include "ManualDriveCommandModule.h"
#include "AbstractModeController.h"
#include "FindMarkerModule.h"

class ManualModeController : public AbstractModeController
{

public:
	ManualModeController();
	virtual ~ManualModeController();
	ManualDriveCommandModule *m_ManualDriveCommandModule;
	FindMarkerModule *m_FindMarkerModule;

	ManualModeController(DriveCommandHandler driveCommandHandler);
	int drive(std::chrono::duration duration, int velocity, int steering);
	void searchMarker();
	void setMaxDriveDuration(std::chrono::duration maxDriveDuration);

};
#endif // !defined(EA_39300704_4F13_482b_8C83_392CF5C94C8C__INCLUDED_)
