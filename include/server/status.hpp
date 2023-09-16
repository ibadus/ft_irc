#ifndef STATUS_HPP
#define STATUS_HPP

enum te_status {
	e_STOP = 0,
	e_RUN = 1,
	e_RESTART = 2
};

/*
* 0 = stop, 1 = run, 2 = restart
*
* initalized to 0 in Server.cpp and 1 in server.start() method
*
* Note: state of the server needs to be global to be accessed by the signal handler
*/
extern te_status global_status;

#endif