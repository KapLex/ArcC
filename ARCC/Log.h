/** \file Log.h
    \brief

    Interface to logging functionality
*/

#ifndef _LOG_H_
#define _LOG_H_

// Std
#include <stdbool.h>
#include <string.h>

// Log4c
#include <log4c.h>

// SDL + GL
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

log4c_category_t* rootLog;

/**
 * Initialize logging to desired appender
 * Appenders can be: "stdout", "file.log"
 *
 * Note: ARC_Quit() closes the log subsystem (as well as other subsystems) file for us
 */
int ARC_InitLogger(char *appender);

#ifdef __cplusplus
}
#endif


#endif
