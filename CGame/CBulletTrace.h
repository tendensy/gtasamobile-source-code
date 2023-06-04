#ifndef CBULLETTRACE_H
#define CBULLETTRACE_H

#include "Types.h"

#pragma pack( push, 1 )
struct CBulletTrace {
	RwV3D from;
	RwV3D to;
	bool isExist;
	uint8_t _pad[3];
	uint32_t createTime;
	uint32_t lifeTime;
	float radius;
	uint8_t alpha;
	uint8_t _pad2[3];
};
#pragma pack( pop )

#endif // CBULLETTRACE_H
