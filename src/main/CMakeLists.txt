add_executable(main ConsoleApp.cpp stdafx.cpp targetver.h)

target_link_libraries(main library)

include_directories ("${PROJECT_SOURCE_DIR}/library")