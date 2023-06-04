#ifndef SCM_H
#define SCM_H

#include "Types.h"

#define MAX_SCRIPT_VARS 16                  // Size of our variable saving array
#define MAX_SCRIPT_SIZE 255                 // Size of ScriptBuf - Max is really (2+(13*5))

struct SCRIPT_COMMAND						// Params:
{											//	i = integer
	WORD    OpCode;							//	f = float
	char    Params[MAX_SCRIPT_VARS];		//	v = variable
};											//	s = string

class SCMThread
{
	struct GAME_SCRIPT_THREAD				// 0xE0 bytes total.
	{
		BYTE    Pad1[0x14];					// 0x00 [0x14]
		BYTE    *dwScriptIP;				// 0x14 [0x04]
		BYTE    Pad2[0x24];					// 0x18 [0x24]
		DWORD   dwLocalVar[18];				// 0x3C [0x48]
		BYTE    Pad3[0x41];					// 0x84 [0x41]
		DWORD   dwIfFlag;					// 0xC5 [0x04]
		BYTE    Pad4[0xF];					// 0xC9 [0x0F]
		DWORD   dwIndexSomething;			// 0xD8 [0x04]  (indexes into 0xA49960)
		BYTE    bHasLocalCopy;				// 0xDC [0x01]  (has local copy of something, if 1, then uses .data:00A48960 CTheScripts_LocalCopy instead of var0)
		BYTE    Pad5[0x3];					// 0xDD [0x03]
	};
	GAME_SCRIPT_THREAD *gst;
	BYTE *ScriptBuf;
	DWORD *pdwParamVars[18];
	int bufferSize;
public:
	SCMThread(int buff = 256);
	virtual ~SCMThread();

	virtual void reset();
	virtual void resizeBuffer(int buff);
	virtual int getBufferSize();

	virtual int ScriptCommand(const SCRIPT_COMMAND *pScriptCommand, ...);
};

#endif // SCM_H
