

#include "DennTrisC_globalsettings.h"
#include "DennTrisC_base.h"
#include "remainder.h"

#include "remainder_extended.h"





//to predefine the void, to be used in the handleHelp
//But better define the complete void down there, well, because its optical better
//to let the handleHelp stand at top

int handleHelp(int argc, char **argstart){
	int err = 0;
	if (argc < 3) {
		printf("To few arguments for:\n");
		//misuse the err as loop-counter.
		for(err=0;err<argc;err++)
			printf(" %s", *(argstart+err));
		printf("\n");
		return MAIN_ERR_FEW_CMDS;
	}
	if (strcmp(*(argstart+1), "print") == 0) {
		if (strcmp(*(argstart+2), "iftype") == 0) {
		}
		else if (strcmp(*(argstart+2), "cmdatts") == 0) {
		}
//		else if (strcmp(*(argstart+2), "") == 0) { }
		else {
			printf("Invalid parameter after print: %s\nExpected <iftype | >", *(argstart+2));
			return MAIN_ERR_BAD_CMDLINE;
		}
	}
//	err = send_with_cmdContainer(sktctr, argc, argstart, cmd);

	return err;
}




