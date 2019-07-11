
#define NO_DEBUG_C_FUNCTIONS

#include "DennTrisC_globalsettings.h"
#include "DennTrisC_base.h"
#include "remainder.h"

#include "head/DennTrisC_extern_functions.h"

/*
 * Some Functions like
 */
 
 
 
#ifdef DEBUG
	int DebugPrintCount=0;
#endif




int handleDebug(int argc, char **argstart){
	int err = 0;
	if (argc < 1) {
		printf("To few arguments for:\n");
		//misuse the err as loop-counter.
		for(err=-1;err<argc;err++)
			printf(" %s", *(argstart+err));
		printf("\n");
		return MAIN_ERR_FEW_CMDS;
	}
	if (strcmp(*(argstart), "") == 0){
		argc--;
		argstart++;
		if (argc < 1) {
			printf("To few arguments");
			return MAIN_ERR_FEW_CMDS;
		}
	} else if (strcmp(*(argstart), "") == 0){
	}
	return err;
}



#undef NO_DEBUG_C_FUNCTIONS
