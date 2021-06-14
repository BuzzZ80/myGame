#include <Room.h>

Room::Room (Environment *env, const char *file, Player *player) {
  this->env = env;

  Json::Value roomData;
  std::ifstream ifs;

  ifs.open(FileManager::toAbsolute(file));

  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;

  if(!parseFromStream(builder, ifs, &roomData, &errs)) printf("JSON ERROR!");

  SDL_SetRenderDrawColor(this->env->window->renderer, 
      roomData["defaultColor"][0].asUInt(), 
      roomData["defaultColor"][1].asUInt(), 
      roomData["defaultColor"][2].asUInt(),
      roomData["defaultColor"][3].asUInt());

  this->background = FileManager::loadTexture(roomData["background"].asCString(), this->env->window->renderer);
  
  player->spritesheet = FileManager::loadTexture(roomData["player"]["image"].asCString(), this->env->window->renderer);
  
  player->x = roomData["player"]["x"].asFloat();
  player->y = roomData["player"]["y"].asFloat();
  player->w = roomData["player"]["w"].asUInt();
  player->h = roomData["player"]["h"].asUInt();

  player->tw = roomData["player"]["tw"].asUInt();
  player->th = roomData["player"]["th"].asUInt();

  player->xVelocity = roomData["player"]["yv"].asFloat();
  player->yVelocity = roomData["player"]["yv"].asFloat();

  player->xVelocity = roomData["player"]["xv"].asFloat();
  player->yVelocity = roomData["player"]["yv"].asFloat();

  player->xAcceleration = roomData["player"]["xa"].asFloat();
  player->yAcceleration = roomData["player"]["ya"].asFloat();

  player->xTerminal = roomData["player"]["xt"].asFloat();
  player->yTerminal = roomData["player"]["yt"].asFloat();

  player->movementSpeed = roomData["player"]["ms"].asFloat();
  player->jumpSpeed = roomData["player"]["js"].asFloat();

  player->solid = true;

  player->setSprite(0,0);

  static SDL_Texture *platformTextures[4];
  int len = roomData["platformImages"].size();
  for (int i = 0; i < len; i++) {
    platformTextures[i] = FileManager::loadTexture(roomData["platformImages"][i].asCString(), this->env->window->renderer);
  }

  int i;
  for (i = 0; i < 16; i++) {
    if (not roomData["platforms"][i].isMember("texture")) break;
    this->platforms[i] = new Entity(this->env);

    this->platforms[i]->spritesheet = platformTextures[roomData["platforms"][i]["texture"].asUInt()];

    this->platforms[i]->x = roomData["platforms"][i]["x"].asFloat();
    this->platforms[i]->y = roomData["platforms"][i]["y"].asFloat();
    this->platforms[i]->w = roomData["platforms"][i]["w"].asUInt();
    this->platforms[i]->h = roomData["platforms"][i]["h"].asUInt();

    this->platforms[i]->tw = roomData["platforms"][i]["tw"].asUInt();
    this->platforms[i]->th = roomData["platforms"][i]["th"].asUInt();

    this->platforms[i]->xVelocity = roomData["platforms"][i]["xv"].asFloat();
    this->platforms[i]->yVelocity = roomData["platforms"][i]["yv"].asFloat();

    this->platforms[i]->xAcceleration = roomData["platforms"][i]["xa"].asFloat();
    this->platforms[i]->yAcceleration = roomData["platforms"][i]["ya"].asFloat();

    this->platforms[i]->xTerminal = roomData["platforms"][i]["xt"].asFloat();
    this->platforms[i]->yTerminal = roomData["platforms"][i]["yt"].asFloat();

    this->platforms[i]->solid = true;

    this->platforms[i]->setSprite(0,0);
  }
  if (i < 15) this->platforms[i + 1] = NULL;
}

void Room::update(Player *player) {
  for (int i = 0; i < 16; i++) {
    if (this->platforms[i] == NULL) break;
    this->platforms[i]->update();
  }
  player->update();

  for (int i = 0; i < 16; i++) {
    if (this->platforms[i] == NULL) break;
    player->collide(this->platforms[i]);
  }
  player->lastX = player->x;
  player->lastY = player->y;
}

void Room::render(Player *player) {
  SDL_RenderClear(this->env->window->renderer);
  SDL_RenderCopy(this->env->window->renderer, background, NULL, NULL);
  player->render();
  for (int i = 0; i < 16; i++) {
    if (this->platforms[i] == NULL) break;
    this->platforms[i]->render();
  }
  SDL_RenderPresent(this->env->window->renderer);
}
