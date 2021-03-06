#ifndef PROCESS_CONTROL_BLOCK_H
#define PROCESS_CONTROL_BLOCK_H

#include <time.h>
#include <thread>
#include <unistd.h>
#include "Logger.h"
#include "ConfigurationSettings.h"

using namespace std;

extern Logger myLog;

/**
 * Used for creating new threads.
 * Converts given parameter to microseconds
 * Then calls usleep
 *
 * Pre: None
 * Post: Program will wait sleepTime milliseconds
 * 
 * @param sleepTimeInMilliSec Sleep time given in milliseconds
 */
//static void createThreadThatSleeps(
//	int sleepTimeInMilliSec );

class ProcessControlBlock
{
public:
	/**
	 * ProcessControlBlock constructor
	 * Updates this PCB's processNumber and various cycleTime settings
	 * - ProcessCycleTime
	 * - MonitorDisplayTime
	 * - HardDriveCycleTime
	 * - PrinterCycleTime
	 * - KeyboardCyelTime
	 *
	 * Pre: None
	 * Post: Will update all settings necessary for this object to function
	 * correctly.
	 */
	ProcessControlBlock( 
		int pProcessNumber, 
		const ConfigurationSettings &pSettings );

	/**
	 * Creates a new Processor Thread
	 * Sets sleep time to processCycleTime * cycleTime
	 * Creates new thread, then waits for thread to end.
	 *
	 * Pre: processCycleTime has been set appropriately
	 * Post: Program will create and wait for a processor thread
	 * Will also log output for start/end of process
	 * 
	 * @param operation Name of the operation, used for output
	 * @param cycleTime Number of cycles to run for
	 */
	void newProcessThread( 
		string operation, 
		int cycleTime );

	/**
	 * Creates a new Processor Thread
	 * Sets sleep time to 
	 *  hardDriveCycleTime * cycleTime
	 *  keyboardCycleTime * cycleTime
	 * based on the given operation
	 * Creates new thread, then waits for thread to end.
	 *
	 * Pre: hardDriveCycleTime and keyboardCycleTime
	 * have been set appropriately
	 * Post: Program will create and wait for a input thread
	 * Will also log output for start/end of process
	 * 
	 * @param operation Name of the operation, used for output
	 * @param cycleTime Number of cycles to run for
	 */
	void newInputThread( 
		string operation, 
		int cycleTime );

	/**
	 * Creates a new Output Thread
	 * Sets sleep time to 
	 *  hardDriveCycleTime * cycleTime
	 *  monitorDisplayTime * cycleTime
	 *  printerCycleTime * cycleTime
	 * based on the given operation
	 * Creates new thread, then waits for thread to end.
	 *
	 * Pre: hardDriveCycleTime, monitorDisplayTime, printerCycleTime
	 * have been set appropriately
	 * Post: Program will create and wait for an output thread
	 * Will also log output for start/end of process
	 * 
	 * @param operation Name of the operation, used for output
	 * @param cycleTime Number of cycles to run for
	 */
	void newOutputThread( 
		string operation, 
		int cycleTime );
private:
	int processNumber;
	int processCycleTime;
	int monitorDisplayTime;
	int hardDriveCycleTime;
	int printerCycleTime;
	int keyboardCycleTime;
	// Future: Queue for CPU scheduling
};
#endif // PROCESS_CONTROL_BLOCK_H