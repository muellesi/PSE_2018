///////////////////////////////////////////////////////////
//  Color.h
//  Implementation of the Class Color
//  Created on:      05-Jun-2018 14:42:01
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_368FC462_12DC_4cdc_BBA5_6D43D53D4FD0__INCLUDED_)
#define EA_368FC462_12DC_4cdc_BBA5_6D43D53D4FD0__INCLUDED_

/**
 * RGB Color
 */
class Color
{

public:
	virtual ~Color();

	Color()
	    : Color(0, 0, 0)
	{

	}
	Color(unsigned char r, unsigned char g, unsigned char b)
	    : m_R(r),m_G(g),m_B(b)
	{

	}
	unsigned char b() const{

		return 0;
	}
	unsigned char g() const{

		return 0;
	}
	unsigned char r() const{

		return 0;
	}

private:
	unsigned char m_B;
	unsigned char m_G;
	unsigned char m_R;

};
#endif // !defined(EA_368FC462_12DC_4cdc_BBA5_6D43D53D4FD0__INCLUDED_)
