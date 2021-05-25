/**
 * @brief Used to aid in debugging
 * @author Bryce Standley
 * @date 08/04/2021
 * @version 1
 */

#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <regex>
#include <chrono>


/**
 * @class Debugger
 * @brief helper functions and flags to aid in debugging aspects of the engine
 */
class Debugger{
public:
    static Debugger* GetInstance();


    /**
     * @brief turns a vec3 into a string for console output
     * @param Vec3 a
     * @return string - string value with each XYZ of a given vec3
     */
    std::string DebugVec3(glm::vec3 a);

    /**
     * @brief Used to open the log file and save its pointer
     */
	void OpenLogger();

	/**
	 * @brief Appends a string to the log file with current time of the system and information where the append came from
	 * @param type
	 * @param fromFile
	 * @param outputString
	 */
	void AppendLogger(std::string fromFile, std::string outputString);

	/**
	 * @brief closes the log file on exit
	 */
	void CloseLogger();


    /**
     * @brief flag for enabling/disabling debug and error information in the console
     */
    bool debugToConsole = false;

    /**
     * @brief flag for enabling/disabling debug information about collisions in the console
     */
    bool debugCollisionsToConsole = false;

	/**
	 * @brief flag for enabling/disabling debug information about FSM in the console
	 */
    bool debugFSMToConsole = false;

	/**
	 * @brief flag for enabling/disabling debug information about weapons in the console
	 */
    bool debugWeapons = false;

	/**
	 * @brief flag for enabling/disabling debug information about tokens in the console
	 */
    bool debugTokensToConsole = false;

	/**
	 * @brief flag for enabling/disabling debug information about animations in the console
	 */
    bool debugAnimationsToConsole = false;

	/**
	 * @brief flag for enabling/disabling debug information about MD2 in the console
	 */
    bool debugMD2ToConsole = false;

	/**
	 * @brief flag for enabling/disabling debug information about player position in the the game screen
	 */
	bool debugPlayerPos = false;

	/**
	 * @brief flag for enabling/disabling debug information about framerate in the game screen
	 */
	bool stickyFPSCounter = false;

	/**
	 * @brief flag for enabling/disabling debug information about info types to the log file
	 */
	bool debugInfoToLogFile = false;

	/**
	 * @brief flag for enabling/disabling debug information about error types to the log file
	 */
	bool debugErrorsToLogFile = false;

	/**
	 * @brief flag for enabling/disabling debug information about engine types to the log file
	 */
	bool debugEngineToLogFile = true;

	/**
	 * @brief Flag for enabling/disabling debug information about warning types to the log file
	 */
	bool debugWarningToLogFile = false;

	/**
	 * @brief flag for enabling/disabling the debug panel
	 */
    bool drawDebugPanel = false;

	/**
	 * @brief reference to a GLFW window
	 */
    GLFWwindow* windowRef = nullptr;

    /**
     * @brief Enum of different log types
     */
    enum LogType
    {
    	INFO,
    	WARNING,
    	ERROR,
    	ENGINE,
    	ALL
    };

	/**
	 * @brief String of log file path
	 */
	std::string logFilePath;

	/**
	 * @brief Global log type
	 */
	LogType type = ENGINE;



private:

	/**
	 * @brief File pointer of log
	 */
	FILE* logFile;



	/**
	 *  @brief Converts a log type enum to a string for using in the logging process
	 * @param logtype t
	 * @return string of type
	 */
	std::string LogTypeToString(LogType t);




protected:
    Debugger() = default;
    static Debugger* instance;


};


#endif //DEBUGGING_H