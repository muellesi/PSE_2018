///////////////////////////////////////////////////////////
//  DriveController.h
//  Implementation of the Class DriveController
//  Created on:      05-Jun-2018 14:42:03
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_7AE5830F_74B5_4217_A865_EE955AC6EAA3__INCLUDED_)
#define EA_7AE5830F_74B5_4217_A865_EE955AC6EAA3__INCLUDED_

/**
 * Interface to the drive hardware.
 */
class DriveController
{

public:
	DriveController(const DriveController& prm1) = delete;
	static DriveController* getInstance();
	bool getTestMode() const;
	DriveController& operator=(const DriveController& prm1) = delete;
	void setTestMode(bool enable);
	void step();
	bool updateController(int speed, int steering);
	bool updateDirect(int speed, int steering);
	bool updateDirectMotor(int speedLeft, int speedRight);

protected:
	std::unique_ptr<DriveControllerPimpl> m_Pimpl;

	DriveController();
	~DriveController();

};
#endif // !defined(EA_7AE5830F_74B5_4217_A865_EE955AC6EAA3__INCLUDED_)
