///////////////////////////////////////////////////////////
//  DriveCommandPublisher.h
//  Implementation of the Class DriveCommandPublisher
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_E7849A16_7164_41e1_8DBA_EE781DAC4F65__INCLUDED_)
#define EA_E7849A16_7164_41e1_8DBA_EE781DAC4F65__INCLUDED_

#include "DriveCommandSubscriber.h"

class DriveCommandPublisher
{

public:
	DriveCommandPublisher();
	virtual ~DriveCommandPublisher();
	DriveCommandSubscriber *m_DriveCommandSubscriber;

	DriveCommandPublisher(DriveCommandPublisherType type);
	void addSubscriber(DriveCommandSubscriber& subscriber);

protected:
	int updateSubscribers(int speed, int steering);

private:
	DriveCommandPublisherType driveCommandPublisherType;
	std::vector<DriveCommandSubscriber&> subscribers;

};
#endif // !defined(EA_E7849A16_7164_41e1_8DBA_EE781DAC4F65__INCLUDED_)
