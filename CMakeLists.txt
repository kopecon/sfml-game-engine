cmake_minimum_required(VERSION 3.28)
project(bonk_game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if (PRODUCTION_BUILD)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization
else ()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
endif ()

if (MSVC)
    add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif ()


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable("${CMAKE_PROJECT_NAME}" src/main.cpp
        src/Player.cpp
        Includes/Player.hpp
        src/background.cpp
        Includes/background.hpp
        src/Camera.cpp
        Includes/Camera.hpp
        src/AnimationComponent.cpp
        Includes/AnimationComponent.hpp
        src/PhysicsComponent.cpp
        Includes/PhysicsComponent.hpp
        src/InputComponent.cpp
        Includes/InputComponent.hpp
        utils/utils.cpp
        Includes/utils.hpp
        src/World.cpp
        Includes/World.hpp
        Src/Entity.cpp
        Includes/Entity.hpp
        Src/Ground.cpp
        Includes/Ground.hpp
        Src/Game.cpp
        Includes/Game.hpp
        Src/VideoComponent.cpp
        Includes/VideoComponent.hpp
        Src/AudioComponent.cpp
        Includes/AudioComponent.hpp
        Src/Scenery.cpp
        Includes/Scenery.hpp
        Src/TimeComponent.cpp
        Includes/TimeComponent.hpp
)

if (PRODUCTION_BUILD)
    # setup the ASSETS_PATH macro to be in the root folder of your exe
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./Resources/")

    # remove the option to debug asserts.
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEVELOPLEMT_BUILD=0)

else ()
    # This is useful to get an ASSETS_PATH in your IDE during development
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEVELOPLEMT_BUILD=1)

endif ()

if (MSVC) # If using the VS compiler...

    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

    # set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console

endif ()

#force remove unicode
if (WIN32)
    target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE /UUNICODE /U_UNICODE)
endif ()

target_compile_features("${CMAKE_PROJECT_NAME}" PRIVATE cxx_std_23)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Graphics)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Main)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Audio)
