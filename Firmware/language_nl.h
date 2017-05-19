/**
 * Dutch
 *
 * LCD Menu Messages
 * Please note these are limited to 17 characters!
 *
 */

#define(length=20) WELCOME_MSG              CUSTOM_MENDEL_NAME " gereed."
#define MSG_SD_INSERTED                     "SD ingestoken"
#define MSG_SD_REMOVED                      "SD verwijderd"
#define MSG_MAIN                            "Hoofdmenu"
#define(length=20) MSG_DISABLE_STEPPERS                "Motoren uit"
#define MSG_AUTO_HOME                       "Startpositie"
#define MSG_SET_HOME_OFFSETS                "Set home offsets"
#define MSG_SET_ORIGIN                      "Oorsprong instellen"
#define MSG_COOLDOWN                        "Afkoelen"
#define MSG_SWITCH_PS_ON                    "Opstarten"
#define MSG_SWITCH_PS_OFF                   "Uitschakelen"
#define MSG_MOVE_AXIS                       "As verplaatsen"
#define MSG_MOVE_X                          "Verplaats X"
#define MSG_MOVE_Y                          "Verplaats Y"
#define MSG_MOVE_Z                          "Verplaats Z"
#define MSG_MOVE_E                          "Extruder"
#define MSG_SPEED                           "Snelheid"
#define MSG_NOZZLE                          "Tuit"
#define MSG_NOZZLE1                         "Tuit2"
#define MSG_NOZZLE2                         "Tuit3"
#define MSG_BED                             "Bed"
#define(length=20) MSG_FAN_SPEED                       "Fan snelheid"
#define MSG_FLOW                            "Flow"
#define MSG_FLOW0                           "Flow 0"
#define MSG_FLOW1                           "Flow 1"
#define MSG_FLOW2                           "Flow 2"
#define MSG_CONTROL                         "Control"
#define MSG_MIN                             " \002 Min"
#define MSG_MAX                             " \002 Max"
#define MSG_FACTOR                          " \002 Fact"
#define MSG_TEMPERATURE                     "Temperatuur"
#define MSG_MOTION                          "Beweging"
#define MSG_VOLUMETRIC                      "Filament"
#define MSG_VOLUMETRIC_ENABLED		        "E in mm3"
#define MSG_STORE_EPROM                     "Geheugen opslaan"
#define MSG_LOAD_EPROM                      "Geheugen laden"
#define MSG_RESTORE_FAILSAFE                "Backup terugzetten"
#define MSG_REFRESH                         "\xF8" "Herladen"
#define MSG_WATCH                           "Info scherm"
#define MSG_TUNE                            "Fijninstellingen"
#define MSG_PAUSE_PRINT                     "Print pauzeren"
#define MSG_RESUME_PRINT                    "Print hervatten"
#define MSG_STOP_PRINT                      "Print stoppen"
#define MSG_CARD_MENU                       "Print van SD"
#define MSG_NO_CARD                         "Geen SD kaart"
#define MSG_DWELL                           "Slapen..."
#define(length=20) MSG_USERWAIT             			"Wachten op gebruiker"
#define(length=20, lines=2) MSG_RESUMING                        "Print hervatten"
#define(length=20) MSG_PRINT_ABORTED        "Print afgebroken"
#define MSG_NO_MOVE                         "Geen beweging."
#define(length=20) MSG_KILLED                          "NOODSTOP/KILLED. "
#define MSG_STOPPED                         "GESTOPT. "
#define MSG_FILAMENTCHANGE                  "Wissel filament"
#define MSG_INIT_SDCARD                     "Init. SD kaart"
#define MSG_CNG_SDCARD                      "Wissel SD kaart"
#define MSG_BABYSTEP_X                      "Babystep X"
#define MSG_BABYSTEP_Y                      "Babystep Y"
#define MSG_BABYSTEP_Z                      "Live Z aanpassen"
#define(length=20) MSG_ADJUSTZ							"Auto instellen Z?"
#define(length=20) MSG_PICK_Z							"Pick print"

#define MSG_SETTINGS                        "Instellingen"
#define MSG_PREHEAT                         "Voorverwarmen"
#define MSG_UNLOAD_FILAMENT                 "Filament uithalen"
#define MSG_LOAD_FILAMENT                 	"Filament laden"
#define(length=20)  MSG_LOAD_FILAMENT_1					"Filament 1 laden"
#define(length=20)  MSG_LOAD_FILAMENT_2					"Filament 2 laden"
#define(length=20)  MSG_LOAD_FILAMENT_3					"Filament 3 laden"
#define(length=20)  MSG_LOAD_FILAMENT_4					"Filament 4 laden"
#define(length=20)  MSG_UNLOAD_FILAMENT_1				"Filament 1 uithalen"
#define(length=20)  MSG_UNLOAD_FILAMENT_2				"Filament 2 uithalen"
#define(length=20)  MSG_UNLOAD_FILAMENT_3				"Filament 3 uithalen"
#define(length=20)  MSG_UNLOAD_FILAMENT_4				"Filament 4 uithalen"
#define(length=20) MSG_UNLOAD_ALL						"Alle uithalen"
#define(length=20) MSG_LOAD_ALL						"Alle laden"

#define MSG_RECTRACT                        "Rectract"
#define MSG_ERROR                        	"FOUT:"
#define(length=20) MSG_PREHEAT_NOZZLE       "Tuit voorverwarmen!"
#define MSG_SUPPORT 						"Support"
#define(length=20) MSG_CORRECTLY			"Wissel ok?"
#define MSG_YES								"Ja"
#define MSG_NO								"Nee"
#define(length=20) MSG_NOT_LOADED 			"Fil. niet geladen"
#define(length=20) MSG_NOT_COLOR 	"Kleur niet duidelijk"
#define(length=20) MSG_LOADING_FILAMENT		"Laade Filament"
#define(length=20) MSG_PLEASE_WAIT			"Wacht aub"
#define MSG_LOADING_COLOR					"Laade kleur"
#define(length=20) MSG_CHANGE_SUCCESS					"Wissel succesvol!"
#define(length=20) MSG_PRESS				"en druk op knop"
#define(length=20) MSG_INSERT_FILAMENT		"Filament insteken"
#define(length=20) MSG_CHANGING_FILAMENT	"Wissel filament!"


#define MSG_SILENT_MODE_ON					"Mode     [silent]"
#define MSG_SILENT_MODE_OFF					"Mode [high power]" 
#define(length=20) MSG_REBOOT				"Herstart  de printer"
#define(length=20, lines=2) MSG_TAKE_EFFECT			" om effectief te worden"											

#define MSG_Enqueing                        "enqueing \""
#define MSG_POWERUP                         "PowerUp"
#define MSG_CONFIGURATION_VER               " Laaste geupdatet: "
#define MSG_FREE_MEMORY                     " Vrij geheugen: "
#define MSG_PLANNER_BUFFER_BYTES            "  PlannerBufferBytes: "
#define MSG_OK                              "ok"
#define MSG_ERR_CHECKSUM_MISMATCH           "checksum fout, Laatste lijn: "
#define MSG_ERR_NO_CHECKSUM                 "Geen Checksum met lijnnummer Laatste Lijn: "
#define MSG_BEGIN_FILE_LIST                 "Begin file lijst"
#define MSG_END_FILE_LIST                   "Eind file lijst"
#define MSG_M104_INVALID_EXTRUDER           "M104 Invalid extruder "
#define MSG_M105_INVALID_EXTRUDER           "M105 Invalid extruder "
#define MSG_M200_INVALID_EXTRUDER           "M200 Invalid extruder "
#define MSG_M218_INVALID_EXTRUDER           "M218 Invalid extruder "
#define MSG_M221_INVALID_EXTRUDER           "M221 Invalid extruder "
#define MSG_ERR_NO_THERMISTORS              "Geen Temp.sensoren - geen temperatuur"
#define MSG_M109_INVALID_EXTRUDER           "M109 Invalid extruder "
#define MSG_HEATING                         "Opwarmen"
#define(length=20) MSG_HEATING_COMPLETE     "Opwarmen klaar."
#define MSG_BED_HEATING                     "Bed opwarmen"
#define MSG_BED_DONE                        "Bed OK."
#define MSG_M115_REPORT                     "FIRMWARE_NAME:Marlin V1.0.2; Sprinter/grbl mashup for gen6 FIRMWARE_URL:" FIRMWARE_URL " PROTOCOL_VERSION:" PROTOCOL_VERSION " MACHINE_TYPE:" CUSTOM_MENDEL_NAME " EXTRUDER_COUNT:" STRINGIFY(EXTRUDERS) " UUID:" MACHINE_UUID "\n"
#define MSG_ERR_KILLED                      "Printer gestopt. kill() called!"
#define MSG_ERR_STOPPED                     "Printer vanwege fouten gestopt. Repareer de fout en gebruiken M999 te herstarten. (Temperatuur is gereset. Stel het na het herstarten)"
#define MSG_RESEND                          "Resend: "
#define MSG_M119_REPORT                     "Endstop status weergeven"
#define MSG_ENDSTOP_HIT                     "gesloten"
#define MSG_ENDSTOP_OPEN                    "open"

#define MSG_SD_CANT_OPEN_SUBDIR             "Kan map niet openen"
#define MSG_SD_INIT_FAIL                    "SD opstarten mislukt"
#define MSG_SD_VOL_INIT_FAIL                "volume.init mislukt"
#define MSG_SD_OPENROOT_FAIL                "openRoot mislukt"
#define MSG_SD_CARD_OK                      "SD card ok"
#define MSG_SD_WORKDIR_FAIL                 "workDir openen mislukt"
#define MSG_SD_OPEN_FILE_FAIL               "openen mislukt, Bestand : "
#define MSG_SD_FILE_OPENED                  "Bestand  geopend: "
#define MSG_SD_FILE_SELECTED                "Bestand  geselecteerd"
#define MSG_SD_WRITE_TO_FILE                "Naar bestand schrijven: "
#define MSG_SD_PRINTING_BYTE                "SD printing byte "
#define MSG_SD_NOT_PRINTING                 "geen SD printen"
#define MSG_SD_ERR_WRITE_TO_FILE            "fout bij schrijven naar bestand"
#define MSG_SD_CANT_ENTER_SUBDIR            "Kan niet in map: "

#define MSG_STEPPER_TOO_HIGH                "Steprate too high: "
#define MSG_ENDSTOPS_HIT                    "endstops hit: "
#define MSG_ERR_COLD_EXTRUDE_STOP           " koude extrusie voorkomen"
#define MSG_BABYSTEPPING_X                  "Babystepping X"
#define MSG_BABYSTEPPING_Y                  "Babystepping Y"
#define MSG_BABYSTEPPING_Z                  "Instellen Z"
#define MSG_SERIAL_ERROR_MENU_STRUCTURE     "Error in menu structure"

#define MSG_LANGUAGE_NAME					"Nederlands"
#define MSG_LANGUAGE_SELECT					"Kies taal"
#define MSG_PRUSA3D							"prusa3d.com"
#define MSG_PRUSA3D_FORUM					"forum.prusa3d.com"
#define MSG_PRUSA3D_HOWTO					"howto.prusa3d.com"

#define(length=20) MSG_SELFTEST_ERROR					"Zelftest Fout !"
#define MSG_SELFTEST_PLEASECHECK			"Controleer aub:"	
#define(length=20) MSG_SELFTEST_NOTCONNECTED			"Niet aangesloten"
#define MSG_SELFTEST_HEATERTHERMISTOR		"Heater/Thermistor"
#define MSG_SELFTEST_BEDHEATER				"Bed / Heater"
#define(length=20) MSG_SELFTEST_WIRINGERROR			"Bedrading fout"
#define MSG_SELFTEST_ENDSTOPS				"Endstops"
#define MSG_SELFTEST_MOTOR					"Motor"
#define MSG_SELFTEST_ENDSTOP				"Endstop"
#define(length=20) MSG_SELFTEST_ENDSTOP_NOTHIT			"Endstop niet geraakt"
#define MSG_SELFTEST_OK						"Zelftest OK"
#define(length=20) MSG_LOOSE_PULLEY					"Loose pulley"

#define MSG_SELFTEST_FAN					"Fan test";
#define(length=20) MSG_SELFTEST_COOLING_FAN			"Voordere fan?";
#define(length=20) MSG_SELFTEST_EXTRUDER_FAN			"Linke fan?";
#define MSG_SELFTEST_FAN_YES				"Roteert";
#define(length=20) MSG_SELFTEST_FAN_NO					"Roteert niet";

#define(length=20) MSG_STATS_TOTALFILAMENT	"Filament total: "
#define(length=20) MSG_STATS_TOTALPRINTTIME "Total printtijd:"
#define(length=20) MSG_STATS_FILAMENTUSED	"Filamentverbruik:"
#define(length=20) MSG_STATS_PRINTTIME		"Printtijd:   "
#define(length=20) MSG_SELFTEST_START				"Zelftest  start  "
#define(length=20) MSG_SELFTEST_CHECK_ENDSTOPS		"Controleer endstops"
#define(length=20) MSG_SELFTEST_CHECK_HOTEND		"Controleer hotend  "  
#define(length=20) MSG_SELFTEST_CHECK_X				"Controleer X as    "
#define(length=20) MSG_SELFTEST_CHECK_Y				"Controleer Y as    "
#define(length=20) MSG_SELFTEST_CHECK_Z				"Controleer Z as    "
#define(length=20) MSG_SELFTEST_CHECK_BED			"Controleer bed  "
#define(length=20) MSG_SELFTEST_CHECK_ALLCORRECT	"Allemaal goed    "
#define MSG_SELFTEST						"Zelftest         "
#define(length=20) MSG_SELFTEST_FAILED		"Zelftest mislukt "
#define MSG_STATISTICS						"Statistieken"
#define MSG_USB_PRINTING					"USB printing  "
#define MSG_HOMEYZ                          "Kalibreren Z"
#define MSG_HOMEYZ_PROGRESS                 "Kalibreren Z"
#define MSG_HOMEYZ_DONE		                "Kalbibratie OK"

#define MSG_SHOW_END_STOPS					"Toon endstops"
#define MSG_CALIBRATE_BED					"Kalibratie XYZ"
#define MSG_CALIBRATE_BED_RESET				"Reset XYZ kalibr."

#define(length=20, lines=8) MSG_MOVE_CARRIAGE_TO_THE_TOP 	"Kalibreren van XYZ. Draai de knop om de Z-wagen omhoog te gaan tot het einde stoppers. Klik als klaar."
#define(length=20, lines=8) MSG_MOVE_CARRIAGE_TO_THE_TOP_Z 	"Kalibreren van XYZ. Draai de knop om de Z-wagen omhoog te gaan tot het einde stoppers. Klik als klaar."

#define(length=20, lines=8) MSG_CONFIRM_NOZZLE_CLEAN			"Reinig het tuit voor de kalibratie aub. Klik als klaar."
#define(length=20, lines=8) MSG_CONFIRM_CARRIAGE_AT_THE_TOP	"Zijn beide Z wagen heelemaal boven?"

#define(length=60) MSG_FIND_BED_OFFSET_AND_SKEW_LINE1		"Zoeke bed kalibratiepunt"
#define(length=14) MSG_FIND_BED_OFFSET_AND_SKEW_LINE2		" van 4"
#define(length=60) MSG_IMPROVE_BED_OFFSET_AND_SKEW_LINE1	"Nauwkeurigheid verbeteren bij kalibratiepunt"
#define(length=14) MSG_IMPROVE_BED_OFFSET_AND_SKEW_LINE2	" van 9"
#define(length=60) MSG_MEASURE_BED_REFERENCE_HEIGHT_LINE1	"Meten van reference hoogte van de kalibratiepunt"
#define(length=14) MSG_MEASURE_BED_REFERENCE_HEIGHT_LINE2	" van 9"
#define(length=20) MSG_FIND_BED_OFFSET_AND_SKEW_ITERATION	"Herhaling "

#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_POINT_NOT_FOUND			"XYZ kalibratie mislukt. Bed kalibratiepunt niet gevonden."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_FITTING_FAILED				"XYZ kalibratie mislukt. Raadpleeg de handleiding."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_PERFECT					"XYZ kalibratie ok. X/Y-assen staan perpendiculair. Gefeliciteerd!"
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_SKEW_MILD					"XYZ kalibratie ok. X/Y-assen zijn iets scheef. Scheefheid wordt automatisch gecorrigeerd. Goed gedaan!"
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_SKEW_EXTREME				"XYZ kalibratie ok. X/Y-assen zijn heel scheef. Scheefheid wordt automatisch gecorrigeerd."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_FAILED_FRONT_LEFT_FAR		"XYZ kalibratie mislukt. Linksvoor kalibratiepunt niet bereikbaar."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_FAILED_FRONT_RIGHT_FAR		"XYZ kalibratie mislukt. Rechtsvoor kalibratiepunt niet bereikbaar."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_FAILED_FRONT_BOTH_FAR		"XYZ kalibratie mislukt. Voorzijde kalibratiepunten niet bereikbaar."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_WARNING_FRONT_LEFT_FAR		"XYZ kalibratie gecompromitteerd. Linksvoor kalibratiepunt niet bereikbaar."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_WARNING_FRONT_RIGHT_FAR	"XYZ kalibratie gecompromitteerd. Rechtsvoor kalibratiepunt niet bereikbaar."
#define(length=20, lines=8) MSG_BED_SKEW_OFFSET_DETECTION_WARNING_FRONT_BOTH_FAR		"XYZ kalibratie gecompromitteerd. Voorzijde kalibratiepunten niet bereikbaar."

#define(length=20, lines=6) MSG_BED_LEVELING_FAILED_POINT_LOW						"Bed nivellering mislukt. Sensor was niet geactiveerd. Vuil op nozzle? Wacht op reset."
#define(length=20, lines=5) MSG_BED_LEVELING_FAILED_POINT_HIGH						"Bed nivellering mislukt. Een sensor heeft te hoog getriggerd. Wacht op reset."
#define(length=20, lines=6) MSG_BED_LEVELING_FAILED_PROBE_DISCONNECTED				"Bed nivellering mislukt.Sensor niet aangesloten of kabel gebroken.Wacht op reset"

#defineMSG_NEW_FIRMWARE_AVAILABLE								"Nieuwe firmware versie beschikbaar:"
#define(length=20) MSG_NEW_FIRMWARE_PLEASE_UPGRADE									"Upgraden aub."

#define(length=20, lines=8) MSG_FOLLOW_CALIBRATION_FLOW								"Printer is nog niet gekalibreerd. Volg de handleiding, hoofdstuk First steps, sectie Calibration flow."
#define(length=20, lines=12) MSG_BABYSTEP_Z_NOT_SET									"Afstand tussen tip van het tuit en het print oppervlak nog niet vastgesteld. Volg de handleiding, First steps, sectie First layer calibration."

#define(length=20, lines=4) MSG_FILAMENT_LOADING_T0							"Steek filament in de extruder 1. Klik als klaar."
#define(length=20, lines=4) MSG_FILAMENT_LOADING_T1							"Steek filament in de extruder 2. Klik als klaar."
#define(length=20, lines=4) MSG_FILAMENT_LOADING_T2							"Steek filament in de extruder 3. Klik als klaar."
#define(length=20, lines=4) MSG_FILAMENT_LOADING_T3							"Steek filament in de extruder 4. Klik als klaar."
#define(length=20, lines=1) MSG_CHANGE_EXTR									"Wissel extruder"

#define(length=20, lines=2) MSG_FIL_LOADED_CHECK								"Is filament ingestoken?"
#define(length=20, lines=3) MSG_FIL_TUNING										"Knop draaien om filament in te stellen."
#define(length=20, lines=4) MSG_FIL_ADJUSTING								"Aanpassen filamenten. Even geduld aub."
#define(length=20, lines=8) MSG_CONFIRM_NOZZLE_CLEAN_FIL_ADJ			"Filamenten zijn nu ingesteld. Reinig het tuit voor de kalibratie. Klik als klaar."
#define(length=20, lines=4) MSG_STACK_ERROR						"Error - static memory has been overwritten"
#define(length=20, lines=1) MSG_CALIBRATE_E						"Kalibratie E"
//#define(length=20, lines=1) MSG_RESET_CALIBRATE_E				"Reset E Cal."
#define(length=20, lines=8) MSG_E_CAL_KNOB						"Draai knop tot mark extruder bereikt is. Klik als klaar."

//#define(length=20, lines=1) MSG_FARM_CARD_MENU					"Farm mode print"
#define(length=20, lines=8) MSG_MARK_FIL						"Mark filament 100mm van extruder body. Klik als klaar."
#define(length=20, lines=8) MSG_CLEAN_NOZZLE_E				"E kalibratie voltooid. Reinig het tuit. Klik op als klaar."
#define(length=20, lines=3) MSG_WAITING_TEMP				"Wachten op afkoelen van heater en bed."
#define(length=20, lines=2) MSG_FILAMENT_CLEAN				"Is kleur zuiver?"
#define(length=20) MSG_UNLOADING_FILAMENT			"Filament uitwerpen"
#define(length=20, lines=10) MSG_PAPER						"Leg een vel papier onder het tuit tijdens de kalibratie van de eerste 4 punten. Als het tuit het papier vangt, Printer onmiddellijk uitschakelen."

#define(length=20) MSG_BED_CORRECTION_MENU									"Bed juist"
#define MSG_BED_CORRECTION_LEFT									"Links     [um]"
#define MSG_BED_CORRECTION_RIGHT								"Rechts    [um]"
#define MSG_BED_CORRECTION_FRONT								"Voorruit  [um]"
#define MSG_BED_CORRECTION_REAR									"Achter    [um]"
#define MSG_BED_CORRECTION_RESET								"Reset"

#define MSG_MESH_BED_LEVELING									"Mesh Bed Leveling"
#define MSG_MENU_CALIBRATION									"Kalibratie"
#define MSG_TOSHIBA_FLASH_AIR_COMPATIBILITY_OFF					"SD card [normal]"
#define MSG_TOSHIBA_FLASH_AIR_COMPATIBILITY_ON					"SD card [FlshAir]"
#define MSG_PRINTER_DISCONNECTED								"Printer ontbonden"
#define(length=20) MSG_FINISHING_MOVEMENTS									"Bewegingen afwerken"
#define MSG_PRINT_PAUSED										"Druck pauzeren"
#define MSG_RESUMING_PRINT										"Print hervatten"
#define MSG_PID_EXTRUDER										"PID kalibratie"
#define MSG_SET_TEMPERATURE										"Temp. instellen"
#define MSG_PID_FINISHED										"PID kal. klaar      "
#define MSG_PID_RUNNING											"PID kal.     "
#define MSG_PID_BED												"PID bed kalibratie  "
#define MSG_PID_BED_FINISHED									"PID bed kal. klaar  "
#define MSG_PID_BED_RUNNING										"PID bed kal. "

#define MSG_CALIBRATE_PINDA										"PINDA Temp. kal."
#define MSG_CALIBRATION_PINDA_MENU								"PINDA Temp. kal."
#define(length=20, lines=3) MSG_PINDA_NOT_CALIBRATED								"PINDA temperatuur calibratie was nog niet uitgevoerd"
#define MSG_PINDA_PREHEAT										"PINDA warmt op"
#define(length=20) MSG_TEMP_CALIBRATION									"PINDA Temp.kal."
#define(length=20, lines=3) MSG_TEMP_CALIBRATION_DONE								"PINDA temperatuur calibratie is klaar. Klik om door te gaan."
#define(length=20) MSG_TEMP_CALIBRATION_ON								"PINDA T.kal. [ON]"
#define(length=20) MSG_TEMP_CALIBRATION_OFF								"PINDA T.kal.[OFF]"
#define(length=20, lines=1) MSG_PREPARE_FILAMENT				"Filament voorbereden"
