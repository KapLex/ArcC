%module ArcC
%{
/* Includes the header in the wrapper code */
#include "Window.h"
#include "Log.h" 
%}

/* Parse the header file to generate wrappers */
%include "Window.h"
%include "Log.h"
