#ifndef DENNTRISC_EXTERN_FUNCTIONS_H
#define DENNTRISC_EXTERN_FUNCTIONS_H



#include <linux/types.h>
#include <sys/types.h>
#include <stdint.h>





extern double getRealTime();







#ifndef NO_DENNTRISC_C_FUNCTIONS
#endif






#ifndef NO_MAIN_FUNCTION_C_FUNCTIONS
extern int dauerbetrieb(int argc, char **argv);
#endif






#ifndef NO_REMAINDER_C_FUNCTIONS
extern int senddetermined (int socket, char *msg, int msglen);
extern void printMAC_fromStr (unsigned char *MAC, int length);
extern void printMAC (unsigned char *MAC, int len);
extern void print_uint64_t_hex(uint64_t val);
extern int getDigitCountofInt(int n);
extern char check_system_endianess(char *system_endianess);
extern uint64_t byte_swap(uint64_t value);
extern uint64_t Send_Endian_Convert(uint64_t value);
#endif






#ifndef NO_DEBUG_C_FUNCTIONS
extern int handleDebug(int argc, char **argstart);
#endif






#ifndef NO_INTERPROGRAM_COMMUNICATION_C_FUNCTIONS
#include "communication_types.h"
extern int recvPyMsgContent(int socket, struct MsgPython **msg, msgsizePy msgsiz);
extern int recvPyMsg(int socket, struct MsgPython **msg);
extern int sendPyMsg(int sock, struct MsgPython *msg, int msgsiz);
extern int createPyMsg(int *msgsize, struct MsgPython **msg, msgtypePy msgtyp, ...);
#endif








#endif /* DENNTRISC_EXTERN_FUNCTIONS_H */
