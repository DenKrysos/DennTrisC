/*
 *main.cpp
 */
/* Within
 *  Project | Properties | C/C++-Build | Settings
 *  | GCC C++ Compiler | Preprocessor
 * set the following defined Symbol:
 *  _FILENAME=${ConfigName}
 */
#define __QUOT2__(x) #x
#define __QUOT1__(x) __QUOT2__(x)
#include __QUOT1__(_FILENAME.c)
#undef __QUOT1__
#undef __QUOT2__
/* The above include directive will include the file ${CfgName}.cpp,
 * wherein ${CfgName} is the name of the build configuration currently
 * active in the project.
 *
 * When right clicking in
 *  Project Tree | (Project)
 * and selecting
 *  Build Configuration | Build all
 * this file will include the corresponding .cpp file  named after the
 * build config and thereby effectively take that file as a main file.
 *
 * Remember to exclude ALL ${CfgName}.cpp files from ALL build configurations.
 */

/* Erklärung auf Deutsch für die Projekt-Organisation:
 * Die Hintergrund-Idee ist im Grunde:
 * 		Man hat zwei Programm-Projekte. Diese sollen eigenständige Programme ergeben,
 * 		die jedoch eng verwandt sind. Es existieren also geteilte Code-Fragmente.
 * 		Mit vorliegendem Verfahren lassen sich diese Projekte in einem Projekt vereinen.
 * 		Und damit müssen die geteilten Code-Fragmente nur einmal vorliegen, anstatt Kopien
 * 		in zwei Projekten.
 * Beide main()-Routinen werden in dasselbe Projekt gelegt. In jeweils eigenen Dateien, die nicht "main.c" heißen.
 * Jede Datei enthält jedoch eine eigene main(). In dasselbe Projekt kommt diese Datei hier.
 * Beispiel:
 * Projekt-Folder
 * 		- programmX.c
 * 			--- main()
 * 		- programmX_CLI.c
 * 			--- main()
 * 		- main.c
 * 			--- ...
 * In den Projekt Einstellungen (Properties) folgende Einstellung vornehmen:
 * 	1. C/C++ Build
 * 		- Settings
 * 			- Manage Configurations ...
 *	  Für jedes "Sub"-Programm eine eigene Build-Configuration anlegen. Diese erhalten
 *	  als Namen jeweils exakt den Namen des C-Files, das für dieses Programm kompiliert werden soll.
 * 	2. C/C++ Build
 * 		- Settings
 * 			- GCC C Compiler
 * 				- Symbols
 * 					Dort folgendes Eintragen "_FILENAME=${ConfigName}"
 *
 * Anschließend durch die Ressource-Configuration alle {Programm-Name}.C-File aus sämtlichen
 * Build-Configurations entfernen:
 * 	- Im Projekt-Explorer die Dateien markieren
 * 	- Rechtsklick
 * 	- Ressource Configurations
 * 		- Exclude form Build
 * 			Sämtliche Build-Configurations anwählen
 *
 * Zusätzlich können weitere Dateien, die nur für bestimmte Builds kompiliert werden sollen aus
 * einzelnen Build-Configurations entfernt werden.
 *
 *
 * Zum kompilieren der einzelnen Programme wird schließlich die entsprechende Build-Configuration
 * zum Build gewählt. Für die einzelnen Programme werden durch den Build damit eigene Ordner im
 * Projekt-Ordner mit dem Build-Namen angelegt, worin die kompilierten Programme zu finden sind.
 */
