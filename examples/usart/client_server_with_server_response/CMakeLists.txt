# USART node 1
add_executable(csp_usart_node1
    csp_usart_node1.c
)
target_link_libraries(csp_usart_node1 csp utils Threads::Threads)

# USART node 2
add_executable(csp_usart_node2
    csp_usart_node2.c
)
target_link_libraries(csp_usart_node2 csp utils Threads::Threads)
