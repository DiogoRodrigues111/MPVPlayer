cmake_minimum_required(VERSION 3.5)

project(term LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MSYS_DIR "C:/msys64/mingw64")

include_directories( term ${MSYS_DIR}/include )
link_directories( term ${MSYS_DIR}/lib )

add_executable(term main.cpp)

target_link_libraries( term PUBLIC
    -L"${MSYS_DIR}/lib/mpv.dll.a"
    -lmpv
)

install(TARGETS term
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
