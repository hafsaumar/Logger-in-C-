# Logger for Windows in C++ Implemented using Microsoft Visual Studio 2017 IDE.

*This class API is implemented in C++11 for logging (information, errors, warning etc) in windows. *

## OverView:
It supports two types of log outputs; Console and File logging. 
	- The type of output is decided at the time of object creation; there are two types of constructors to create the logger object
		1. Without any arguments: this type of object would be created for console output as it just initializes all the elements itselt.
		1. With two arguments: this type of object would be created for file output as it takes filename and file renewal time(in days) as arguments. 
			- Filename must b provided without the file extention as it only supports text file logging and automatically creates the full file name. Also, Filename must be only 8 characters long or else the file name becomes too long and text time would not be generated.
			- It also adds current date to the filename because after the given ammount of days it will renew the file and will add new date to the given filename.

There are five different types of Logging that can be performed:
	1. Information,
	1. Errors,
	1. Warnings,
	1. Critical and
	1. General Messages(/notes)

### Logging Format:
Following is the format of both of the logging outputs:
	_[current datetime] [LoggingType]-[User] "[Message]"_
whereas:
	[LoggingType] = Info, Error, Warning, Critical or Message.
	[User] = Username or User type/ role such as admin, developer, QA etc. This part has to provided at the time of logging by the responsible person.
	[Message] = this is string message that can be stored with the logs for later use. This is an optional argument, User can log any activity with or without a message.
*Example logging  format:*
	_2017-07-09-21:04:11 Log-Error-Developer "An error has occured"_

For logging five types of logging there are following functions: (each of them take two arguments: Usertype and An optional message for logging)
	1. log_infor()
	1. log_Error()
	1. log_Warning()
	1. log_critical()
	1. log_message()
This is done for the ease of user at the time of logging, user could only use the desired function and that function maps to the respective type of logging using key-value mapping.

Log() function, takes the logging type, user type and message, formats the logging string and logs that string onto the desired output (console or file).

### How Renewal of file works?
This logger gives user the choice of storing the data into the same file for as much long as he wants. at the start of file logging, file renewal days are asked, and before logging its checks of the number of days between the start of logging and today is equal to the days of renewal, then it generates a new file for logging.
By doing this, storing and reading the logs might get easier as well as maintainance.

### How multiThreading is supported?
Since all the logging is taking place in the same file/console, so it nultiple threads are logging so the logs could get dispersed. to avoid that mutexes are used to lock the file/console while one thread is logging and other would wait until that thread unlocks the mutex after it finishes. 
This is the most simple yet affective solution the problem. 

### Ideas for Furture Development:
- A new type of logging for Debugging mode can be introduced
- It could also support outputting Logging Enviroment(test, production, Development etc).
- logging output in databases can also be introduced.
- It can also be extended for key logger, that would log all the keystrokes and activities of the application while in use.

### Shortcomings and Known Issues:
- As the mutexes are used so for thousands of working threads race condition might occure while logging. 
- filename is just restricted to 8 characters, which sometimes is not convenient. 