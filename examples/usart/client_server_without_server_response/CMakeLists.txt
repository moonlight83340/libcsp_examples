# CAN node 1
add_executable(csp_client_usart
    csp_client_usart.c
)
target_link_libraries(csp_client_usart csp utils Threads::Threads)

# CAN node 2
add_executable(csp_server_usart
    csp_server_usart.c
)
target_link_libraries(csp_server_usart csp utils Threads::Threads)
