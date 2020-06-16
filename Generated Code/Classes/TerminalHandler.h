///////////////////////////////////////////////////////////
//  TerminalHandler.h
//  Implementation of the Class TerminalHandler
//  Created on:      05-Jun-2018 14:42:06
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_ABFA3B5C_2B42_4553_A69D_998136EF9B00__INCLUDED_)
#define EA_ABFA3B5C_2B42_4553_A69D_998136EF9B00__INCLUDED_

#include "AutoModeController.h"
#include "ManualModeController.h"

class TerminalHandler
{

public:
	TerminalHandler();
	virtual ~TerminalHandler();
	ManualModeController *m_ManualModeController;
	AutoModeController *m_AutoModeController;

	TerminalHandler(ManualModeController manualModeController, AutoModeController autoModeController);
	void abort();
	void startInputHandling();

private:
	AutoModeController mAutoModeController;
	bool mIsInAutoMode;
	ManualModeController mManualModeController;

};
#endif // !defined(EA_ABFA3B5C_2B42_4553_A69D_998136EF9B00__INCLUDED_)
