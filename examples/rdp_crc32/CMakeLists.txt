# CAN RCP CRC32 node 1
add_executable(csp_can_node1_rdp_crc32
    csp_can_node1_rdp_crc32.c
)
target_link_libraries(csp_can_node1_rdp_crc32 csp utils Threads::Threads)

# CAN RCP CRC32 node 2
add_executable(csp_can_node2_rdp_crc32
    csp_can_node2_rdp_crc32.c
)
target_link_libraries(csp_can_node2_rdp_crc32 csp utils Threads::Threads)
