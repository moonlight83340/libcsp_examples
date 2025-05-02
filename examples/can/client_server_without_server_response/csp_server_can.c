#include <csp/csp.h>
#include <csp/csp_debug.h>
#include <csp/drivers/can_socketcan.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csp_posix_helper.h"

#define SERVER_ADDRESS 2
#define CLIENT_ADDRESS 1
#define SERVER_PORT    10
#define VCAN_DEVICE    "vcan0"

static unsigned int server_received = 0;

/* Server thread */
void * server(void * param) {
	(void)param;

	csp_print("Server thread started\n");

	csp_socket_t sock = {0};
	csp_bind(&sock, CSP_ANY);
	csp_listen(&sock, 5);

	while (1) {
		csp_conn_t * conn = csp_accept(&sock, 10000);
		if (!conn)
			continue;

		csp_packet_t * packet;
		while ((packet = csp_read(conn, 100)) != NULL) {
			if (csp_conn_dport(conn) == SERVER_PORT) {
				csp_print("Received: %s\n", (char *)packet->data);
				server_received++;
				csp_buffer_free(packet);
			} else {
				csp_service_handler(packet);
			}
		}

		csp_close(conn);
	}

	return NULL;
}

int main(void) {
	csp_print("Initializing CSP with CAN interface...\n");

	/* Set protocol version and address */
	csp_conf.version = 2;

	/* Init CSP */
	csp_init();

	/* Start router */
	router_start();

	/* Add CAN interface */
	csp_iface_t * iface = NULL;
	if (csp_can_socketcan_open_and_add_interface(
			VCAN_DEVICE, CSP_IF_CAN_DEFAULT_NAME, SERVER_ADDRESS, 1000000, true,
			&iface) != CSP_ERR_NONE) {
		csp_print("Failed to add CAN interface\n");
		return 1;
	}
	iface->is_default = 1;

	csp_print("Interfaces:\n");
	csp_iflist_print();

	csp_print("Starting server...\n");
	csp_pthread_create(server);

	while (1) {
		sleep(5);
		csp_print("Received %u packets so far\n", server_received);
	}

	return 0;
}
