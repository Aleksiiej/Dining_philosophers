set(SRC_LIST
    Philosopher.cpp
    )

add_library(lib STATIC ${SRC_LIST} ${HEADER_LIST})
target_include_directories(lib PUBLIC ../include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_link_libraries(${PROJECT_NAME} PRIVATE lib)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
