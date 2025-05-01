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
	unsigned int count = 'A';

	csp_print("Initializing CSP with KISS device: %s\n", DEVICE_NAME);
	csp_init();
	router_start();

	csp_iface_t * default_iface = NULL;
	csp_usart_conf_t conf = {
		.device = DEVICE_NAME,
		.baudrate = 115200, /* supported on all platforms */
		.databits = 8,
		.stopbits = 1,
		.paritysetting = 0,
	};
	if(csp_usart_open_and_add_kiss_interface(&conf, CSP_IF_KISS_DEFAULT_NAME, CLIENT_ADDRESS, &default_iface) != CSP_ERR_NONE) {
		csp_print("Failed to add KISS interface\n");
		return EXIT_FAILURE;
	}

	default_iface->is_default = 1;

	csp_print("Client started\n");

	while (1) {
		/* Send every 1s */
		usleep(1000000);

		/* Connect to the server, here we will use a connection, so we have a handshake before sending message */
		/* Using a connection less client, server with csp would be maybe more apropriate when sending simple command or telemetry */
		/* But if you want a reliable connection you should use a connection and use rdp option for example, we will not use rdp here */
		csp_conn_t * conn = csp_connect(CSP_PRIO_NORM, SERVER_ADDRESS, SERVER_PORT, 1000, CSP_O_NONE);
		if (!conn) {
			csp_print("Connection failed\n");
			continue;
		}

		csp_packet_t * packet = csp_buffer_get(0);
		if (!packet) {
			csp_print("Failed to get packet buffer\n");
			csp_close(conn);
			continue;
		}

		/* Send Hello world with a counter */
		snprintf((char *)packet->data, CSP_BUFFER_SIZE, "Hello world %c", count++);
		packet->length = strlen((char *)packet->data) + 1;

		csp_send(conn, packet);

		csp_packet_t * reply = csp_read(conn, 1000);
		if (reply) {
			csp_print("Server replied: %s\n", (char *)reply->data);
			csp_buffer_free(reply);
		} else {
			csp_print("No reply from server\n");
		}

		csp_close(conn);
	}

	return EXIT_SUCCESS;
}
