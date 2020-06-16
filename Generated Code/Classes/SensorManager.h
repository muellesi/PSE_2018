///////////////////////////////////////////////////////////
//  SensorManager.h
//  Implementation of the Class SensorManager
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_3F7C8FF8_007F_4d5d_99BA_C76C7D045F32__INCLUDED_)
#define EA_3F7C8FF8_007F_4d5d_99BA_C76C7D045F32__INCLUDED_

/**
 * Sensor and image processing manager.
 */
class SensorManager
{

public:
	SensorManager(const SensorManager& prm1) = delete;
	struct SDL_Surface* getDebugDisplaySurface();
	double getDepth(int x, int y);
	float getFps();
	static SensorManager* getInstance();
	std::vector<MarkerInfo> getMarkerList();
	int getSensorHeight();
	int getSensorWidth();
	SensorManager& operator=(const SensorManager& prm1) = delete;
	bool runOnce();

protected:
	std::shared_ptr<SensorManagerPimpl> m_Pimpl;

	SensorManager();
	~SensorManager();

};
#endif // !defined(EA_3F7C8FF8_007F_4d5d_99BA_C76C7D045F32__INCLUDED_)
