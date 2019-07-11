#ifndef DEBUG_H
#define DEBUG_H

#include <limits.h>//For maximum limits of Data-Types
#include <float.h>//Same for floats

#include "DennTrisC_globalsettings.h"

/*
 * Some Functions like 
 */




#define print_malloc_size(voidpoint) { \
	size_t mallocsize=malloc_usable_size(voidpoint); \
	ANSICOLORSET(ANSI_COLOR_BLUE); \
	printf("Allocated size: %d",(int)mallocsize); \
	ANSICOLORRESET; \
	printf("\n"); \
}
	
	
	

//Debug Print (simple ones)
//A sophisticated, big brother, which covers this all here
//together by overloading mechanism lays down under
#ifdef DEBUG
	extern int DebugPrintCount;
#endif
#ifdef DEBUG
	#define deprl(...) printfc(blue,"\n==> "); \
		printfc(green,"Debug "); \
		printfc(cyan,"Line "); \
		printfc(red,"%d",__LINE__); \
		printfc(green," (#%d)",DebugPrintCount); \
		printf(" | "__VA_ARGS__); \
		puts(""); \
		DebugPrintCount++;
#else
	#define deprl(...)
#endif
#ifdef DEBUG
	#define depri(idx,...) printfc(blue,"\n==> "); \
		printfc(green,"Debug "); \
		printfc(cyan,"Idx "); \
		printfc(red,#idx); \
		printfc(green," (#%d)",DebugPrintCount); \
		printf(" | "__VA_ARGS__); \
		puts(""); \
		DebugPrintCount++;
#else
	#define depri(...)
#endif


//Debug Print
//Works differently, with a differing Number of delivered Arguments
//Could be anything from 0 to gratuitious amounts of Arguments
/* Use like this:
 * The Arguments:
 * depr(); Prints Line Number of Makro Usage and an incrementing Counter
 * depr(Index); Additionally the delivered Index
 * depr(Index,String); Additionally a String, like basic printf
 * depr(Index,String,StringArgs); Additionally Arguments for the preceding String, like with printf
 * Full Command Example:
 * depr(1,"Test float: %lf",floatvariable);
 */
#ifdef DEBUG
	extern int DebugPrintCount;
#endif
#ifdef DEBUG
	#define deprColorPrefix blue
	#define deprColorDebug green
	#define deprColorIndex magenta
	#define deprColorIndexNumber red
	#define deprColorLine cyan
	#define deprColorCounter brown
	#define deprExpandprintfc(color,...) printfc(color,__VA_ARGS__)

	#define macro_overloader(func, ...) \
		macro_overloader_(func, COUNT_VARARGS(__VA_ARGS__))
	#define macro_overloader_(func, nargs) \
		macro_overloader__(func, nargs)
	#define macro_overloader__(func, nargs) \
		func ## nargs

	#define depr(...) macro_overloader(depr, __VA_ARGS__)(__VA_ARGS__)
	#define depr0(...) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorLine,"Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d",__LINE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		puts(""); \
		DebugPrintCount++;
	#define depr1(idx) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorIndex,"Idx "); \
		deprExpandprintfc(deprColorIndexNumber,#idx); \
		deprExpandprintfc(deprColorLine," Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d",__LINE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		puts(""); \
		DebugPrintCount++;
	#define depr2(idx,...) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorIndex,"Idx "); \
		deprExpandprintfc(deprColorIndexNumber,#idx); \
		deprExpandprintfc(deprColorLine," Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d",__LINE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		printf(" | "__VA_ARGS__); \
		puts(""); \
		DebugPrintCount++;
	#define depr3(idx,...) deprExpandprintfc(deprColorPrefix,"\n==> "); \
		deprExpandprintfc(deprColorDebug,"Debug "); \
		deprExpandprintfc(deprColorIndex,"Idx "); \
		deprExpandprintfc(deprColorIndexNumber,#idx); \
		deprExpandprintfc(deprColorLine," Line "); \
		deprExpandprintfc(deprColorIndexNumber,"%d",__LINE__); \
		deprExpandprintfc(deprColorCounter," (#%d)",DebugPrintCount); \
		printf(" | "__VA_ARGS__); \
		puts(""); \
		DebugPrintCount++;
	#define depr4(idx,...) depr3(idx,__VA_ARGS__)
	#define depr5(idx,...) depr3(idx,__VA_ARGS__)
	#define depr6(idx,...) depr3(idx,__VA_ARGS__)
	#define depr7(idx,...) depr3(idx,__VA_ARGS__)
	#define depr8(idx,...) depr3(idx,__VA_ARGS__)
	#define depr9(idx,...) depr3(idx,__VA_ARGS__)
#else
	#define depr(...)
#endif
//NOTE:
// - depr2(idx,...) could be depr2(idx, str) instead
// - depr3(idx,...) could be depr3(idx, str, format) instead





#endif /* DEBUG_H */
