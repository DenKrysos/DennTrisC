#ifndef CONFIG_H
#define CONFIG_H


#include "DennTrisC_globalsettings.h"







#define ABSINT_CFG_FILE_NAME "absint"
#define ABSINT_CFG_FILE_PATH_PREFIX ""
#define ABSINT_CFG_FILE_PATH_SUFFIX ".cfg"
#define ABSINT_ADHOC_CFG_FILE_NAME "absint-wpa_supplicant-adhoc_"
#define ABSINT_ADHOC_CFG_FILE_PATH_PREFIX "wlan/"
#define ABSINT_ADHOC_CFG_FILE_PATH_SUFFIX ".conf"
#define ABSINT_AI_CTRL_STD_PORT 24292
#define ABSINT_SDN_CTRL_STD_PORT 8080
#define ABSINT_AI_PARTNER_STD_PORT 24291
#define RECVBUFFSIZECONTROLLER 1024
#define RECVBUFFSIZEOTHERAI 1024
#define INTER_AI_MSG_MAX_SIZE 1024

#define ABSINT_SWITCH_MODE_TIMEOUT_S 10
#define ABSINT_SWITCH_MODE_TIMEOUT_NS 0






/* You could use the AI Partner Address - in case of Working as Server from the Inter AI Communication Point of View -
 * to restrict incoming Connection Requests
 * See the Wildcard Comment on the Server Setup Macro
 */
/* IMPORTANT: First expand the Macro "CREATE_PROGRAM_PATH(*args)", before using this Macro
 * Because this here needs the Program Path
 * So a Call looks like this:
 *		CREATE_PROGRAM_PATH(*args);
 *		ABSINT_READ_CONFIG_FILE;
 */
/*
 * umask(0); is nearly the opposite of umask(ACCESSPERMS);
 * Used here like this, because umask specifies which permission flags get cleared at file/folder creation
 * umask(mask) specifies the mask which used at creation with something like mkdir("dir",creatmask)
 * 		in form of (creatmask & ~mask)
 */
#define ABSINT_READ_CONFIG_FILE printf("\tReading in the config-file...\n"); \
		umask(0); \
    	int aipc=1; \
    	int aiport; \
    	struct in_addr dnsserverip4; \
    	/*uintptr_t sdnctrldns;*/ \
    	char *sdnctrldns; \
    	sdnctrldns=NULL; \
    	int aictrlport; \
    	int sdnctrlport; \
    	struct in_addr controlleraddress; \
    	struct timespec WLANChanTrafficMonTime; \
        /* Maybe Open a Scope for Variables, which won't be needed forever */ \
		/* Remember to close the Scope somewhere after the Macro-Usage */ \
		/* If there aren't any Variables like this just close it immediately after the Macro Usage */ \
		/* or delete the Line with the opening Bracket ( { \ ) */ \
    	struct aiconnectmode aiconnectmodecfg={ \
			.clientOrServer=INTER_AI_CLSERV_AUTO, \
			.AIPartnerAddrSrc=INTER_AI_ADDR_SRC_AUTO \
		}; \
    	struct in_addr aipaddresscfg; \
        /* Open a Scope for the Config-related Variables (Read-Buffer, File Pointer...) */ \
        /* Therewith they get deallocated after the File-Readout */ \
    	{ \
		char cfg_file[strlen(ProgPath)+strlen(ABSINT_CFG_FILE_PATH_PREFIX)+strlen(ABSINT_CFG_FILE_NAME)+strlen(ABSINT_CFG_FILE_PATH_SUFFIX)+1]; \
		memcpy(cfg_file,ProgPath,strlen(ProgPath)); \
		memcpy(cfg_file+strlen(ProgPath),ABSINT_CFG_FILE_PATH_PREFIX,strlen(ABSINT_CFG_FILE_PATH_PREFIX)); \
		memcpy(cfg_file+strlen(ProgPath)+strlen(ABSINT_CFG_FILE_PATH_PREFIX),ABSINT_CFG_FILE_NAME,strlen(ABSINT_CFG_FILE_NAME)); \
		memcpy(cfg_file+strlen(ProgPath)+strlen(ABSINT_CFG_FILE_PATH_PREFIX)+strlen(ABSINT_CFG_FILE_NAME),ABSINT_CFG_FILE_PATH_SUFFIX,strlen(ABSINT_CFG_FILE_PATH_SUFFIX)); \
		cfg_file[sizeof(cfg_file)-1]='\0'; \
	    FILE *cfgf; \
	    cfgf = fopen(cfg_file, "r"); \
	    if (!cfgf) { \
			char cfg_file_dir[strlen(ProgPath)+strlen(ABSINT_CFG_FILE_PATH_PREFIX)+1]; \
	    	switch(errno) { \
	    		case EACCES: \
	    			printf("\tERROR: Couldn't open cfg-File!\n\t\tReason:Permission denied!\n"); \
	    		break; \
	    		case ENOENT: \
	    			printf("\tERROR: Cfg-File doesn't exist!\n"); \
	    			printf("\tCreating new one:\n\t\twhile setting every Entry to auto...\n"); \
					/*NOT Exclude the preceding '/' from the folder-path*/ \
					memcpy(cfg_file_dir,ProgPath,strlen(ProgPath)); \
					memcpy(cfg_file_dir+strlen(ProgPath),ABSINT_CFG_FILE_PATH_PREFIX,strlen(ABSINT_CFG_FILE_PATH_PREFIX)); \
					cfg_file_dir[sizeof(cfg_file_dir)-1]='\0'; \
					/*Check the complete Path and eventually create the folders*/ \
					CREATE_COMPLETE_FOLDER_PATH(cfg_file_dir); \
	    		    cfgf = fopen(cfg_file, "w+"); \
	    		    if(!cfgf){ \
	    		    	printf("\t\tERROR: Couldn't create new cfg-file!\n"); \
	    		    	return FILE_ERR_PERMISSION_DENIED; \
	    		    } \
    		    	printf("\t\tSetting up config-file with:\n"); \
					printf("\t\t\t#AIConnectMode=auto\n"); \
					fprintf(cfgf, "\n#AIConnectMode=auto"); \
	    			fprintf(cfgf, "\n*INFO: The AIs have to communicate with each other. This Value describes how they set up the connection"); \
	    			fprintf(cfgf, "\n*INFO: Allowed Values:"); \
	    			fprintf(cfgf, "\n*INFO: server: This AI starts a server, to which other AIs can connect."); \
	    			fprintf(cfgf, "\n*INFO: client: This AI assumes that one AI on the other Side of the physical Connection runs as a Server and trys to connect to it."); \
	    			fprintf(cfgf, "\n*INFO: auto: Automatic Detection and maybe setting up of a server or connecting to an existing one."); \
	    			printf("\t\t\t#DNSServerIP4=172.10.0.100\n"); \
	    			fprintf(cfgf, "\n#DNSServerIP4=172.10.0.100"); \
	    			printf("\t\t\t#SDNControllerIPorDNS=dns\n"); \
	    			fprintf(cfgf, "\n#SDNControllerIPorDNS=dns"); \
	    			fprintf(cfgf, "\n*INFO: dns: AI takes the String at SDNControllerAddrDNS and does a DNS Lookup"); \
	    			fprintf(cfgf, "\n*INFO: ip4: AI uses directly the IPv4 Address from SDNControllerAddrIP4"); \
	    			printf("\t\t\t#SDNControllerAddrDNS=sdncontroller.cocos.de\n"); \
					fprintf(cfgf, "\n#SDNControllerAddrDNS=sdncontroller.cocos.de"); \
					printf("\t\t\t#SDNControllerAddrIP4=192.168.1.1\n"); \
					fprintf(cfgf, "\n#SDNControllerAddrIP4=192.168.1.1"); \
					inet_pton(AF_INET,"192.168.1.1",&controlleraddress); \
					printf("\t\t\t#SDNControllerPort=%d\n",ABSINT_SDN_CTRL_STD_PORT); \
					fprintf(cfgf, "\n#SDNControllerPort=%d",ABSINT_SDN_CTRL_STD_PORT); \
					sdnctrlport=ABSINT_SDN_CTRL_STD_PORT; \
					printf("\t\t\t#AIControllerPort=%d\n",ABSINT_AI_CTRL_STD_PORT); \
					fprintf(cfgf, "\n#AIControllerPort=%d",ABSINT_AI_CTRL_STD_PORT); \
					aictrlport=ABSINT_AI_CTRL_STD_PORT; \
	    			fprintf(cfgf, "\n*INFO: Setup should be as following:"); \
	    			fprintf(cfgf, "\n*INFO: AI-Ctrl is autonomous Program, that runs on the same Machine as the SDN-Ctrl"); \
	    			fprintf(cfgf, "\n*INFO: The AI-Ctrl communicates on this Machine with the SDN-Ctrl"); \
	    			fprintf(cfgf, "\n*INFO: Every AI communicates over the Network with the AI-Ctrl"); \
	    			fprintf(cfgf, "\n*INFO: So the AI-Ctrl Port is used between every AI and the AI-Ctrl"); \
	    			fprintf(cfgf, "\n*INFO: And the SDN-Ctrl Port is used only from the AI-Ctrl; between the AI-Ctrl and the SDN-Ctrl"); \
					printf("\t\t\t#WLANChanTrafficMonS=0\n"); \
					fprintf(cfgf, "\n#WLANChanTrafficMonS=0"); \
					printf("\t\t\t#WLANChanTrafficMonNS=500000000\n"); \
					fprintf(cfgf, "\n#WLANChanTrafficMonNS=500000000"); \
					WLANChanTrafficMonTime.tv_sec=0; \
					WLANChanTrafficMonTime.tv_nsec=500000000; \
					printf("\t\t\t#AIPartnerCount=1\n"); \
					fprintf(cfgf, "\n#AIPartnerCount=1"); \
					printf("\t\t\t#AIPartnerAddrSrc=auto\n"); \
					fprintf(cfgf, "\n#AIPartnerAddrSrc=auto"); \
					printf("\t\t\t#AIPartnerAddrIP4=10.0.1.20\n"); \
					fprintf(cfgf, "\n#AIPartnerAddrIP4=10.0.1.20"); \
					inet_pton(AF_INET,"10.0.1.20",&aipaddresscfg); \
					printf("\t\t\t#AIPartnerPort=%d\n",ABSINT_AI_PARTNER_STD_PORT); \
					fprintf(cfgf, "\n#AIPartnerPort=%d",ABSINT_AI_PARTNER_STD_PORT); \
					aiport=ABSINT_SDN_CTRL_STD_PORT; \
					fprintf(cfgf, "\n"); \
	    	    	fclose(cfgf); \
	    			printf("\t\t...created cfg-file successfully!\n"); \
	    			printfc(red,"\tProgram is now exiting!\n"); \
	    			printfc(red,"\t\t-->"); \
	    			printfc(yellow," -->\n"); \
	    			printfc(yellow,"\tPlease configure the cfg-file and start again!\n"); \
	    			printf("Exit.\n"); \
	    			exit(0); \
	    		break; \
				default: \
					fprintf(stderr, "Ups, seems like we've encountered a case, which isn't caught yet :o("); \
					return MAIN_ERR_FUNC_INCOMPLETE; \
				break; \
	    	} \
	    } else { \
	    	char buf[128]; \
	    	memset(buf,0,sizeof(buf)); \
	    	while(1) { \
	    		int loopcnt; \
	    		int readval; \
				if ((readval = getc(cfgf)) == EOF) { \
				 printf("\t...Read completely through config-file.\n"); \
				 break; \
				} \
				buf[0]=(char)readval; \
				if (buf[0] == '#') { \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '=') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
				} \
				if(strcmp(buf,"AIConnectMode")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(strcmp(buf,"client")==0){ \
						aiconnectmodecfg.clientOrServer=INTER_AI_CLSERV_CLIENT; \
					} else \
					if(strcmp(buf,"server")==0){ \
						aiconnectmodecfg.clientOrServer=INTER_AI_CLSERV_SERVER; \
					} else \
					if(strcmp(buf,"auto")==0){ \
						aiconnectmodecfg.clientOrServer=INTER_AI_CLSERV_AUTO; \
					} else { \
						printf("\tERROR: cfg-file damaged! Invalid Entry at AIConnectMode!\n"); \
					} \
				} else if(strcmp(buf,"SDNControllerAddrIP4")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					inet_pton(AF_INET,buf,&controlleraddress); \
				} else if(strcmp(buf,"AIPartnerCount")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					char *endpoint; \
					aipc = strtol(buf, &endpoint, 10); \
					if (*endpoint) { \
						printf("ERROR: Unsupported Format in cfg-File at:\n\tAIPartnerCount\n"); \
						return MAIN_ERR_BAD_CMDLINE; \
					} \
				} else if(strcmp(buf,"SDNControllerPort")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(strcmp(buf,"auto")==0){ \
					}else{ \
						char *endpoint; \
						sdnctrlport = strtol(buf, &endpoint, 10); \
						if (*endpoint) { \
							printf("ERROR: Unsupported Format in cfg-File at:\n\tSDNControllerPort\n"); \
							return MAIN_ERR_BAD_CMDLINE; \
						} \
					} \
				} else if(strcmp(buf,"AIControllerPort")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(strcmp(buf,"auto")==0){ \
					}else{ \
						char *endpoint; \
						aictrlport = strtol(buf, &endpoint, 10); \
						if (*endpoint) { \
							printf("ERROR: Unsupported Format in cfg-File at:\n\tAIControllerPort\n"); \
							return MAIN_ERR_BAD_CMDLINE; \
						} \
					} \
				} else if(strcmp(buf,"WLANChanTrafficMonS")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					char *endpoint; \
					WLANChanTrafficMonTime.tv_sec = strtol(buf, &endpoint, 10); \
					if (*endpoint) { \
						printf("ERROR: Unsupported Format in cfg-File at:\n\tWLANChanTrafficMonS\n"); \
						return MAIN_ERR_BAD_CMDLINE; \
					} \
				} else if(strcmp(buf,"WLANChanTrafficMonNS")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					char *endpoint; \
					WLANChanTrafficMonTime.tv_nsec = strtol(buf, &endpoint, 10); \
					if (*endpoint) { \
						printf("ERROR: Unsupported Format in cfg-File at:\n\tWLANChanTrafficMonNS\n"); \
						return MAIN_ERR_BAD_CMDLINE; \
					} \
				} else if(strcmp(buf,"AIPartnerPort")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(strcmp(buf,"auto")==0){ \
					}else{ \
						char *endpoint; \
						aiport = strtol(buf, &endpoint, 10); \
						if (*endpoint) { \
							printf("ERROR: Unsupported Format in cfg-File at:\n\tAIPartnerCount\n"); \
							return MAIN_ERR_BAD_CMDLINE; \
						} \
					} \
				} else if(strcmp(buf,"AIPartnerAddrSrc")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(strcmp(buf,"auto")==0){ \
						aiconnectmodecfg.AIPartnerAddrSrc=INTER_AI_ADDR_SRC_AUTO; \
					}else if(strcmp(buf,"cfg")==0){ \
						aiconnectmodecfg.AIPartnerAddrSrc=INTER_AI_ADDR_SRC_CFG; \
					}else if(strcmp(buf,"cmdline")==0){ \
						aiconnectmodecfg.AIPartnerAddrSrc=INTER_AI_ADDR_SRC_CMDLINE; \
					}else{ \
						printf("ERROR: Unsupported Format in cfg-File at:\n\tAIPartnerAddrSrc\n"); \
						return MAIN_ERR_BAD_CMDLINE; \
					} \
				} else if(strcmp(buf,"AIPartnerAddrIP4")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					inet_pton(AF_INET,buf,&aipaddresscfg); \
				} else if(strcmp(buf,"DNSServerIP4")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					inet_pton(AF_INET,buf,&dnsserverip4); \
				} else if(strcmp(buf,"SDNControllerIPorDNS")==0){ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(strcmp(buf,"dns")==0){ \
						/*sdnctrldns=malloc(256);*/ \
						sdnctrldns=(void *)1; \
					} \
					/*Maybe add more here in the future to differ IP4 and IP6*/ \
				} else if(strcmp(buf,"SDNControllerAddrDNS")==0){ \
					/*For this Method it is mighty, mighty important, that #SDNControllerIPorDNS comes before #SDNControllerAddrDNS in the cfg-File*/ \
					/* Or it screws up */ \
					for(loopcnt=0;loopcnt<sizeof(buf);loopcnt++){ \
						if (((buf[loopcnt] = getc(cfgf)) == '\n') || (buf[loopcnt] == EOF)) { \
							buf[loopcnt]='\0'; \
							break; \
						} \
					} \
					if(sdnctrldns!=NULL){ \
						sdnctrldns=malloc(loopcnt+1); \
						memcpy(sdnctrldns,buf,loopcnt+1); \
					} \
				} \
	    	} \
	    	printf("\t...Read in Connection Mode to other AIs: %s\n", (aiconnectmodecfg.clientOrServer==INTER_AI_CLSERV_CLIENT)?"client":((aiconnectmodecfg.clientOrServer==INTER_AI_CLSERV_SERVER)?"server":((aiconnectmodecfg.clientOrServer==INTER_AI_CLSERV_AUTO)?"auto":"Ehm, something gone wrong... so use: AUTO"))); \
	    	printf("\t\tRemember: Commandline has higher Priority (if given)\n"); \
			char ControllerIP4[16]; \
			inet_ntop(AF_INET,&controlleraddress,ControllerIP4,sizeof(ControllerIP4)); \
			printf("\t...Read Address (IP4) of SDN Controller: %s\n",ControllerIP4); \
	    	printf("\t...Read Number of connected other AIs: %d\n",aipc); \
	        if (fclose(cfgf)) { \
	        	printf("NOTICE: Config-File couldn't be closed successfully!"); \
	        } else { \
	        	printf("...config-file read successfully!\n"); \
	        } \
	    } \
		/* Close the Scope for the Config-related Variables */ \
		}






#endif /* CONFIG_H */
