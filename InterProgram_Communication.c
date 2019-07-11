


#define NO_INTERPROGRAM_COMMUNICATION_C_FUNCTIONS



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
#include <stdarg.h>

#include "DennTrisC_globalsettings.h"
#include "DennTrisC_base.h"
#include "remainder.h"
#include "debug.h"


#include "remainder_extended.h"
#include "socket_stuff.h"

#include "head/DennTrisC_extern_functions.h"



//################################################################################################################################
//################################################################################################################################
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//				Python Section
//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################
//################################################################################################################################






int DennTris_Python_Connection_Loss_Server(){
	printfc(red,"ERROR");
	printf(": Lost Connection to the Python-Program.\n");
	printf("TODO: DennTris_Python_Connection_Loss\n");

	return 0;
}

int DennTris_Python_Connection_Loss_Client(){
	printfc(red,"ERROR");
	printf(": Lost Connection to the Python-Program.\n");
	printf("TODO: DennTris_Python_Connection_Loss\n");

	return 0;
}


/* The delivered msg is one byte larger than bytes_recvd
 * and appendixed with a '\0' */
/* Be careful with the passed msg Pointer. It should be properly initialized and tracked.
 * I.e.: If it isn't malloced, it should be == NULL */
int recvPyMsgContentString(int sock, char **msg, msgsizePy msgsiz){
    msgsizePy bytes_recvd;

//    depr(1,"%d",msgsiz)
    if(*msg){
    	free(*msg);
    }
	*msg=malloc(msgsiz+1);
	if(msgsiz>0){
		bytes_recvd=recv(sock,*msg,msgsiz,0);
		while(bytes_recvd<msgsiz){
			bytes_recvd+=recv(sock,*msg+bytes_recvd,msgsiz-bytes_recvd,0);
		}
		(*msg)[bytes_recvd]='\0';
	}
	return bytes_recvd;
}



int recvPyMsgContent(int sock, struct MsgPython **msg, msgsizePy msgsiz){
	#define msgstruct ((struct MsgPython *)(*msg))
    msgsizePy bytes_recvd;
	msgsizePy msgsizeAndType;
	
	msgsizeAndType=msgsiz+sizeof(msgtypePy);

    if(*msg){
    	free(*msg);
    }
//    depr(1,"%d | %d",msgsiz,msgsizeAndType)
	*msg=malloc(msgsizeAndType);
		bytes_recvd=recv(sock,*msg,msgsizeAndType,0);
		while(bytes_recvd<msgsizeAndType){
			bytes_recvd+=recv(sock,(*msg)+bytes_recvd,msgsizeAndType-bytes_recvd,0);
		}
		//Maybe some check "Type against Size" to secure if some Type needs Payload.
	NET_ENDIAN_CONVERT_GENERAL((*msg)->type,sizeof(msgtypePy))
	switch((*msg)->type){
	case MSG_TYPE_PY_C_GOT_BLOCK:
		#if (SIZEOF_msg_to_Py_Block_Idx > 1)
		NET_ENDIAN_CONVERT_GENERAL(((struct MsgPythonBlockIdx *)(*msg))->block_idx,sizeof(msg_to_Py_Block_Idx));//Not necessary, just 1 Byte
		#endif
		break;
	case MSG_TYPE_PY_C_MISC:
		/* Be careful, this delivers back a "char-Array". It could be just a bunch of Bytes or
		 * a String. If it is a String it is NOT Null-terminated. Use the received-bytes as help
		 * or for further conversion */
		break;
	}
	return bytes_recvd;
	#undef msgstruct
}


/* You could either pass it the address of a char* or properly a struct MsgPython*.
 * But after return be careful and at least use it castet. */
/* Be careful with the passed msg Pointer. It should be properly initialized and tracked.
 * I.e.: If it isn't malloced, it should be == NULL */
/* After you're finished with the Content of the received Msg you could/should free the Pointer */
int recvPyMsg(int sock, struct MsgPython **msg){
	msgsizePy msgsiz;
    msgsizePy bytes_recvd;

    if((bytes_recvd=recv(sock,&msgsiz,sizeof(msgsizePy),0))>0){
    	MSGSIZE_PY_ENDIAN(msgsiz);
    	bytes_recvd=recvPyMsgContent(sock, msg, msgsiz);
    }else{
    	DennTris_Python_Connection_Loss();
    }
    return bytes_recvd;
}



/* This function doesn't free the passed msg-Pointer. If it's something dynamic do it outside the function.
 * Maybe you want to use a static array anyhow, so that there isn't anything about memory-management or free or all this ;) ... */
int sendPyMsg(int sock, struct MsgPython *msg, int sendbytes){
	int err;
	msgsizePy msgsizpy=sendbytes;
	MSGSIZE_PY_ENDIAN(msgsizpy);
	int sendbytescomplete=sendbytes+sizeof(msgsizePy)+sizeof(msgtypePy);
	char *send_msg=malloc(sendbytescomplete);
	memcpy(send_msg,&msgsizpy,sizeof(msgsizePy));
	memcpy(send_msg+sizeof(msgsizePy),msg,sendbytes+sizeof(msgtypePy));
	NET_ENDIAN_CONVERT_GENERAL(*(send_msg+sizeof(msgsizePy)),sizeof(msgtypePy));
    err=senddetermined(sock,send_msg,sendbytescomplete);
    free(send_msg);
    return err;
}



/* You don't have to fill in the msgsize. You get it delivered Back by the Pointer (First Argument).
 * But if you pass a String or Array (MsgType Misc or something i not know yet ;oP ) give the Size of it directly after itself. */
int createPyMsg(int *msgsize, struct MsgPython **msg, msgtypePy msgtyp, ...){
	int err=0;
	va_list variadics;

	va_start(variadics,msgtyp);
	switch(msgtyp){
	case MSG_TYPE_PY_C_WANT_BLOCK:
		*msgsize=sizeof(msg_to_Py_Block_Idx);
//		*msg=malloc(sizeof(msgtypePy)+sizeof(msg_to_Py_Block_Idx));
		*msg=malloc(sizeof(struct MsgPythonBlockIdx));
		(*msg)->type=msgtyp;
		((struct MsgPythonBlockIdx *)(*msg))->block_idx = (msg_to_Py_Block_Idx)va_arg(variadics,int);
		#if (SIZEOF_msg_to_Py_Block_Idx > 1)
//		NET_ENDIAN_CONVERT_GENERAL(((struct MsgPythonBlockIdx *)(*msg))->block_idx);//Not necessary, is only one Byte...
		#endif
		break;
	case MSG_TYPE_PY_C_MISC:
		;
		char *msgstr=va_arg(variadics,char*);
		int sendbytes=va_arg(variadics,int);
		//Check, if we got a string with Null-terminating Character.
		//We don't have to send the '\0'
		if(msgstr[sendbytes-1]=='\0')
			sendbytes--;
		*msgsize=sendbytes;
		*msg=malloc(sizeof(msgtypePy)+sendbytes);
		(*msg)->type=msgtyp;
		memcpy(&(((struct MsgPythonMisc *)(*msg))->misc),msgstr,sendbytes);
		break;
	default:
		*msgsize=0;
		err=ARG_ERR_STD;
		break;
	}

	// The Endian_Convert is done inside the Send-Function
//	NET_ENDIAN_CONVERT_GENERAL((*msg)->type,sizeof(msgtypePy))

	va_end(variadics);
	return err;
}



//################################################################################################################################
//################################################################################################################################
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//				Python Ende
//________________________________________________________________________________________________________________________________
//################################################################################################################################
//################################################################################################################################
//################################################################################################################################






#undef NO_INTERPROGRAM_COMMUNICATION_C_FUNCTIONS
