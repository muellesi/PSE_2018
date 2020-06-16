///////////////////////////////////////////////////////////
//  PIDController.h
//  Implementation of the Class PIDController
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_D60E5701_7970_4327_954D_527821FB5CF3__INCLUDED_)
#define EA_D60E5701_7970_4327_954D_527821FB5CF3__INCLUDED_

class PIDController
{

public:
	PIDController();
	virtual ~PIDController();

	int PIDController(double P, double I, double D);
	double calculate(double error);

private:
	double d;
	double error;
	double errorDot;
	double i;
	double integralError;
	double p;

};
#endif // !defined(EA_D60E5701_7970_4327_954D_527821FB5CF3__INCLUDED_)
