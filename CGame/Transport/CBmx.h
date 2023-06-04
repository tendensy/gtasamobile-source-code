#ifndef CBMX_H
#define CBMX_H

#include "CBike.h"

class CBmx : public CBike {
public:
	float		  field_814;
	float		  field_818;
	float		  field_81C;
	float		  field_820;
	float		  field_824;
	float		  field_828;
	float		  m_fDistanceBetweenWheels;
	float		  m_fWheelsBalance;
	unsigned char field_834;
	char		  _pad[3];
};

VALIDATE_SIZE( CBmx, 0x838 );

#endif // CBMX_H
