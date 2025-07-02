# sdk/c++/CMakeLists.txt

find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_library(config_loader config_loader.cpp)

target_include_directories(config_loader
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(config_loader
    PUBLIC                         # ✅ PUBLIC ensures it's visible to dependent targets
        yaml-cpp::yaml-cpp         # ✅ Fix deprecated warning
        nlohmann_json::nlohmann_json
)
