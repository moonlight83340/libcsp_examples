#include <csp/csp_debug.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <csp/csp.h>
#include <csp/drivers/usart.h>

#include "csp_posix_helper.h"

#define SERVER_PORT    10
#define DEVICE_NAME    "/tmp/pty2"
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

	/* Add USART interface */
	csp_iface_t * iface = NULL;
	csp_usart_conf_t conf = {
		.device = DEVICE_NAME,
		.baudrate = 115200, /* supported on all platforms */
		.databits = 8,
		.stopbits = 1,
		.paritysetting = 0,
	};
	if (csp_usart_open_and_add_kiss_interface(&conf, CSP_IF_KISS_DEFAULT_NAME,
											  SERVER_ADDRESS,
											  &iface) != CSP_ERR_NONE) {
		csp_print("Failed to add KISS interface\n");
		return -1;
	}
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
