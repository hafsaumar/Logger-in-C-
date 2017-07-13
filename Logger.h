/*---------------------------------------
		Logger.h
		logger for windows
		by, Hafsa Umar
----------------------------------------*/

#ifndef LOGGER_H   
#define LOGGER_H

#pragma once
#include <String>
#include <fstream>
#include <mutex>
#include<map>
#include <time.h>
#include <iostream>
using namespace std;

class Logger
{
public:
	enum logger_output {	//types of output supported
		CONSOLE,
		FILE
	};	
	Logger( string filename, int filerenewaltime);	// overloaded constructor for file logging takes files name and file renewal time in days 
	Logger();										// constructor for console logging
	~Logger();

	enum log_types {		// types of logs supported
		MSG,
		INFO,
		WARN,
		ERR,
		CRITICAL,
	};	
	void log_info(string usertype, string message = "") ;	// to log information messages
	void log_error(string usertype, string message = "") ;	// to log error messages
	void log_warning(string usertype, string message = "");	// to log warnings
	void log_message(string usertype, string message = "");	// to log general messages
	void log_critical(string usertype, string message = ""); // to log critical messages
	
private:
	logger_output log_output_type;		// output type: console or file
	int filerenewal_time;				// file renewal time in days 
	string complete_filename;			// complete filename with date and extension 
	string given_filename;				// given filename without date and extension
	ofstream logfile;					// for opening and writing into the log file
	mutex file_log_mutex;				// for locking the file while logging
	mutex console_log_mutex;			// for locking the console while logging
	time_t begin_time;					// logging begin time
	string currentdate;					// to store current date

	map<Logger::log_types, string> log_type_description;			// for mapping types of logs 
	void populate_log_type_map();									// to populate the types of log via maps
	string get_current_datetime();									// to get current date and time
	void log(log_types logtype, string usertype, string message);	// to format and log output
	string formatime(time_t formattime);							// to make the date time in a consistant format 
	int get_noofdays(time_t begintime);								// to get the number of days since the begin time
};
#endif
