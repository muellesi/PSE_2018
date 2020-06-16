///////////////////////////////////////////////////////////
//  DataProcessModule.h
//  Implementation of the Class DataProcessModule
//  Created on:      05-Jun-2018 14:42:02
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_7EB265CF_B1BB_458d_80AE_0AE0BC0479D8__INCLUDED_)
#define EA_7EB265CF_B1BB_458d_80AE_0AE0BC0479D8__INCLUDED_

#include "SensorManager.h"

class DataProcessModule
{

public:
	DataProcessModule();
	virtual ~DataProcessModule();
	SensorManager *m_SensorManager;

	DataProcessModule(std::shared_ptr<SensorManagerPimpl> sensorManager);
	virtual void processData() =0;

private:
	std::shared_ptr<SensorManagerPimpl> mSensorManager;

};
#endif // !defined(EA_7EB265CF_B1BB_458d_80AE_0AE0BC0479D8__INCLUDED_)
