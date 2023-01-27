include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)
set(CMAKE_CXX_FLAGS_DEBUG )
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Ofast -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-rtti")
add_executable(main5_3 TypeList.hpp TypeList.cpp)

target_include_directories(main5_3 PUBLIC ${CMAKE_SOURCE_DIR}/fast_io/include/)

if(supported)
    message(STATUS "IPO/LTO enabled")
    set_property(TARGET main5_3 PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO/LTO not supported: <${error}>")
endif()
