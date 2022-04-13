	
cmake_minimum_required(VERSION 3.13.0)
project(tempest-atari VERSION 0.1.0)


find_package(SDL2 REQUIRED)

set(SOURCES 
  src/main.cpp 
  src/utils/Timer.cpp
  src/utils/Utils.cpp
  src/utils/Vector2D.cpp
        src/core/Game.cpp
  src/core/Renderer.cpp
        src/state/SceneManager.cpp
  src/state/TitleScreen.cpp
        src/state/LevelSelectionScene.cpp
        src/core/Band.hpp src/core/Band.cpp src/core/Map.hpp src/core/Map.cpp src/state/GameScene.cpp src/state/GameScene.hpp src/core/Data.cpp src/core/Data.hpp src/core/GameObject.cpp src/core/GameObject.hpp src/core/Blaster.cpp src/core/Blaster.hpp src/core/Flipper.cpp src/core/Flipper.hpp src/core/Bullet.cpp src/core/Bullet.hpp src/core/GameObjectPool.hpp src/core/SpawnManager.cpp src/core/SpawnManager.hpp src/utils/Delay.hpp src/core/LevelData.cpp src/core/LevelData.hpp)
 
add_executable(tempest ${SOURCES})

set_property(TARGET tempest PROPERTY CXX_STANDARD 20)
target_link_libraries(tempest ${SDL2_LIBRARIES})

target_compile_options(tempest PRIVATE -Wall -Wextra -Wpedantic -g ) 
