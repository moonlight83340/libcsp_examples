#include <csp/csp_debug.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <csp/csp.h>
#include <csp/drivers/can_socketcan.h>

#include "csp_posix_helper.h"

#define SERVER_PORT    10
#define VCAN_DEVICE    "vcan0"
#define CLIENT_ADDRESS 1
#define SERVER_ADDRESS 2

int main(void) {
	int ret = EXIT_SUCCESS;
	struct timespec start_time, current_time;
	unsigned int successful_ping = 0;
	unsigned int run_duration_in_sec = 3;
	unsigned int count = 'A';

	/* Set CSP protocol version and address */
	csp_conf.version = 2;

	/* Initialize CSP */
	csp_init();

	/* Start CSP router */
	router_start();

	/* Add CAN interface */
	csp_iface_t * iface = NULL;
	int error = csp_can_socketcan_open_and_add_interface(VCAN_DEVICE, CSP_IF_CAN_DEFAULT_NAME, CLIENT_ADDRESS, 1000000, true, &iface);
	if (error != CSP_ERR_NONE) {
		csp_print("Error adding CAN interface [%s], error: %d\n", VCAN_DEVICE, error);
		return EXIT_FAILURE;
	}

	/* Set this interface as default */
	iface->is_default = 1;

	/* Print interface list */
	csp_print("Available interfaces:\n");
	csp_iflist_print();

	csp_print("Client started\n");

	while (1) {
		/* Wait 200 ms between iterations */
		usleep(200000);

		/* Send a CSP ping to the server */
		int result = csp_ping(SERVER_ADDRESS, 1000, 100, CSP_O_NONE);
		csp_print("Ping to address %u, result %d [ms]\n", SERVER_ADDRESS, result);
		if (result >= 0) {
			++successful_ping;
		}

		/* Establish a connection to the server */
		csp_conn_t * conn = csp_connect(CSP_PRIO_NORM, SERVER_ADDRESS, SERVER_PORT, 1000, CSP_O_NONE);
		if (conn == NULL) {
			csp_print("Connection failed\n");
			ret = EXIT_FAILURE;
			break;
		}

		/* Get a CSP packet buffer */
		csp_packet_t * packet = csp_buffer_get(0);
		if (packet == NULL) {
			csp_print("Failed to obtain CSP buffer\n");
			ret = EXIT_FAILURE;
			break;
		}

		/* Fill the packet with data */
		snprintf((char *)packet->data, CSP_BUFFER_SIZE, "Hello world %c", count++);
		packet->length = strlen((char *)packet->data) + 1;

		/* Send the packet and close the connection */
		csp_send(conn, packet);
		csp_close(conn);
	}

	return ret;
}
