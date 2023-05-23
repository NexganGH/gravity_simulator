cmake_minimum_required(VERSION 3.16)
project(gas VERSION 0.1.0 LANGUAGES CXX)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)


# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# # abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# # abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")



find_package(SFML 2.5 COMPONENTS system window graphics)
add_executable(gas main.cpp)

target_link_libraries(gas PRIVATE sfml-graphics sfml-system sfml-window)

#target_include_directories(gas PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(gas PRIVATE cxx_std_17)
install(TARGETS gas)
#add_subdirectory(SFML)


# se il testing e' abilitato...
# #   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
# if (BUILD_TESTING)

#   # aggiungi l'eseguibile statistics.t
#   add_executable(main.t main.cpp)
#   # aggiungi l'eseguibile statistics.t alla lista dei test
#   add_test(NAME main.t COMMAND main.t)

# endif()

