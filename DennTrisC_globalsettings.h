#ifndef DENNTRISC_GLOBALSETTINGS_H
#define DENNTRISC_GLOBALSETTINGS_H






/*NOTE:
 * 1. If this is defined: The Files (and folders) like cfg's are stored locally
 * 		(it looks inside some special specified locations, like $XDG_CONFIG_HOME or just $HOME for their presence on the system.
 * 		 then stores for example inside the Home Folder of your Linux Machine -> DennTrisC/...)
 * 2. If it is outcommented: These Files are stored inside the DennTrisC Project Folder or whatever/wherever DennTrisC is stored
 */
#define FILES_LOCAL_OR_IN_PROJECT (1)
/*NOTE ctd.:
 * The following determines a second Stage of Path Specification
 * 1. If you have chosen to save the Files localy (i.e. on some Plattform Folders instead of inside the Program Folder)
 * 		, then
 * 2. If this is defined: The Files are stored inside /etc/DennTrisC/...
 * 		If it is outcommented: The Files are stored in user specific Folders
 * 		(which in most cases should be /root, because ollersu needs Super User for most functionality)
 */
#define FILES_GLOBAL_OR_USER_SPECIFIC (1)


//#define RELEASE_VERSION


#ifndef RELEASE_VERSION
	#define DEVELOPMENT_MODE


	#define DEBUG

//	#define DEBUG_WIFI_SNIFF
#endif







#endif /* DENNTRISC_GLOBALSETTINGS_H */
