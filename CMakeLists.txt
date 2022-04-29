	
cmake_minimum_required(VERSION 3.13.0)
project(tempest-atari VERSION 0.1.0)


find_package(SDL2 REQUIRED)

set(SOURCES 
      src/main.cpp 

      src/core/Game.cpp
      src/core/RenderHandler.cpp
      src/core/Band.hpp
      src/core/Band.cpp
      src/core/Map.hpp
      src/core/Map.cpp
      src/core/Data.cpp
      src/core/Data.hpp
      src/core/GameObject.cpp
      src/core/GameObject.hpp
      src/core/Blaster.cpp
      src/core/Blaster.hpp
      src/core/Flipper.cpp
      src/core/Flipper.hpp
      src/core/Bullet.cpp
      src/core/Bullet.hpp
      src/core/GameObjectPool.hpp
      src/core/SpawnManager.cpp
      src/core/SpawnManager.hpp
      src/core/Tanker.cpp
      src/core/Tanker.hpp
      src/core/Spiker.cpp
      src/core/Spiker.hpp

      src/state/SceneManager.cpp
      src/state/TitleScreen.cpp
      src/state/WinScreen.cpp
      src/state/DeathScreen.cpp
      src/state/LevelSelectionScene.cpp
      src/state/GameScene.cpp
      src/state/GameScene.hpp

      src/ui/Pen.cpp
      src/ui/ColorHandler.cpp
      src/ui/UIElement.cpp
      src/ui/UILevelCarousel.cpp
      src/ui/UILevelBox.cpp

      src/utils/Timer.hpp
      src/utils/Errors.cpp
      src/utils/Delay.hpp

      src/sdlw/SDLW.cpp)
 
add_executable(tempest ${SOURCES})

set_property(TARGET tempest PROPERTY CXX_STANDARD 20)
target_link_libraries(tempest ${SDL2_LIBRARIES})

target_compile_options(tempest PRIVATE -Wall -Wextra -Wpedantic -Wreorder -g ) 
