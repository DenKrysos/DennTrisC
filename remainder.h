#ifndef REMAINDER_H
#define REMAINDER_H


#include "DennTrisC_globalsettings.h"

/*
 * Just a bunch of helpful functions/makros
 * Especially used for debugging/developing
 * Or something nice like the ansi_escape_use setting
 */

#include <pwd.h>




extern int getDigitCountofInt(int n);






#define BYTETOBINPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBIN(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

/* Use like:
char testchar=0x02;
printf("Bsp Convert Hex: %02X to Bin "BYTETOBINPATTERN"\n",testchar, BYTETOBIN(testchar));
*/















//For now just hardcoded and use ANSI Escape on the Output Console
//Later on maybe something like a config File Read-In with possible Values:
// on, off, auto
//and than with the auto something like the crazy Lookup-Table Stuff, that ncurses does.
#define SET_ansi_escape_use ansi_escape_use = 1;


//And a macro for the quick programming use of changing the Console Color
#define ANSICOLORSET(ANSIcolorToSet) if(ansi_escape_use==1){ \
		printf(ANSIcolorToSet); \
	}

#define ANSICOLORRESET if(ansi_escape_use==1){ \
		printf(ANSI_COLOR_RESET); \
	}
//And to make it still shorter:
#define printfc(color,...) ANSICOLORSET(ANSI_COLOR_##color); \
printf(__VA_ARGS__); \
ANSICOLORRESET;


//Macros to Set or Unset a flag
#define FLAG_SET(FlagHolder,Flag) (FlagHolder)=(FlagHolder) | (Flag)

#define FLAG_UNSET(FlagHolder,Flag) (FlagHolder)=(FlagHolder) & (~(Flag))

#define FLAG_CHECK(FlagHolder,Flag) ((FlagHolder) & (Flag))


//It gets a Pointer to a string
//About the String-Size: Minus the "denntrisc", but with +1 for the '\0'
//NOTE: The initial arguments, that are given to the program at Terminal-Call should be
//globally stored in "args".
//This means, you are able to call this Macro everywhere like "CREATE_PROGRAM_PATH(*args);
#ifdef FILES_LOCAL_OR_IN_PROJECT
	#ifdef FILES_GLOBAL_OR_USER_SPECIFIC
		#define CREATE_PROGRAM_PATH(arg) \
			char ProgPath[]="/etc/DennTrisC/";
			//printf("ProgPath %s | %d\n",ProgPath[0-5],sizeof(ProgPath));exit(1);
	#else
		#define CREATE_PROGRAM_PATH(arg) \
			{ \
				char *tmppath; \
				if ((tmppath = getenv("XDG_CONFIG_HOME")) == NULL) { \
					if ((tmppath = getenv("HOME")) == NULL) { \
						tmppath = getpwuid(getuid())->pw_dir; \
					} \
				} \
				/* len=strlen(Ascertained_Path)+strlen("\DennTrisC\")+'\0' */ \
				err=(strlen(tmppath)+12); \
			} \
			char ProgPath[err]; \
			{ \
				char *tmppath; \
				if ((tmppath = getenv("XDG_CONFIG_HOME")) == NULL) { \
					if ((tmppath = getenv("HOME")) == NULL) { \
						tmppath = getpwuid(getuid())->pw_dir; \
					} \
				} \
				memcpy(ProgPath,tmppath,strlen(tmppath)+1); \
				snprintf(ProgPath+strlen(tmppath),12,"/DennTrisC/"); \
				ProgPath[sizeof(ProgPath)]='\0'; \
			}
	#endif
#else
	#define CREATE_PROGRAM_PATH(arg) char ProgPath[strlen(arg)-8]; \
		memcpy(ProgPath,arg,sizeof(ProgPath)); \
		ProgPath[sizeof(ProgPath)-1]='\0';
#endif


/*Everything is in a scope*/
/*Give this Macro a string with the preceding '/' after the last folder*/
/*This is IMPORTANT or the last folder isn't created*/
/*Example: "/folderA/folderB/folderC/"  */
#define CREATE_COMPLETE_FOLDER_PATH(path) { \
	int pathloop; \
	struct stat st = {0}; \
	char temppath[sizeof(path)]; \
	memset(temppath,0,sizeof(temppath)); \
	for(pathloop=1;pathloop<strlen(path);pathloop++){ \
		if(path[pathloop]=='/'){ \
			memcpy(temppath,path,pathloop); \
			/*temppath[pathloop]='\0';*/ \
			if (stat(temppath, &st) == -1) { \
				mkdir(temppath,S_IRWXU|S_IRWXG|S_IRWXO); \
			} \
		} \
	} \
} \



//Macro "returns" the number of passed arguments
//Current Implementation: A Maximum of 5
//Easily extendible (in an obvious way...) to up to 63
//(which reaches the limit of preprocessor arguments anyway...)
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_VARARGS(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
//Ähnliche Funktion, kann aber nicht mit "leeren" variadic arguments umgehen
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 5,4,3,2,1)
#define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,N,...) N




//Use this to specify Mili-Seconds from Nano-Seconds
#define MS_TO_NS(MS) MS ## 000000

#define WAITNS(SEC,NSEC) { \
	struct timespec remainingdelay; \
	remainingdelay.tv_sec = SEC; \
	remainingdelay.tv_nsec = NSEC; \
	while (nanosleep(&remainingdelay, &remainingdelay)<0){} \
}



#endif /* REMAINDER_H */
