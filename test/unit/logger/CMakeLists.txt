add_executable(logger_test
  ${CMAKE_SOURCE_DIR}/test/unit/logger/test_logger.cpp
  ${CMAKE_SOURCE_DIR}/daemon/common/logger.cpp
)

target_include_directories(logger_test PRIVATE
  ${CMAKE_SOURCE_DIR}/daemon/common
)

target_link_libraries(logger_test
  PRIVATE GTest::gtest_main spdlog fmt
)


add_test(NAME cpp_logger_test COMMAND logger_test)
