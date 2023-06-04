#include "C3DMarkers.h"

C3dMarker *C3dMarker::pool() {
	return (C3dMarker *)0xC7DD58;
}

CCheckpoint *CCheckpoint::pool() {
	return (CCheckpoint *)0xC7F158;
}
