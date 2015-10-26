#include "ProcessControlBlock.h"

static void createThreadThatSleeps( 
	int sleepTimeInMilliSec )
{
	int sleepTimeInMicroSec = sleepTimeInMilliSec * 1000;
	usleep( sleepTimeInMicroSec );
}

ProcessControlBlock::ProcessControlBlock( 
	int pProcessNumber, 
	const ConfigurationSettings & pSettings )
{
	processNumber = pProcessNumber;
	processCycleTime = pSettings.processCycleTime;
	monitorDisplayTime = pSettings.monitorDisplayTime;
	hardDriveCycleTime = pSettings.hardDriveCycleTime;
	printerCycleTime = pSettings.printerCycleTime;
	keyboardCycleTime = pSettings.keyboardCycleTime;
}

void ProcessControlBlock::runThreads()
{
	// Check that there are threads to run
	if(readyProcessThreads.size() == 0)
	{
		myLog.logError( "This ProcessControlBlock has no processes, but was asked to run its threads" );
	}
	// Iterate through each thread
	// Process thread, then dump from ready queue to finished queue
	while(readyProcessThreads.size() != 0)
	{
		// Log start process
		myLog.logProcess( readyProcessThreads.front() );
		// Sleep
		thread process( createThreadThatSleeps, readyProcessThreads.front() );
		process.join();
		// Log end process
		myLog.logProcess( readyProcessThreads.front() );
		// Push front of ready to finished, then pop it off of ready
		finishedProcessThreads.push_back( readyProcessThreads.front( ) );
		readyProcessThreads.erase( readyProcessThreads.begin( ) );
	}
}

void ProcessControlBlock::newProcessThread( 
	string operation, 
	int numberOfCycles )
{
	int processTime;
	string startLogMessage, endLogMessage;
	// Process #: start processing action
	startLogMessage =
		string( "Process " ) + 
		to_string( processNumber ) + 
		": start processing action" );
	// Calculate the time thread will need to be processed
	processTime = processCycleTime * numberOfCycles;
	endLogMessage =
		string( "Process " ) + 
		to_string( processNumber ) + 
		": end processing action" );
	// Initialize the new thread
	os_thread currentThread;
	currentThread.startLogMessage = startLogMessage;
	currentThread.endLogMessage = endLogMessage;
	currentThread.processTime = processTime;
	// Push thread to back of ready queue
	readyProcessThreads.push_back( currentThread );
}

void ProcessControlBlock::newInputThread( 
	string operation, 
	int numberOfCycles )
{
	int processTime;
	string startLogMessage, endLogMessage;
	// Process #: start <operation> input
	startLogMessage =
		string( "Process " ) + 
		to_string( processNumber ) + 
		": start " + operation + " input" );
	// Calculate the time thread will need to be processed
	if( operation.compare( "hard drive" ) == 0 )
	{
		processTime = hardDriveCycleTime * numberOfCycles;
	}
	else if( operation.compare( "keyboard" ) == 0 )
	{
		processTime = keyboardCycleTime * numberOfCycles;
	}
	// Process #: end <operation> input
	endLogMessage =
		string( "Process " ) + 
		to_string( processNumber ) + 
		": end " + operation + " input" );
	// Initialize the new thread
	os_thread currentThread;
	currentThread.startLogMessage = startLogMessage;
	currentThread.endLogMessage = endLogMessage;
	currentThread.processTime = processTime;
	// Push thread to back of ready queue
	readyProcessThreads.push_back( currentThread );
}

void ProcessControlBlock::newOutputThread( 
	string operation, 
	int numberOfCycles )
{
	int processTime;
	string startLogMessage, endLogMessage;
	// Process #: start <operation> output
	startLogMessage =
		string( "Process " ) + 
		to_string( processNumber ) + 
		": start " + operation + " output" );
	// Calculate the time thread will need to be processed
	if( operation.compare( "hard drive" ) == 0 )
	{
		processTime = hardDriveCycleTime * numberOfCycles;
	}
	else if( operation.compare( "monitor" ) == 0 )
	{
		processTime = monitorDisplayTime * numberOfCycles;
	}
	else if( operation.compare( "printer" ) == 0 )
	{
		processTime = printerCycleTime * numberOfCycles;
	}
	// Process #: end <operation> output
	endLogMessage =
		string( "Process " ) + 
		to_string( processNumber ) + 
		": end " + 
		operation + 
		" output" );
	// Initialize the new thread
	os_thread currentThread;
	currentThread.startLogMessage = startLogMessage;
	currentThread.endLogMessage = endLogMessage;
	currentThread.processTime = processTime;
	// Push thread to back of ready queue
	readyProcessThreads.push_back( currentThread );
}