cmake_minimum_required(VERSION 3.28)
project(sfml_game_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
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
        Src/Game/World/Entity/Player/Player.cpp
        Includes/Game/World/Entity/Player/Player.hpp
        Src/Game/World/Entity/Scenery/Background.cpp
        Includes/Game/World/Entity/Scenery/Background.hpp
        Src/Game/Components/Video/Camera.cpp
        Includes/Game/Components/Video/Camera.hpp
        Includes/Game/Engines/AnimationEngine/AnimationEngine.hpp
        Src/Game/World/Entity/Player/Components/PhysicsComponent.cpp
        Includes/Game/World/Entity/Player/Components/PhysicsComponent.hpp
        Src/Game/World/Entity/Player/Components/Input/InputComponent.cpp
        Includes/Game/World/Entity/Player/Components/Input/InputComponent.hpp
        Includes/Utils/utils.hpp
        Src/Game/World/World.cpp
        Includes/Game/World/World.hpp
        Src/Game/World/Entity/Entity.cpp
        Includes/Game/World/Entity/Entity.hpp
        Src/Game/World/Entity/Scenery/Ground.cpp
        Includes/Game/World/Entity/Scenery/Ground.hpp
        Src/Game/Game.cpp
        Includes/Game/Game.hpp
        Src/Game/Components/Video/VideoComponent.cpp
        Includes/Game/Components/Video/VideoComponent.hpp
        Src/Game/Components/Audio/AudioComponent.cpp
        Includes/Game/Components/Audio/AudioComponent.hpp
        Src/Game/Components/Time/TimeComponent.cpp
        Includes/Game/Components/Time/TimeComponent.hpp
        Includes/Game/Components/Video/TextureComponent.hpp
        Src/Game/Engines/PhysicsEngine.cpp
        Includes/Game/Engines/PhysicsEngine.hpp
        Src/Game/World/Entity/Player/Components/Movement/MovementComponent.cpp
        Includes/Game/World/Entity/Player/Components/Movement/MovementComponent.hpp
        Src/Game/World/Entity/Player/Components/Combat/CombatComponent.cpp
        Includes/Game/World/Entity/Player/Components/Combat/CombatComponent.hpp
        Includes/Game/Engines/StateMachine/State.hpp
        Includes/Game/World/Entity/Player/Components/States/StateSet.hpp
        Includes/Utils/EnumSet.hpp
        Includes/Game/World/Entity/Player/Components/States/PlayerState.hpp
        Src/Game/World/Entity/Player/Components/States/StateManager.cpp
        Includes/Game/World/Entity/Player/Components/States/StateManager.hpp
        Src/Game/World/Entity/Player/Components/States/Idle.cpp
        Includes/Game/World/Entity/Player/Components/States/Idle.hpp
        Src/Game/World/Entity/Player/Components/States/Walking.cpp
        Includes/Game/World/Entity/Player/Components/States/Walking.hpp
        Src/Game/World/Entity/Player/Components/States/Jumping.cpp
        Includes/Game/World/Entity/Player/Components/States/Jumping.hpp
        Src/Game/World/Entity/Player/Components/States/Running.cpp
        Includes/Game/World/Entity/Player/Components/States/Running.hpp
        Src/Game/World/Entity/Player/Components/States/Stopping.cpp
        Includes/Game/World/Entity/Player/Components/States/Stopping.hpp
        Src/Game/World/Entity/Player/Components/States/Attacking.cpp
        Includes/Game/World/Entity/Player/Components/States/Attacking.hpp
        Src/Game/World/Entity/Player/Components/States/Winking.cpp
        Includes/Game/World/Entity/Player/Components/States/Winking.hpp
        Includes/Game/World/Entity/Player/Components/States/Concentrating.hpp
        Src/Game/World/Entity/Player/Components/States/Concentrating.cpp
        Src/Game/Engines/SceneGraph/Render.cpp
        Includes/Game/Engines/SceneGraph/Render.hpp
        Src/Game/World/Entity/Player/Components/Render/RenderManager.cpp
        Includes/Game/World/Entity/Player/Components/Render/RenderManager.hpp
        Src/Game/Engines/SceneGraph/Composite.cpp
        Includes/Game/Engines/SceneGraph/Composite.hpp
        Src/Game/Engines/AnimationEngine/AnimationSheet.cpp
        Includes/Game/Engines/AnimationEngine/AnimationSheet.hpp
        Includes/Game/Engines/AnimationEngine/Animation.hpp
        Includes/Game/Engines/SceneGraph/AnimatedSprite.hpp
        Includes/Game/Engines/AnimationEngine/Animatable.hpp
        Src/Game/World/Entity/Player/Components/Render/PlayerSprite.cpp
        Includes/Game/World/Entity/Player/Components/Render/PlayerSprite.hpp
        Src/Game/Engines/SceneGraph/Sprite.cpp
        Includes/Game/Engines/SceneGraph/Sprite.hpp
        Includes/Game/Engines/SceneGraph/Colorable.hpp
        Src/Game/Engines/SceneGraph/RectangleShape.cpp
        Includes/Game/Engines/SceneGraph/RectangleShape.hpp
        Src/Game/Engines/EventHandling/EventHandler.cpp
        Includes/Game/Engines/EventHandling/EventHandler.hpp
        Includes/Utils/customTypes.hpp
        Src/Game/Engines/EventHandling/InputHandler.cpp
        Includes/Game/Engines/EventHandling/InputHandler.hpp
        Includes/Game/Engines/EventHandling/EventSubscriber.hpp
        Src/Game/Engines/EventHandling/EventSubscriber.cpp
        Src/Game/World/Entity/Player/Components/States/Braking.cpp
        Includes/Game/World/Entity/Player/Components/States/Braking.hpp
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

#target_compile_features("${CMAKE_PROJECT_NAME}" PRIVATE cxx_std_23)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Graphics)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE SFML::Audio)

target_include_directories("${CMAKE_PROJECT_NAME}"
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes
)