

#define NO_REMAINDER_C_FUNCTIONS

#include <sys/socket.h>
#include </usr/include/linux/wireless.h>
#include </usr/include/linux/if_arp.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <errno.h>
#include <limits.h>

#include "DennTrisC_globalsettings.h"
#include "DennTrisC_base.h"

#include "debug.h"
#include "remainder.h"

/*
 * Just a bunch of helpful functions/makros
 * Especially some used for debugging/developing
 * Or something nice like the ansi_escape_use setting
 */



int senddetermined (int socket, char *msg, int msglen){
	int bytes_sent;
//	msglen = strlen(msg);
	SendAgain:
	bytes_sent = send(socket, msg, msglen, 0);
	switch(bytes_sent) {
	case -1:
		//Something gone wrong. Read out errno for further detail
		return errno;
		break;
	default:
		if(bytes_sent==msglen) {
			//Everything sent, everything done. Just fine and we are finished.
		} else if(bytes_sent<msglen) {
			//Not everything sent, but the beginning. Go on and send the rest.
			msg=msg+bytes_sent;
			msglen=msglen-bytes_sent;
			goto SendAgain;
		} else {
			//How could this happen o.O ?
			//SHUTDOWN!!!
			//SHUTDOWN!!!
			//Just kidding. Should never occur...
			return OPERATION_ERR_NEVER_HAPPEN;
		}
		break;
	}
	return 0;
}


void printMAC_fromStr (unsigned char *MAC, int length){
	int i;
	length--;
	// Find the real length of the String
	for(; MAC[length] == '\0'; length--) {
		if (length < 0)
			goto NothingToPrint;
	}
	// length now holds the max index
	// And now we are able to properly print it.
	for(i=0; i<length; i++) {
		printf("%02X:", MAC[i]);
	}

	printf("%02X", MAC[length]);

	NothingToPrint:
//	printf("\nDebug-Stringlength: %d\n", length);
	;
}
void printMAC (unsigned char *MAC, int len){
	int i;

	if(!len){
		len=sizeof(MAC);
	}

	if(len<6){
		printf("\nWARNING: You gave me an Array shorter than 6 Byte.Has: %d.\nI'll print the few you gave me, to help you debug ;o)\n",len);
	} else if(len>6){
		printf("\nWARNING: You gave me an Array bigger than 6 Byte.Has: %d.\nI use the first six Byte.\n",len);
		len=6;
	}
	len--;
	for(i=0; i<len; i++) {
		printf("%02X:", MAC[i]);
	}

	printf("%02X", MAC[len]);

//	NothingToPrint:
//	printf("\nDebug-Stringlength: %d\n", length);
	;
}

void print_uint64_t_hex(uint64_t val){
	int i;
	printf("%02X",(unsigned int)(*((unsigned char *)&val)));
	for(i=1;i<8;i++){
		printf(" %02X",(unsigned int)(*(((unsigned char *)&val)+i)));
	}
}







int getDigitCountofInt(int n){
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}



char check_system_endianess(char *endianess){
#define ENDIAN_CHECK_VALUE ((char)(0x11))
	int n = ENDIAN_CHECK_VALUE;
	// TRUE: little endian
	if(*((char *)(&n)) == ENDIAN_CHECK_VALUE){
		*endianess = ENDIANESS_LITTLE;
		printfc(gray,"Info: ");printf("System is Little Endian.\n");
		return ENDIANESS_LITTLE;
	} else if(*(((char *)(&n))+sizeof(int)-1) == ENDIAN_CHECK_VALUE){
		printfc(gray,"Info: ");printf("System is Big Endian.\n");
		*endianess = ENDIANESS_BIG;
		return ENDIANESS_BIG;
	} else{
		printfc(yellow,"WARNING: ");printf("Couldn't get the System Endianess. Thus using Little Endian.\n");
		printf("This may cause some Operations like Network-Communication to not work properly...\n");
		*endianess = ENDIANESS_LITTLE;
		return ENDIANESS_LITTLE;
	}
#undef ENDIAN_CHECK_VALUE
}



uint64_t byte_swap(uint64_t value){
#define SHIFT_FROM_MID_1 8
#define SHIFT_FROM_MID_2 24
#define SHIFT_FROM_MID_3 40
#define SHIFT_FROM_MID_4 56
#define BITMASK_BYTE_0 0xff00000000000000
#define BITMASK_BYTE_1 0xff000000000000
#define BITMASK_BYTE_2 0xff0000000000
#define BITMASK_BYTE_3 0xff00000000
#define BITMASK_BYTE_4 0xff000000
#define BITMASK_BYTE_5 0xff0000
#define BITMASK_BYTE_6 0xff00
#define BITMASK_BYTE_7 0xff

	uint64_t swapped;

	swapped =	((value>>SHIFT_FROM_MID_4)&BITMASK_BYTE_7) |
				((value>>SHIFT_FROM_MID_3)&BITMASK_BYTE_6) |
				((value>>SHIFT_FROM_MID_2)&BITMASK_BYTE_5) |
				((value>>SHIFT_FROM_MID_1)&BITMASK_BYTE_4) |
				((value<<SHIFT_FROM_MID_1)&BITMASK_BYTE_3) |
				((value<<SHIFT_FROM_MID_2)&BITMASK_BYTE_2) |
				((value<<SHIFT_FROM_MID_3)&BITMASK_BYTE_1) |
				((value<<SHIFT_FROM_MID_4)&BITMASK_BYTE_0);

	return swapped;

#undef SHIFT_FROM_MID_1
#undef SHIFT_FROM_MID_2
#undef SHIFT_FROM_MID_3
#undef SHIFT_FROM_MID_4
#undef BITMASK_BYTE_0
#undef BITMASK_BYTE_1
#undef BITMASK_BYTE_2
#undef BITMASK_BYTE_3
#undef BITMASK_BYTE_4
#undef BITMASK_BYTE_5
#undef BITMASK_BYTE_6
#undef BITMASK_BYTE_7
}





/* Use the following for Endianess in Network-Sendings.
 * E.g. as Byte-Ordering for the (Header-)msgsize. */
uint64_t Send_Endian_Convert(uint64_t value){
	int temp_end;
	temp_end=system_endianess;
	AGAIN:
	switch(temp_end){
	case ENDIANESS_BIG:
	case ENDIANESS_LITTLE:
		if(temp_end==ENDIANESS_SEND){
			//Nothing to convert. The Endianesses match. System uses same Byte-Order as we want for Network-Ops
			return value;
		}else{
//			depr(10)
//			print_uint64_t_hex(value);printf("\n");
//			print_uint64_t_hex(byte_swap(value));printf("\n");
			return byte_swap(value);
		}
		break;
	case ENDIANESS_UNKNOWN:
	default:
		temp_end=check_system_endianess(&system_endianess);
		goto AGAIN;
		break;
	}
}








#undef NO_REMAINDER_C_FUNCTIONS
