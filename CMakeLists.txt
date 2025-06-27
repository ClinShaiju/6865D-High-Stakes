include_directories("${PROJECT_SOURCE_DIR}/include/" "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.41.34120/include")
add_subdirectory(src)
add_executable(${EXECUTABLE_NAME} main.cpp ${SOURCE})