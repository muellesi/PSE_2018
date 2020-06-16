///////////////////////////////////////////////////////////
//  FollowMarkerModule.h
//  Implementation of the Class FollowMarkerModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_6287F375_AF0F_4016_93B5_C5597946B770__INCLUDED_)
#define EA_6287F375_AF0F_4016_93B5_C5597946B770__INCLUDED_

#include "DriveCommandPublisher.h"
#include "DataProcessModule.h"
#include "PIDController.h"

class FollowMarkerModule : public DriveCommandPublisher, public DataProcessModule
{

public:
	FollowMarkerModule();
	virtual ~FollowMarkerModule();
	PIDController *m_PIDController;

	virtual void processData();
	void setDistance(int distance);

private:
	int mDistance;

};
#endif // !defined(EA_6287F375_AF0F_4016_93B5_C5597946B770__INCLUDED_)
