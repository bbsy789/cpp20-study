include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
set(CMAKE_CXX_FLAGS_DEBUG )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Ofast -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-rtti")

add_executable(main6_1 constexpr.cpp)

target_include_directories(main6_1 PUBLIC /home/wwj/source-code/fast_io/include)

if(supported)
    message(STATUS "IPO/LTO enabled")
    set_property(TARGET main6_1 PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO/LTO not supported: <${error}>")
endif()
