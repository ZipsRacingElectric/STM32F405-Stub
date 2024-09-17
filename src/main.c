// Includes -------------------------------------------------------------------------------------------------------------------

// ChibiOS
#include "ch.h"
#include "hal.h"

// Threads --------------------------------------------------------------------------------------------------------------------

static THD_WORKING_AREA (heartbeatWa, 128);

static THD_FUNCTION (heartbeatThread, arg)
{
	(void) arg;
	chRegSetThreadName ("heartbeat");

	while (true)
	{
		// palSetLine (0);
		chThdSleepMilliseconds (10000);
		// palClearLine (0);
		chThdSleepMilliseconds (10000);
	}
}

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main(void)
{
	// ChibiOS Initialization
	halInit ();
	chSysInit ();

	// Create the heartbeat thread
	chThdCreateStatic (heartbeatWa, sizeof(heartbeatWa), NORMALPRIO, heartbeatThread, NULL);

	// Do nothing.
	while (true)
		chThdSleepMilliseconds (500);
}
