
#ifndef H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_
#define H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_

#include "Scene.hpp"

class LevelSelectionScene : public Scene
{
private:
public:
  LevelSelectionScene();
  ~LevelSelectionScene();

  void processEvent(SDL_Event event) override;
  void update(f64 delta) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif