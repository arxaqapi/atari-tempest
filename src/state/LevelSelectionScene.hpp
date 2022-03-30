
#ifndef H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_
#define H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_

#include "Scene.hpp"

class SceneManager;

class LevelSelectionScene : public Scene
{
private:
public:
  LevelSelectionScene();
  ~LevelSelectionScene();

  void processEvent(SDL_Event event, SceneManager const &sm) override;
  void update(f64 delta, SceneManager const &sm) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif