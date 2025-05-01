# CAN RDP node 1
add_executable(csp_can_node1_rdp
    csp_can_node1_rdp.c
)
target_link_libraries(csp_can_node1_rdp csp utils Threads::Threads)

# CAN RDP node 2
add_executable(csp_can_node2_rdp
    csp_can_node2_rdp.c
)
target_link_libraries(csp_can_node2_rdp csp utils Threads::Threads)
