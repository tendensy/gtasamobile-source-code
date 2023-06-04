#ifndef CBONE_H
#define CBONE_H

#include "Types.h"
#include "CHAnimIFrame.h"

namespace BodyPed{
	namespace Head{
		enum{
			Throat = 4,
			Neck,
			Brain,
			zzz_RightTemple, // Does not use it ))
			Face
		};
	};
	namespace Torso{
		enum {
			Groin = 1,
			Venter,
			Chest
		};
	};
	namespace Arms{
		namespace Left{
			enum {
				Forearm = 31,
				Shoulder,
				Elbow,
				Wrist,
				Truss,
				Fingers
			};
		};
		namespace Right{
			enum {
				Forearm = 21,
				Shoulder,
				Elbow,
				Wrist,
				Truss,
				Fingers
			};
		};
	};
	namespace Legs{
		namespace Left{
			enum{
				Hip = 41,
				Knee,
				Shin,
				Foot
			};
		};
		namespace Right{
			enum{
				Hip = 51,
				Knee,
				Shin,
				Foot
			};
		};
	};
};

class CBone
{
public:
	BYTE          m_bFlags;
	RwV3D         m_vOffset;  // Статичное смещение относительно родительской кости
	CHAnimIFrame *m_pIFrame;  // Указатель на структуру, которая содержит интерполированные данные о положении кости
	DWORD         m_dwNodeId; // Специальный идентификатор кости
};

#endif // CBONE_H
