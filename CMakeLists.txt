cmake_minimum_required(VERSION 3.14)
project(RelaGit CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Your executable
add_executable(RelaGit
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
target_link_libraries(RelaGit PRIVATE nlohmann_json::nlohmann_json)

# --- libcurl setup ---
set(CURL_DLL "C:/dev/curl/bin/libcurl-x64.dll") 
set(CURL_INCLUDE_DIR "C:/dev/curl/include")
set(CURL_LIB "C:/dev/curl/lib/libcurl.a") 

target_include_directories(RelaGit PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(RelaGit PRIVATE ${CURL_LIB})

# Copy libcurl DLL next to the executable after build
add_custom_command(TARGET RelaGit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CURL_DLL}
        $<TARGET_FILE_DIR:RelaGit>)
