///////////////////////////////////////////////////////////
//  Diagnostics.h
//  Implementation of the Class Diagnostics
//  Created on:      05-Jun-2018 14:42:02
//  Original author: student
///////////////////////////////////////////////////////////

#if !defined(EA_8F25F8E8_7CC1_46ca_8FF0_29AD3992A595__INCLUDED_)
#define EA_8F25F8E8_7CC1_46ca_8FF0_29AD3992A595__INCLUDED_

class Diagnostics
{

public:
	Diagnostics();
	virtual ~Diagnostics();

	static void log(DiagnosticLevel level, const char* file, int line, const char* const msg, ... prm1);
	static void setMaxLevel(DiagnosticLevel level);

};
#endif // !defined(EA_8F25F8E8_7CC1_46ca_8FF0_29AD3992A595__INCLUDED_)
