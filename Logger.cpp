#include "stdafx.h"
#include "Logger.h"

Logger::Logger() { // overloaded constructor for console logging 
	log_output_type = logger_output::CONSOLE;
	populate_log_type_map();
}
Logger::Logger(string filename, int filerenewaltime) { // overloaded constructor for file logging takes files name and file renewal time in days 
	filerenewal_time = filerenewaltime;
	log_output_type = logger_output::FILE;
	begin_time = time(0);
	string buf = formatime(begin_time);
	given_filename = filename;
	complete_filename = filename + currentdate + ".txt";
	populate_log_type_map();
}
void Logger::log(log_types logtype, string usertype, string message) {
	if (message != "")
		message = "\"" + message + "\"";
	string output = get_current_datetime() + " " + log_type_description[logtype] + "-" + usertype + message;
	if (log_output_type == logger_output::CONSOLE) {
		console_log_mutex.lock();
		cout << output << endl;
		console_log_mutex.unlock();
	}
	else {
		file_log_mutex.lock();
		if (get_noofdays(begin_time) == filerenewal_time) {
			string buf = formatime(time(0));
			complete_filename = given_filename + currentdate + ".txt";
			logfile.open(complete_filename, ios::out | ios::app);
			logfile << output << endl;
			logfile.close();
		}
		else {
			logfile.open(complete_filename, ios::out | ios::app);
			logfile << output << endl;
			logfile.close();
		}
		file_log_mutex.unlock();
	}

}
void Logger::populate_log_type_map()
{
	log_type_description[Logger::log_types::INFO] = "Log:Info";
	log_type_description[Logger::log_types::ERR] = "Log:Error";
	log_type_description[Logger::log_types::CRITICAL] = "Log:Critical";
	log_type_description[Logger::log_types::MSG] = "Log:Message";
	log_type_description[Logger::log_types::WARN] = "Log:Warning";
}
void Logger::log_info(string usertype, string message) { // to log information messages
	log(log_types::INFO, usertype, message);
}
void Logger::log_error(string usertype, string message) { // to log error messages
	log(log_types::ERR, usertype, message);
}
void Logger::log_warning(string usertype, string message) { // to log warnings
	log(log_types::WARN, usertype, message);
}
void Logger::log_message(string usertype, string message) { // to log general messages
	log(log_types::MSG, usertype, message);
}
void Logger::log_critical(string usertype, string message) { // to log critical messages
	log(log_types::CRITICAL, usertype, message);
}
string Logger::get_current_datetime() {
	time_t now = time(0);
	string buf = formatime(now);
	return buf;
}
string Logger::formatime(time_t formattime) {
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&formattime);
	currentdate = to_string(tstruct.tm_mday) + "-" + to_string(tstruct.tm_mon + 1) + "-" + to_string(tstruct.tm_year + 1900);
	strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);
	return buf;
}
int Logger::get_noofdays(time_t begintime) {
	time_t now = time(0);
	struct tm then = *localtime(&begintime);
	struct tm today = *localtime(&now);
	struct tm a = { 0,0,0,then.tm_mday,then.tm_mon,then.tm_year }; // begin date of logging
	struct tm b = { 0,0,0,today.tm_mday,today.tm_mon,today.tm_year };  // todays date
	time_t x = mktime(&a);
	time_t y = mktime(&b);
	if (x != (time_t)(-1) && y != (time_t)(-1))
	{
		double difference = difftime(y, x) / (60 * 60 * 24);
		return difference;
	}
	return 0;
}
Logger::~Logger()
{
}
