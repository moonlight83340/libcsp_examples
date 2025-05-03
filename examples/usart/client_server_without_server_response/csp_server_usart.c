#include <csp/csp.h>
#include <csp/csp_debug.h>
#include <csp/drivers/usart.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "csp_posix_helper.h"

#define SERVER_ADDRESS 2
#define CLIENT_ADDRESS 1
#define SERVER_PORT    10
#define DEVICE_NAME    "/tmp/pty1"

void * server(void * param) {
	(void)param;
	csp_print("Server task started\n");

	csp_socket_t sock = {0};
	csp_bind(&sock, CSP_ANY);
	csp_listen(&sock, 10);

	while (1) {
		csp_conn_t * conn = csp_accept(&sock, 10000);
		if (!conn)
			continue;

		csp_packet_t * packet;
		while ((packet = csp_read(conn, 50)) != NULL) {
			if (csp_conn_dport(conn) == SERVER_PORT) {
				csp_print("Received: %s\n", (char *)packet->data);
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
	csp_print("Initializing CSP with USART interface...\n");

	/* Set protocol version and address */
	csp_conf.version = 2;

	/* Init CSP */
	csp_init();

	/* Start router */
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

	csp_print("Connection table\r\n");
	csp_conn_print_table();

	csp_print("Interfaces\r\n");
	csp_iflist_print();

	csp_pthread_create(server);

	while (1) {
		sleep(1);
	}

	return 0;
}
