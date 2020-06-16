///////////////////////////////////////////////////////////
//  ObstacleAvoidanceModule.h
//  Implementation of the Class ObstacleAvoidanceModule
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_787CF77F_FF7B_4599_A077_EE2F361A4AA7__INCLUDED_)
#define EA_787CF77F_FF7B_4599_A077_EE2F361A4AA7__INCLUDED_

#include "DriveCommandPublisher.h"
#include "DataProcessModule.h"

class ObstacleAvoidanceModule : public DriveCommandPublisher, public DataProcessModule
{

public:
	ObstacleAvoidanceModule();
	virtual ~ObstacleAvoidanceModule();

	virtual void processData();

};
#endif // !defined(EA_787CF77F_FF7B_4599_A077_EE2F361A4AA7__INCLUDED_)
