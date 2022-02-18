	
cmake_minimum_required(VERSION 3.13.0)
project(tempest-atari VERSION 0.1.0)


find_package(SDL2 REQUIRED)

set(SOURCES 
  src/main.cpp 
  src/utils/Timer.cpp
  src/utils/Utils.cpp
  src/utils/Vector2D.cpp
  src/core/GameObject.cpp
  src/core/Renderer.cpp
  src/core/Entity.cpp
  src/state/Scene.cpp
  src/state/SceneManager.cpp
  src/state/TitleScreen.cpp
  src/state/SLevelSelect.cpp
)
 
add_executable(tempest ${SOURCES})

set_property(TARGET tempest PROPERTY CXX_STANDARD 20)
target_link_libraries(tempest ${SDL2_LIBRARIES})

target_compile_options(tempest PRIVATE -Wall -Wextra -Wpedantic -g ) 
