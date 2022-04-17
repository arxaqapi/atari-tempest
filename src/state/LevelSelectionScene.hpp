
#ifndef H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_
#define H_TEMPEST_GAME_INC_SCENE_LEVEL_SELECT_

#include "../ui/UILevelBox.hpp"
#include "Scene.hpp"
#include <filesystem>

class SceneManager;

class LevelSelectionScene : public Scene
{
private:
  std::vector<std::filesystem::path> available_levels_;
  std::vector<UILevelBox> ui_elements_;
  int selected_level_ = 0;

public:
  LevelSelectionScene();
  ~LevelSelectionScene();

  void processEvent(SDL_Event* event, SceneManager& sm) override;
  void update(f64 delta, SceneManager& sm) override;
  void render(SDL_Renderer* renderer) const override;
};

#endif