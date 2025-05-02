# CAN node 1
add_executable(csp_can_node1
    csp_can_node1.c
)
target_link_libraries(csp_can_node1 csp utils Threads::Threads)

# CAN node 2
add_executable(csp_can_node2
    csp_can_node2.c
)
target_link_libraries(csp_can_node2 csp utils Threads::Threads)
