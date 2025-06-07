cmake_minimum_required(VERSION 3.16)
project(logseq-rm)

find_package(Qt6 REQUIRED COMPONENTS Quick)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/out)

add_subdirectory(src)
install(TARGETS logseq_rm DESTINATION bin)
