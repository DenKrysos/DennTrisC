


#define NO_MAIN_FUNCTION_C_FUNCTIONS



#include <string.h>
#include <time.h>
#include <ctype.h>
#include <linux/types.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <endian.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include "DennTrisC_globalsettings.h"
#include "DennTrisC_base.h"
#include "remainder.h"
#include "debug.h"


#include "remainder_extended.h"
#include "socket_stuff.h"

#include "head/DennTrisC_extern_functions.h"






int dauerbetrieb(int argc, char **argv){
	#define msgstruct ((struct MsgPython *)(msg_recvd))
	int err;


	UNIX_SOCKET_C_PYTHON_CLIENT_CONNECT;

    msgsizePy bytes_recvd;
    struct MsgPython *msg_recvd=NULL;

    bytes_recvd=recvPyMsg(socket_Python,&msg_recvd);
//    Test-Output
//    int k=0;
//    for(;k<=bytes_recvd;k++){
//    	printf("%c : %d : 0x%x | %d\n",*(msg_recvd+k),*(msg_recvd+k),*(msg_recvd+k),k);
//    
//	printf("Msgtype: %d | ",msgstruct->type);print_uint64_t_hex(msgstruct->type);puts("");
//	printf("Block IDx: %d\n",((struct MsgPythonBlockIdx *)(msg_recvd))->block_idx);

    struct MsgPython *msg_send=NULL;
    int msg_send_size;

	err=createPyMsg(&msg_send_size, &msg_send, MSG_TYPE_PY_C_WANT_BLOCK, 2);
//	puts("");print_uint64_t_hex((uint64_t)(((struct MsgPythonBlockIdx *)(msg_recvd))->block_idx));puts("");
//	for(err=0;err<=2;err++){
//		puts("");print_uint64_t_hex((uint64_t)(*(((char*)(msg_send))+sizeof(msgtypePy)+err)));puts("");
//	}

    err=sendPyMsg(socket_Python,msg_send,msg_send_size);




	return err;
	#undef msgstruct
}




#undef NO_MAIN_FUNCTION_C_FUNCTIONS
