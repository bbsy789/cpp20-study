include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
set(CMAKE_CXX_FLAGS_DEBUG )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Ofast -fno-exceptions -fno-winds-tables -fno-asynchronous-wind-tables -fno-rtti")
add_executable(main2_1 main.cpp)

target_include_directories(main2_1 PUBLIC /home/wwj/source-code/fast_io/include/)
if(supported)
    message(STATUS "IPO/LTO enabled")
    set_property(TARGET main2_1 PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO/LTO not supported: <${error}>")
endif()

