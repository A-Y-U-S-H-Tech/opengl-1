/*
this defines  logging tools for both the program and opengl functions
*/
extern char logbuff[];//buffer to store the log message
extern const char defaultfile[];//file to store the logs in

void logFileAppend();//appends the log file with error logs
void gllog();//gets any gl eror if eror the appends the log file via logFileAppend
void consoleLog();//used to log info to the console
void consoleLogLogerError(char * data);

//specific function to check error for specific opengl functions
void shaderChecker(unsigned int shader);
void programChecker(unsigned int program);