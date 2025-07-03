add_executable(ipc_daemon main.cpp)
target_link_libraries(ipc_daemon PRIVATE Threads::Threads)
