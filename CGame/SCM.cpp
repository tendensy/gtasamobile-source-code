#include "SCM.h"

SCMThread::SCMThread( int buff ) : bufferSize( buff ) {
	gst		  = new GAME_SCRIPT_THREAD;
	ScriptBuf = new byte[buff];
	reset();
}

SCMThread::~SCMThread() {
	delete ScriptBuf;
	delete gst;
}

void SCMThread::reset() {
	ZeroMemory( gst, sizeof( GAME_SCRIPT_THREAD ) );
	ZeroMemory( ScriptBuf, bufferSize );
}

void SCMThread::resizeBuffer( int buff ) {
	byte *newBuffer = new byte[buff];
	if ( buff > bufferSize ) memcpy( newBuffer, ScriptBuf, bufferSize );
	delete ScriptBuf;
	ScriptBuf  = newBuffer;
	bufferSize = buff;
}

int SCMThread::getBufferSize() {
	return bufferSize;
}

int SCMThread::ScriptCommand( const SCRIPT_COMMAND *pScriptCommand, ... ) {
	va_list		ap;
	const char *p = pScriptCommand->Params;			  // Get parameter string.
	va_start( ap, pScriptCommand );					  // Initialize varargs.
	memcpy( &ScriptBuf, &pScriptCommand->OpCode, 2 ); // Copy opcode to script buf.
	int	 buf_pos = 2;								  // Position in buffer after opcode.
	WORD var_pos = 0;								  // Init var_pos.

	// (aru) Reset all vars before proceeding (To fix some nasty 0x00465CB4 crashes)
	// May cause problems with functions that use local vars returned from previous calls
	for ( int i = 0; i < 18; i++ ) gst->dwLocalVar[i] = 0;

	while ( *p ) // While we've not ran out of parameters...
	{
		switch ( *p ) // Switch current parameter.
		{
			case 'i': // If integer...
			{
				int i			   = va_arg( ap, int ); // Grab an int off the stack.
				ScriptBuf[buf_pos] = 0x01;				// Variable data type = 0x01 (4b int).
				buf_pos++;
				;

				// Increment buffer position.
				memcpy( &ScriptBuf[buf_pos], &i, 4 ); // Insert the int.
				buf_pos += 4;						  // Increment buffer by 4b.
				break;
			}

			case 'f': // If float...
			{
				float f			   = (float)va_arg( ap, double ); // Get float off the stack.
				ScriptBuf[buf_pos] = 0x06;						  // Variable data type = 0x06 (float).
				buf_pos++;										  // Increment buffer position.
				memcpy( &ScriptBuf[buf_pos], &f, 4 );			  // Copy float into script buf.
				buf_pos += 4;									  // Increment buffer by 4b.
				break;
			}

			case 'v': // If variable...
			{
				DWORD *v		   = va_arg( ap, DWORD * ); // Get the pointer to the passed variable.
				ScriptBuf[buf_pos] = 0x03;					// Variable data type = 0x03 (Local Var).
				buf_pos++;									// Increment buffer position.
				pdwParamVars[var_pos]	 = v;				// Save pointer to passed variable.
				gst->dwLocalVar[var_pos] = *v;				// Put value of passed variable into local.
				memcpy( &ScriptBuf[buf_pos], &var_pos, 2 ); // Copy the offset into the script.
				buf_pos += 2;								// Increment buffer by 2b.
				var_pos++;									// Increment the variable position.
				break;
			}
			case 's': // If string... Updated 13th Jan 06.. (kyeman) SA string support
			{
				char *		  sz   = va_arg( ap, char * );
				unsigned char aLen = strlen( sz );
				ScriptBuf[buf_pos] = 0x0E;
				buf_pos++;
				ScriptBuf[buf_pos] = aLen;
				buf_pos++;
				memcpy( &ScriptBuf[buf_pos], sz, aLen );
				buf_pos += aLen;
				break;
			}
			case 'z': // If the params need zero-terminating...
			{
				ScriptBuf[buf_pos] = 0x00;
				buf_pos++;
				break;
			}
			default: {
				return 0;
			}
		}

		++p; // Next parameter
	}

	va_end( ap ); // End varargs.

	// Execute script stub.
	gst->dwScriptIP = ScriptBuf;
	typedef void( __thiscall * ExecuteScriptBuf )( GAME_SCRIPT_THREAD * _this );
	( ExecuteScriptBuf( 0x469EB0 ) )( gst );

	if ( var_pos ) // if we've used a variable...
	{
		for ( int i = 0; i < var_pos; i++ ) // For every passed variable...
		{
			*pdwParamVars[i] = gst->dwLocalVar[i]; // Retrieve variable from local var.
		}
	}

	return gst->dwIfFlag;
}
