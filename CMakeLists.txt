cmake_minimum_required(VERSION 3.16)
project(gravity VERSION 0.1.0 LANGUAGES CXX)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(TGUI_BACKEND SFML_GRAPHICS)

# # abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# # abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

#including header file direcotry
include_directories(include)
# Add the source files in the src/ directory
file(GLOB_RECURSE SRC_FILES src/*.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)


#find_package(TGUI 0.10 REQUIRED)

#add_executable(gravity src/main.cpp src/body.cpp src/configuration.cpp src/configurations.cpp src/orbit_drawer.cpp src/physics_engine.cpp src/renderer.cpp src/simulation_state.cpp src/vector.cpp src/simulation_state.cpp src/gui_manager.cpp)

include_directories(include)
add_executable(gravity ${SRC_FILES})

target_link_libraries(gravity PRIVATE sfml-graphics sfml-system sfml-window tgui)
#target_link_libraries(gravity PRIVATE TGUI::TGUI)

#target_include_directories(gas PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(gravity PRIVATE cxx_std_17)
install(TARGETS gravity)
#add_subdirectory(SFML)

# se il testing e' abilitato...
# per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)
    file(GLOB_RECURSE TEST_FILES test/*.cpp)
    list(REMOVE_ITEM TEST_FILES "${CMAKE_SOURCE_DIR}/test/doctest.h")  # Exclude doctest.h from the test files

    file(GLOB_RECURSE SRC_FILES_TEST src/*.cpp)
    list(REMOVE_ITEM SRC_FILES_TEST "${CMAKE_SOURCE_DIR}/src/main.cpp")
    
    #add_executable(tests "test/body.test.cpp")
    #target_sources(tests PRIVATE ${SRC_FILES_TEST})

    foreach(TEST_FILE ${TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        add_executable(${TEST_NAME}.t ${TEST_FILE} ${SRC_FILES_TEST})
        target_link_libraries(${TEST_NAME}.t PRIVATE sfml-graphics sfml-system sfml-window tgui)
        add_test(NAME ${TEST_NAME}.t COMMAND ${TEST_NAME}.t)
    endforeach()
    #add_test(NAME tests COMMAND tests)

endif()