
#ifndef H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_
#define H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_

#include "../ui/UILevelBox.hpp"
#include "../ui/UILevelCarousel.hpp"
#include "Scene.hpp"
#include <filesystem>

class SceneManager;

class LevelSelectionScene : public Scene
{
private:
  UILevelCarousel ui_level_carousel_;

public:
  LevelSelectionScene();
  ~LevelSelectionScene();

  void processEvent(SDL_Event* event, SceneManager& sm) override;
  void update(f64 delta, SceneManager& sm) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif