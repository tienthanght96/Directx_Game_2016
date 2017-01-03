#include "m2dxutil.h"

string getFileNameWithoutExtension(LPCSTR fileName)
{
	return ((string)fileName).substr(0, ((string)fileName).find_last_of("."));
}
