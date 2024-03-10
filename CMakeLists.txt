cmake_minimum_required(VERSION 3.0.0)
project(tier VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OBJS
    sqlite3/sqlite3.o
)

add_executable(tier tier.cpp printtl.cpp ${OBJS})

set_source_files_properties(
    ${OBJS}
    PROPERTIES
    EXTERNAL_OBJECT true
    GENERATED true
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)