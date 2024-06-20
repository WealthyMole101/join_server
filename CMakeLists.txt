cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

find_package(Boost)
find_package(SQLite3)
find_package(SQLite3 REQUIRED /usr/local/lib/libsqlite3.so)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -lsqlite3")
set(BOOST_INCLUDE_LIBRARIES asio)

add_executable(join_server main.cpp server.h server.cpp analyzer.h analyzer.cpp database.h database.cpp)
target_link_libraries (join_server ${SQLITE3_LIBRARIES})

include_directories(/usr/include)
include_directories(/usr/local/lib)
include_directories(${SQLite3_INCLUDE_DIRS})

if (MSVC)
    target_compile_options(join_server PRIVATE
        /W4
    )
else ()
    target_compile_options(join_server PRIVATE
        #-Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT vbespalov@astralinux.ru)

include(CPack)
