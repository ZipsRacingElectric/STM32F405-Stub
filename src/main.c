// Includes -------------------------------------------------------------------------------------------------------------------

// Includes
#include "debug.h"

// ChibiOS
#include "ch.h"
#include "hal.h"

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main (void)
{
	// ChibiOS Initialization
	halInit ();
	chSysInit ();

	// Debug Initialization
	debugInit ("STMF405 Stub Project");

	// Do nothing.
	while (true)
		chThdSleepMilliseconds (500);
}

void faultCallback (void)
{
	// Fault handler implementation
}