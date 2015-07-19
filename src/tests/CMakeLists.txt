

add_executable(tests ConsoleAppTest.cpp SevenSegmentDisplayTest.cpp TestMetaProgramming.cpp TestMyVector.cpp stdafx.cpp targetver.h)

include_directories ("${PROJECT_SOURCE_DIR}/library" "${PROJECT_SOURCE_DIR}/../include")
target_link_libraries(tests library "${PROJECT_SOURCE_DIR}/../libraries/gtestd.lib")
