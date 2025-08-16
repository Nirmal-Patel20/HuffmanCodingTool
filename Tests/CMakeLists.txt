# Bring in Catch2 from our cmake/ folder
include(${CMAKE_SOURCE_DIR}/cmake/FetchCatch2.cmake)

# ---- Create test executable ----
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(HuffmanTests ${TEST_SOURCES})

# Link with Catch2 and your project
target_link_libraries(HuffmanTests PRIVATE Catch2::Catch2WithMain)

# Include headers
target_include_directories(HuffmanTests PRIVATE ../include)

# ---- Enable CTest integration ----
include(Catch)
catch_discover_tests(HuffmanTests)