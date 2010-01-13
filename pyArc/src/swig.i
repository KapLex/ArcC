%module ArcC
%{
/* Includes the header in the wrapper code */
#include "Font.h"
#include "Log.h"
#include "Time.h"
#include "Window.h"  
%}

/* Parse the header file to generate wrappers */
%include "Font.h"
%include "Log.h"
%include "Time.h"
%include "Window.h" 

