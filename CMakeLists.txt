cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://gitee.com/mirrors_laurentgomila/sfml.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# 添加所有源文件
add_executable(main 
    main.cpp
    Game.cpp
    Fruit.cpp
    GameOverScreen.cpp
    GameScreen.cpp
    MenuScreen.cpp
    SettingsScreen.cpp
    SucceedScreen.cpp
    Screen.cpp
    Snake.cpp
    SnakeNode.cpp
    SnakeHead.cpp
)

target_link_libraries(main PRIVATE sfml-graphics sfml-audio)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)

    set_target_properties(main PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
