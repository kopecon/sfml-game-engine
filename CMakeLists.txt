cmake_minimum_required(VERSION 3.28)
project(bonk_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable("${CMAKE_PROJECT_NAME}" Src/main.cpp
        Src/Entity/Player/Player.cpp
        Includes/Entity/Player/Player.hpp
        Src/Entity/Scenery/Background.cpp
        Includes/Entity/Scenery/Background.hpp
        Src/Game/Camera.cpp
        Includes/Game/Camera.hpp
        Src/Game/Engines/AnimationEngine.cpp
        Includes/Game/Engines/AnimationEngine.hpp
        Src/Entity/Player/PhysicsComponent.cpp
        Includes/Entity/Player/PhysicsComponent.hpp
        Src/Entity/Player/InputComponent.cpp
        Includes/Entity/Player/InputComponent.hpp
        Utils/utils.cpp
        Utils/utils.hpp
        Src/World/World.cpp
        Includes/World/World.hpp
        Src/Entity/Entity.cpp
        Includes/Entity/Entity.hpp
        Src/Entity/Scenery/Ground.cpp
        Includes/Entity/Scenery/Ground.hpp
        Src/Game/Game.cpp
        Includes/Game/Game.hpp
        Src/Game/VideoComponent.cpp
        Includes/Game/VideoComponent.hpp
        Src/Game/AudioComponent.cpp
        Includes/Game/AudioComponent.hpp
        Src/Entity/Scenery/Scenery.cpp
        Includes/Entity/Scenery/Scenery.hpp
        Src/Game/TimeComponent.cpp
        Includes/Game/TimeComponent.hpp
        Src/Game/TextureComponent.cpp
        Includes/Game/TextureComponent.hpp
        Src/Game/Engines/PhysicsEngine.cpp
        Includes/Game/Engines/PhysicsEngine.hpp
        Src/Entity/Player/AnimationManager.cpp
        Includes/Entity/Player/AnimationManager.hpp
        Src/Entity/Player/MovementComponent.cpp
        Includes/Entity/Player/MovementComponent.hpp
        Src/Entity/Player/CombatComponent.cpp
        Includes/Entity/Player/CombatComponent.hpp
        Src/Entity/Player/StateManager.cpp
        Includes/Entity/Player/StateManager.hpp
        Src/Entity/Player/States/Idle.cpp
        Includes/Entity/Player/States/Idle.hpp
        Src/Entity/Player/States/Walking.cpp
        Includes/Entity/Player/States/Walking.hpp
        Src/Entity/Player/States/Jumping.cpp
        Includes/Entity/Player/States/Jumping.hpp
        Src/Entity/Player/States/Running.cpp
        Includes/Entity/Player/States/Running.hpp
        Src/Entity/Player/States/Stopping.cpp
        Includes/Entity/Player/States/Stopping.hpp
        Src/Game/Engines/StateMachineEngine.cpp
        Includes/Game/Engines/StateMachineEngine.hpp
)

if (PRODUCTION_BUILD)
    # setup the ASSETS_PATH macro to be in the root folder of your exe
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./Resources/")

    # remove the option to debug asserts.
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEVELOPMENT_BUILD=0)

else ()
    # This is useful to get an ASSETS_PATH in your IDE during development
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEVELOPMENT_BUILD=1)

endif ()

if (MSVC) # If using the VS compiler...

    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

    # set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console

endif ()

#force remove unicode
if (WIN32)
    target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE /UUNICODE /U_UNICODE)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Main)
endif ()

target_compile_features("${CMAKE_PROJECT_NAME}" PRIVATE cxx_std_23)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Graphics)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Audio)
