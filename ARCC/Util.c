
#include "Util.h"

bool ARC_UtilFileExists(char * filename)
{
	FILE* file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}
