///////////////////////////////////////////////////////////
//  MarkerInfo.h
//  Implementation of the Class MarkerInfo
//  Created on:      05-Jun-2018 14:42:05
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_603F5218_E887_49a2_ACA7_93EB2EB51BDB__INCLUDED_)
#define EA_603F5218_E887_49a2_ACA7_93EB2EB51BDB__INCLUDED_

#include "BoundingBox.h"

/**
 * Information about detected marker
 */
struct MarkerInfo
{

public:
	/**
	 * Detection confidence. Range is 0 to 100; 0 is worst, 100 is best.
	 */
	int m_Confidence;
	/**
	 * bounding box of the marker
	 */
	BoundingBox m_Marker;

};
#endif // !defined(EA_603F5218_E887_49a2_ACA7_93EB2EB51BDB__INCLUDED_)
