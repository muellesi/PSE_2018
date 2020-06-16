///////////////////////////////////////////////////////////
//  DriveCommandHandler.h
//  Implementation of the Class DriveCommandHandler
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_48EE90EF_7CC0_40ef_B5BB_8682EEDE39D5__INCLUDED_)
#define EA_48EE90EF_7CC0_40ef_B5BB_8682EEDE39D5__INCLUDED_

#include "DriveCommand.h"
#include "DriveCommandSubscriber.h"
#include "DriveController.h"

class DriveCommandHandler : public DriveCommandSubscriber
{

public:
	DriveCommandHandler();
	virtual ~DriveCommandHandler();
	DriveController *m_DriveController;

	void stepMotor();
	virtual void trySetDriveCommand(DriveCommand command);
	void updateMotor();

private:
	DriveCommand currentDriveCommand;

};
#endif // !defined(EA_48EE90EF_7CC0_40ef_B5BB_8682EEDE39D5__INCLUDED_)
