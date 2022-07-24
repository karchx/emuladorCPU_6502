cmake_minimum_required(VERSION 3.14)
project(6502)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set (M6502_SOURCES
	"src/main_6502.cpp"
	"src/6502Test.cpp")

source_group("src" FILES ${M6502_SOURCES}	)

add_executable(M6502Test ${M6502_SOURCES}	)
target_link_libraries(
  M6502Test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(M6502Test)
