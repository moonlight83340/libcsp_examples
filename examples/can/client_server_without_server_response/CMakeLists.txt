# CAN node 1
add_executable(csp_client_can
    csp_client_can.c
)
target_link_libraries(csp_client_can csp utils Threads::Threads)

# CAN node 2
add_executable(csp_server_can
    csp_server_can.c
)
target_link_libraries(csp_server_can csp utils Threads::Threads)
