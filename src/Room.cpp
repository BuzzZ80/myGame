#include <Room.h>

Room::Room (const char *file, Player *player, SDL_Renderer *ren) {
  Json::Value roomData;
  std::ifstream ifs;
  
  ifs.open(file);

  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;

  if(!parseFromStream(builder, ifs, &roomData, &errs)) printf("JSON ERROR!");

  this->background = FileManager::loadTexture(roomData["background"].asCString(), ren);
  player->x = roomData["player"]["x"].asFloat();
  player->y = roomData["player"]["y"].asFloat();
}

void Room::render(SDL_Renderer *ren, Player *player) {
  SDL_RenderClear(ren);
  SDL_RenderCopy(ren, background, NULL, NULL);
  player->render(ren);
  SDL_RenderPresent(ren);
}
