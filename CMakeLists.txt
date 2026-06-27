# =========================
# ENGINE FRAMEWORK SOURCE LIST
# =========================
set(ENGINE_SOURCES
        # The Engine
        Src/Engine.cpp
        Includes/Engine.hpp

        # Core Systems & Utilities
        Utils/utils.hpp
        Utils/EnumSet.hpp
        Src/Time/TimeComponent.cpp
        Includes/Time/TimeComponent.hpp

        # Framework Identification & Strong IDs
        Src/Identification/Streamable.cpp
        Includes/Identification/Streamable.hpp
        Includes/Identification/StrongType.hpp
        Includes/Identification/Maps.hpp

        # Event & Input Handling
        Src/EventHandling/EventHandler.cpp
        Includes/EventHandling/EventHandler.hpp
        Src/EventHandling/InputHandler.cpp
        Includes/EventHandling/InputHandler.hpp
        Src/EventHandling/EventSubscriber.cpp
        Includes/EventHandling/EventSubscriber.hpp
        Src/EventHandling/Controls.cpp

        # Multimedia (Video & Audio Components)
        Src/Video/Camera.cpp
        Includes/Video/Camera.hpp
        Src/Video/VideoComponent.cpp
        Includes/Video/VideoComponent.hpp
        Includes/Video/TextureComponent.hpp
        Src/Audio/AudioComponent.cpp
        Includes/Audio/AudioComponent.hpp

        # Animation Engine
        Includes/Video/Animation/AnimationEngine.hpp
        Src/Video/Animation/AnimationSheet.cpp
        Includes/Video/Animation/AnimationSheet.hpp
        Includes/Video/Animation/Animation.hpp
        Includes/Video/Animation/Animatable.hpp

        # Scene Graph & Rendering
        Src/Video/SceneGraph/Composite.cpp
        Includes/Video/SceneGraph/Composite.hpp
        Src/Video/SceneGraph/Sprite.cpp
        Includes/Video/SceneGraph/Sprite.hpp
        Src/Video/SceneGraph/RectangleShape.cpp
        Includes/Video/SceneGraph/RectangleShape.hpp
        Src/Video/SceneGraph/ParallaxLayer.cpp
        Includes/Video/SceneGraph/ParallaxLayer.hpp
        Includes/Video/SceneGraph/AnimatedSprite.hpp
        Src/Video/SceneGraph/HitMap.cpp
        Includes/Video/SceneGraph/HitMap.hpp

        # Physics

        # State Machine Framework
        Src/StateMachine/StateMachine.cpp
        Src/StateMachine/States/State.cpp
        Includes/StateMachine/States/State.hpp
        Includes/StateMachine/States/Domain.hpp
        Includes/StateMachine/States/Animated.hpp
        Src/StateMachine/Cores/Core.cpp
        Includes/StateMachine/Cores/Core.hpp
        Includes/StateMachine/Cores/DynamicCore.hpp
        Includes/StateMachine/Evaluations/Evaluation.hpp
        Src/StateMachine/Evaluations/Combo.cpp
        Includes/StateMachine/Evaluations/Combo.hpp
        Src/StateMachine/Evaluations/InputDriven.cpp
        Includes/StateMachine/Evaluations/InputDriven.hpp
        Src/StateMachine/Evaluations/Conditioned.cpp
        Includes/StateMachine/Evaluations/Conditioned.hpp

        # Effect & Extension Framework
        Includes/EntityManager/Entity/Effects/Effect.hpp

        # Base Entities & Components
        Src/EntityManager/Entity/Entity.cpp
        Includes/EntityManager/Entity/Entity.hpp
        Src/EntityManager/Entity/Body/Body.cpp
        Includes/EntityManager/Entity/Body/Body.hpp
        Src/EntityManager/Entity/Body/VitalityComponent.cpp
        Includes/EntityManager/Entity/Body/VitalityComponent.hpp
        Includes/EntityManager/Entity/Body/States/Abilities.hpp
        Includes/EntityManager/Entity/Body/States/VitalityStates.hpp
        Src/EntityManager/Entity/Components/PhysicsComponent.cpp
        Includes/EntityManager/Entity/Components/PhysicsComponent.hpp
        Src/EntityManager/Entity/Components/RenderComponent.cpp
        Includes/EntityManager/Entity/Components/RenderComponent.hpp
        Src/EntityManager/Entity/Components/ColliderComponent.cpp
        Includes/EntityManager/Entity/Components/ColliderComponent.hpp

        # Base Actor & Player Concepts
        Src/StateMachine/Actor/Actor.cpp
        Includes/StateMachine/Actor/Actor.hpp
        Src/Player/Player.cpp
        Includes/Player/Player.hpp

        # NPC Content
        Src/StateMachine/NPC/NPC.cpp
        Includes/StateMachine/NPC/NPC.hpp

        # Environment Foundations
        Src/EntityManager/EntityManager.cpp
        Includes/EntityManager/EntityManager.hpp
        Includes/Scene/Scene.cpp
        Includes/Scene/Scene.hpp
        Src/Physics/PhysicalEnvironment.cpp
        Includes/Physics/PhysicalEnvironment.hpp
        Src/Physics/MotionEquation.cpp
        Includes/Physics/MotionEquation.hpp
)

# Compile as a Static Library
add_library(GameEngine STATIC ${ENGINE_SOURCES})

# MAGIC TRICK: "PUBLIC" means any target that links to GameEngine (like our GameLogic)
# will automatically inherit these include directories!
target_include_directories(GameEngine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)

target_link_libraries(GameEngine PUBLIC SFML::Graphics SFML::Audio)

# Engine Defines
if (MSVC)
    target_compile_definitions(GameEngine PUBLIC _CRT_SECURE_NO_WARNINGS)
endif ()

if (WIN32)
    target_compile_options(GameEngine PRIVATE /UUNICODE /U_UNICODE)
endif ()