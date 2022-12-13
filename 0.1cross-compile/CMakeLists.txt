include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
add_executable(hello-world hello-world.cpp)
# we will print the system name in the code
target_compile_definitions(hello-world
PUBLIC
"SYSTEM_NAME=\"${CMAKE_SYSTEM_NAME}\""
)
install(
TARGETS
hello-world
DESTINATION
${CMAKE_INSTALL_BINDIR}
)