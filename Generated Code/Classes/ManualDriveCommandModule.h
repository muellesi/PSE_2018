///////////////////////////////////////////////////////////
//  ManualDriveCommandModule.h
//  Implementation of the Class ManualDriveCommandModule
//  Created on:      05-Jun-2018 14:42:04
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_AC9C1989_D0FB_4fc9_A008_2C565BB8DE92__INCLUDED_)
#define EA_AC9C1989_D0FB_4fc9_A008_2C565BB8DE92__INCLUDED_

#include "DriveCommandPublisher.h"

class ManualDriveCommandModule : public DriveCommandPublisher
{

public:
	ManualDriveCommandModule();
	virtual ~ManualDriveCommandModule();

	void abort();
	void driveBlocking(std::chrono::duration time, int velocity, int steering);
	void setMaxDriveDuration(std::chrono::duration duration);

private:
	std::chrono::duration mMaxDuration;
	bool mStop;

};
#endif // !defined(EA_AC9C1989_D0FB_4fc9_A008_2C565BB8DE92__INCLUDED_)
