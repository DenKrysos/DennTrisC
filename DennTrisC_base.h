#ifndef DENNTRISC_BASE_H
#define DENNTRISC_BASE_H



#include <errno.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

//#include "debug.h"


/*
 * Definition of return-error-codes
 */
#define MAIN_ERR_NONE 100
#define MAIN_ERR_STD 101
#define MAIN_ERR_WARNING 102
#define MAIN_ERR_CLEARED 103
#define MAIN_ERR_FEW_CMDS 104
#define MAIN_ERR_BAD_CMDLINE 105
#define MAIN_ERR_FUNC_INCOMPLETE 106
#define MAIN_ERR_TIMEOUT 107
#define MAIN_ERR_BAD_RUN 109
#define MAIN_ERR_CANCELED 110
//-----------------------------------------------
#define OPERATION_ERR_STD 10
#define OPERATION_ERR_NOTHING_TO_DO 11
#define OPERATION_ERR_NEVER_HAPPEN 12
#define OPERATION_ERR_NOT_SUPPORTED 13
#define OPERATION_ERR_UNSUCCESSFUL 14
//-----------------------------------------------
#define STRUCT_ERR_STD 20
#define STRUCT_ERR_DMG 21
#define STRUCT_ERR_NOT_EXIST 22
#define STRUCT_ERR_INCOMPLETE 23
//-----------------------------------------------
#define FILE_ERR_NOT_OPENED 31
#define FILE_ERR_NOT_CLOSED 32
#define FILE_ERR_PERMISSION_DENIED 33
//-----------------------------------------------
#define FUNC_ERR_TRY_AGAIN 41
//-----------------------------------------------
#define VALUE_ERR_STD 50
//-----------------------------------------------
#define ARG_ERR_STD 60
//-----------------------------------------------
#define NETWORK_CONNECTION_CLOSED 1000
#define NETWORK_NO_CONNECTION 1001
#define NETWORK_RARE_INTERFACES 1002
//-----------------------------------------------
//===============================================
//===============================================






#define CFG_FILE_MAIN_NAME "DennTrisC.cfg"
#define CFG_FILE_MAIN_SUBPATH "config/"





#ifndef NO_DENNTRISC_GLOBAL_VARIABLES

	extern unsigned char do_debug;
	extern char loglvl;
	//TODO: Define certain specified Debug-Levels
	extern char ansi_escape_use;


	extern int argsc;
	extern char **args;

	extern char system_endianess;

#endif



/* ===================================================================== */
#define ENDIANESS_LITTLE 0
#define ENDIANESS_BIG 1
#define ENDIANESS_UNKNOWN 2
/* Use this as Network Byte-Order: I.e. e.g. for the msgsize.
 * Example: A magsize of 12 (0x0C) would be sent as uint_16 like 0x00 0C, instead of 0x0C 00 */
#define ENDIANESS_SEND ENDIANESS_BIG
/* ===================================================================== */







#define ANSI_COLOR_BLACK "\033[22;30m"
#define ANSI_COLOR_RED "\033[22;31m"
#define ANSI_COLOR_GREEN "\033[22;32m"
#define ANSI_COLOR_BROWN "\033[22;33m"
#define ANSI_COLOR_BLUE "\033[22;34m"
#define ANSI_COLOR_MAGENTA "\033[22;35m"
#define ANSI_COLOR_CYAN "\033[22;36m"
#define ANSI_COLOR_GRAY "\033[22;37m"
#define ANSI_COLOR_DARK_GRAY "\033[01;30m"
#define ANSI_COLOR_LIGHT_RED "\033[01;31m"
#define ANSI_COLOR_LIGHT_GREEN "\033[01;32m"
#define ANSI_COLOR_YELLOW "\033[01;33m"
#define ANSI_COLOR_LIGHT_BLUE "\033[01;34m"
#define ANSI_COLOR_LIGHT_MAGENTA "\033[01;35m"
#define ANSI_COLOR_LIGHT_CYAN "\033[01;36m"
#define ANSI_COLOR_WHITE "\033[01;37m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define ANSI_COLOR_black ANSI_COLOR_BLACK
#define ANSI_COLOR_red ANSI_COLOR_RED
#define ANSI_COLOR_green ANSI_COLOR_GREEN
#define ANSI_COLOR_brown ANSI_COLOR_BROWN
#define ANSI_COLOR_blue ANSI_COLOR_BLUE
#define ANSI_COLOR_magenta ANSI_COLOR_MAGENTA
#define ANSI_COLOR_cyan ANSI_COLOR_CYAN
#define ANSI_COLOR_gray ANSI_COLOR_GRAY
#define ANSI_COLOR_dark_gray ANSI_COLOR_DARK_GRAY
#define ANSI_COLOR_light_red ANSI_COLOR_LIGHT_RED
#define ANSI_COLOR_light_green ANSI_COLOR_LIGHT_GREEN
#define ANSI_COLOR_yellow ANSI_COLOR_YELLOW
#define ANSI_COLOR_light_blue ANSI_COLOR_LIGHT_BLUE
#define ANSI_COLOR_light_magenta ANSI_COLOR_LIGHT_MAGENTA
#define ANSI_COLOR_light_cyan ANSI_COLOR_LIGHT_CYAN
#define ANSI_COLOR_white ANSI_COLOR_WHITE
#define ANSI_COLOR_reset ANSI_COLOR_RESET

#define ANSI_COLOR_Black ANSI_COLOR_BLACK
#define ANSI_COLOR_Red ANSI_COLOR_RED
#define ANSI_COLOR_Green ANSI_COLOR_GREEN
#define ANSI_COLOR_Brown ANSI_COLOR_BROWN
#define ANSI_COLOR_Blue ANSI_COLOR_BLUE
#define ANSI_COLOR_Magenta ANSI_COLOR_MAGENTA
#define ANSI_COLOR_Cyan ANSI_COLOR_CYAN
#define ANSI_COLOR_Gray ANSI_COLOR_GRAY
#define ANSI_COLOR_Dark_gray ANSI_COLOR_DARK_GRAY
#define ANSI_COLOR_Light_Red ANSI_COLOR_LIGHT_RED
#define ANSI_COLOR_Light_Green ANSI_COLOR_LIGHT_GREEN
#define ANSI_COLOR_Yellow ANSI_COLOR_YELLOW
#define ANSI_COLOR_Light_Blue ANSI_COLOR_LIGHT_BLUE
#define ANSI_COLOR_Light_Magenta ANSI_COLOR_LIGHT_MAGENTA
#define ANSI_COLOR_Light_Cyan ANSI_COLOR_LIGHT_CYAN
#define ANSI_COLOR_White ANSI_COLOR_WHITE
#define ANSI_COLOR_Reset ANSI_COLOR_RESET





//Logging
//Level-Values
//Flags
#define LOG_LVL_BASIC 0x01
//#define LOG_LVL_ 0x02
//#define LOG_LVL_ 0x04
//#define LOG_LVL_ 0x08
//#define LOG_LVL_ 0x11
//#define LOG_LVL_ 0x12
//#define LOG_LVL_ 0x14
//#define LOG_LVL_ 0x18



#endif /* DENNTRISC_BASE_H */
