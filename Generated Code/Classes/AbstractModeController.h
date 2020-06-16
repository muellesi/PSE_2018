///////////////////////////////////////////////////////////
//  AbstractModeController.h
//  Implementation of the Class AbstractModeController
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_805EBA1C_A135_4230_8296_CD37D04862CB__INCLUDED_)
#define EA_805EBA1C_A135_4230_8296_CD37D04862CB__INCLUDED_

#include "DriveCommandHandler.h"

class AbstractModeController
{

public:
	AbstractModeController();
	virtual ~AbstractModeController();
	DriveCommandHandler *m_DriveCommandHandler;

	AbstractModeController(DriveCommandHandler driveCommandHandler);
	void abort();
	void step();

protected:
	std::shared_ptr<DriveCommandHandler> m_driveCommandHandler;

};
#endif // !defined(EA_805EBA1C_A135_4230_8296_CD37D04862CB__INCLUDED_)
