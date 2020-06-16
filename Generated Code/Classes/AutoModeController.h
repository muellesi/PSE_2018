///////////////////////////////////////////////////////////
//  AutoModeController.h
//  Implementation of the Class AutoModeController
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_746D9C5C_46D1_4e46_BDB1_568A9857291C__INCLUDED_)
#define EA_746D9C5C_46D1_4e46_BDB1_568A9857291C__INCLUDED_

#include "DriveCommandHandler.h"
#include "AbstractModeController.h"
#include "ObstacleAvoidanceModule.h"
#include "FollowMarkerModule.h"
#include "FindMarkerModule.h"

class AutoModeController : public AbstractModeController
{

public:
	AutoModeController();
	virtual ~AutoModeController();
	ObstacleAvoidanceModule *m_ObstacleAvoidanceModule;
	FollowMarkerModule *m_FollowMarkerModule;
	FindMarkerModule *m_FindMarkerModule;

	AutoModeController(DriveCommandHandler driveCommandHandler);
	void setDistance(int distance);
	void step();

};
#endif // !defined(EA_746D9C5C_46D1_4e46_BDB1_568A9857291C__INCLUDED_)
