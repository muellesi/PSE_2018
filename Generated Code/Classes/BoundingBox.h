///////////////////////////////////////////////////////////
//  BoundingBox.h
//  Implementation of the Class BoundingBox
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_FA3F3D84_2C2F_493c_8840_6D42BF33B706__INCLUDED_)
#define EA_FA3F3D84_2C2F_493c_8840_6D42BF33B706__INCLUDED_

#include "Color.h"

/**
 * Helper class to track and draw bounding boxes on screen.
 */
class BoundingBox
{

public:
	virtual ~BoundingBox();

	BoundingBox();
	BoundingBox(int x, int y, int width, int height, int regionID);
	static bool areaLt(const BoundingBox& first, const BoundingBox& second){

		return false;
	}
	void draw(struct SDL_Surface* surface);
	void drawMarker(struct SDL_Surface* surface);
	int getArea() const;
	int getHeight() const{

		return 0;
	}
	int getRegionID() const{

		return 0;
	}
	int getWidth() const{

		return 0;
	}
	void grow(int amount);
	bool isOverlapping(const BoundingBox& other) const;
	void join(const BoundingBox& other);
	void setPen(Color color){

	}
	int x() const{

		return 0;
	}
	static bool xLt(const BoundingBox& first, const BoundingBox& second){

		return false;
	}
	int y() const{

		return 0;
	}
	static bool yLt(const BoundingBox& first, const BoundingBox& second){

		return false;
	}

protected:
	int m_Height;
	bool m_IsEmpty;
	Color m_PenColor;
	int m_RegionID;
	int m_Width;
	int m_X;
	int m_Y;

};
#endif // !defined(EA_FA3F3D84_2C2F_493c_8840_6D42BF33B706__INCLUDED_)
