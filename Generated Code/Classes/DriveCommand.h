///////////////////////////////////////////////////////////
//  DriveCommand.h
//  Implementation of the Class DriveCommand
//  Created on:      05-Jun-2018 14:42:02
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_C5D6769C_5BBF_45a7_9120_5256F3822FEE__INCLUDED_)
#define EA_C5D6769C_5BBF_45a7_9120_5256F3822FEE__INCLUDED_

struct DriveCommand
{

public:
	DriveCommandPublisherType source;
	int speed;
	int steering;

};
#endif // !defined(EA_C5D6769C_5BBF_45a7_9120_5256F3822FEE__INCLUDED_)
