cmake_minimum_required(VERSION 3.28)
project(SFMLGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS source/*.cpp)
include_directories(include include/SFML include/states)

add_executable(main ${sources})
target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics sfml-main -mwindows)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

install(TARGETS main RUNTIME DESTINATION bin)
install(DIRECTORY assets DESTINATION .)
install(DIRECTORY fonts DESTINATION .)
install(DIRECTORY saves DESTINATION .)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "Alien Game")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "Drole")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Game Project in SFML")
set(CPACK_PACKAGE_EXECUTABLES "alien game" "Alien Game")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "AlienGame")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")

set(CPACK_SOURCE_INSTALLED_DIRECTORIES "${CMAKE_SOURCE_DIR}/source;${CMAKE_SOURCE_DIR}/include")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/CMakeLists.txt.user;/CMakeCache.txt;/cmake_install.cmake;/CPackConfig.cmake;/CPackSourceConfig.cmake;/Makefile;/CMakeFiles/")

include(CPack)