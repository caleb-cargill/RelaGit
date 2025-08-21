cmake_minimum_required(VERSION 3.14)
project(RelaGit CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Your executable
add_executable(rgit
    RelaGit.cpp
    # add more .cpp files if needed
)

# --- nlohmann_json via FetchContent ---
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

# --- CURL ---
find_package(CURL REQUIRED)

if (NOT CURL_FOUND)
    message(FATAL_ERROR "libcurl was not found. 
Please install it with vcpkg:
    vcpkg install curl:x64-windows

Then re-run CMake with:
    cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
")
endif()

# Link libraries
target_link_libraries(rgit
    PRIVATE
        nlohmann_json::nlohmann_json
        CURL::libcurl
)
