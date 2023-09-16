#ifndef STATUS_HPP
#define STATUS_HPP

enum te_status {
	e_STOPPED = 0,
	e_RUNNING = 1,
	e_RESTARTING = 2
};

/*
* 0 = stopped, 1 = running, 2 = restarting
*
* set to 0 in server() and 1 in server.start() method
*
* Note: state of the server needs to be global to be accessed by the signal handler
*/
te_status global_status = e_STOPPED;

#endif