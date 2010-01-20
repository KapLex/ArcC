
#include "Log.h"
#include "Types.h"

int ARC_InitLogger(char* appender)
{
	if (log4c_init())
	{
		// failed to init
		printf("Failed to initialize log4c");
		return EXIT_FAILURE;
	}
	else
	{
		rootLog = log4c_category_get("root");
		log4c_category_set_appender(rootLog, log4c_appender_get(appender));
	}

	return ARC_SUCCESS;
}
