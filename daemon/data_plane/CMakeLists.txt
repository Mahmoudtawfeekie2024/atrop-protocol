add_executable(data_plane_daemon main.cpp)
target_link_libraries(data_plane_daemon PRIVATE Threads::Threads spdlog::spdlog)
