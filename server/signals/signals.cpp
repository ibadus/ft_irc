#include "signals.hpp"

#include <signal.h>

void initAllSignalHandlers() {
	signal(SIGINT, sigIntHandler); // allows to ctrl+c the server once it's started
}