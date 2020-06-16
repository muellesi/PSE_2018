///////////////////////////////////////////////////////////
//  DriveCommandSubscriber.h
//  Implementation of the Class DriveCommandSubscriber
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_9B649CC5_E6FF_4cdd_BC31_C1E7F913B2A8__INCLUDED_)
#define EA_9B649CC5_E6FF_4cdd_BC31_C1E7F913B2A8__INCLUDED_

#include "DriveCommand.h"

class DriveCommandSubscriber
{

public:
	DriveCommandSubscriber();
	virtual ~DriveCommandSubscriber();

	virtual void updateDriveCommand(DriveCommand command) =0;

};
#endif // !defined(EA_9B649CC5_E6FF_4cdd_BC31_C1E7F913B2A8__INCLUDED_)
