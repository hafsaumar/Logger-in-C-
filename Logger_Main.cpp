// Logger_Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include "Logger.h"
#include<thread>
#include <cstdio>

void logging();					// Thread function that is logging

Logger consolelog;				// logger object created for logging onto console
Logger filelog("logfile", 5);	// logger object for writting into the file
								// it takes two parameters: 1- the filename without extension 2- renewal time of the file in number of days

int main()
{
	/*creates 100 threads that logs the same information on console and file*/

	thread threads[10];
	for (int i = 0; i<10; i++)			
		threads[i] = thread(logging);

	for (auto& th : threads) th.join();
	getchar();
    return 0;
}

void logging() {
	// admin logs information without any message on console and on file
	consolelog.log_info("Admin");
	filelog.log_info("Admin");

	// Developer logging error with a message on console and file
	consolelog.log_error("Developer", "This is an error logging");
	filelog.log_error("Developer", "This is an error logging");

	//Developer logging warning
	consolelog.log_warning("Developer", "This is an warning logging");
	filelog.log_warning("Developer", "This is an warning logging");

	// QA Logs message
	consolelog.log_message("QA", "This is an message logging");
	filelog.log_message("QA", "This is an message logging");

	// Developer logs something critical with message
	consolelog.log_critical("Developer", "This is an critical logging");
	filelog.log_critical("Developer", "This is an critical logging");
}
