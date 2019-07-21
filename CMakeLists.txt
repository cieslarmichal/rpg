cmake_minimum_required( VERSION 3.14 )
set( PROJECT_NAME rpg  )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )

set(SFML_INCLUDE_DIR "./SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "./SFML-2.5.1/lib")
set(SFML_DIR "./SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Main.cpp
    ${CMAKE_SOURCE_DIR}/src/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/Animation.cpp
    ${CMAKE_SOURCE_DIR}/src/Blocked.cpp
    ${CMAKE_SOURCE_DIR}/src/Character.cpp
    ${CMAKE_SOURCE_DIR}/src/CollisionHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/Create.cpp
    ${CMAKE_SOURCE_DIR}/src/Delete.cpp
    ${CMAKE_SOURCE_DIR}/src/Dialogues.cpp
    ${CMAKE_SOURCE_DIR}/src/Dragon.cpp
    ${CMAKE_SOURCE_DIR}/src/Draw.cpp
    ${CMAKE_SOURCE_DIR}/src/Enemy.cpp
    ${CMAKE_SOURCE_DIR}/src/EnemySpawner.cpp
    ${CMAKE_SOURCE_DIR}/src/Fight.cpp
    ${CMAKE_SOURCE_DIR}/src/File.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/HUD.cpp
    ${CMAKE_SOURCE_DIR}/src/Input.cpp
    ${CMAKE_SOURCE_DIR}/src/Interaction.cpp
    ${CMAKE_SOURCE_DIR}/src/Inventory.cpp
    ${CMAKE_SOURCE_DIR}/src/Item.cpp
    ${CMAKE_SOURCE_DIR}/src/ItemFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/LevelManager.cpp
    ${CMAKE_SOURCE_DIR}/src/Map.cpp
    ${CMAKE_SOURCE_DIR}/src/Mark.cpp
    ${CMAKE_SOURCE_DIR}/src/Menu.cpp
    ${CMAKE_SOURCE_DIR}/src/Mission.cpp
    ${CMAKE_SOURCE_DIR}/src/Missions.cpp
    ${CMAKE_SOURCE_DIR}/src/Movement.cpp
    ${CMAKE_SOURCE_DIR}/src/Node.cpp
    ${CMAKE_SOURCE_DIR}/src/Npc.cpp
    ${CMAKE_SOURCE_DIR}/src/Obstacle.cpp
    ${CMAKE_SOURCE_DIR}/src/PathFinding.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/Projectile.cpp
    ${CMAKE_SOURCE_DIR}/src/Random.cpp
    ${CMAKE_SOURCE_DIR}/src/Rect.cpp
    ${CMAKE_SOURCE_DIR}/src/Shoot.cpp
    ${CMAKE_SOURCE_DIR}/src/Skeleton.cpp
    ${CMAKE_SOURCE_DIR}/src/SkeletonBerserker.cpp
    ${CMAKE_SOURCE_DIR}/src/Sprite.cpp
    ${CMAKE_SOURCE_DIR}/src/StatusBar.cpp
    ${CMAKE_SOURCE_DIR}/src/Text.cpp
    ${CMAKE_SOURCE_DIR}/src/Tile.cpp
    ${CMAKE_SOURCE_DIR}/src/TimeHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/Update.cpp
    ${CMAKE_SOURCE_DIR}/src/Wrapper.cpp
        )

add_executable( ${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "./include" SFML_INCLUDE_DIR)

target_link_directories(${PROJECT_NAME} PUBLIC SFML_LIBRARY_DIR)

target_link_libraries ( ${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)
