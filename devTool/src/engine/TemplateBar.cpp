#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "json.hpp"
#include "TemplateBar.h"

#include <string>

using namespace std;
using json = nlohmann::json;

TemplateBar::TemplateBar() : DisplayObjectContainer() {
  this->id = "templateBar";

  this->alpha = 100;
	this->width = 1500;
	this->height = 200;
	this->position.x = 0;
	this->position.y = 500;
}

TemplateBar::TemplateBar(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
  this->id = "templateBar";

  this->alpha = 100;
	this->width = 1500;
	this->height = 200;
	this->position.x = 0;
	this->position.y = 500;
}

TemplateBar::~TemplateBar() {

}

void TemplateBar::loadTemplateBar() {
  std::ifstream i("./resources/templates/templates.json");
	json templates = json::parse(i);
	int offset = 20;
	for (auto templ : templates["templates"]){
		std::ifstream t(templ["path"]);
		json spriteTemplate = json::parse(t);
		if (spriteTemplate["isStatic"]){
			Sprite* s = new Sprite( spriteTemplate["id"], spriteTemplate["basePathFolder"].get<std::string>() + spriteTemplate["isStaticBaseFile"].get<std::string>());
			s->id = spriteTemplate["id"];
			s->imgPath = spriteTemplate["basePathFolder"].get<std::string>() + spriteTemplate["isStaticBaseFile"].get<std::string>();
			s->position.x = spriteTemplate["posX"].get<int>() + offset;
			s->position.y = spriteTemplate["posY"].get<int>() + 60;
			s->pivot.x = spriteTemplate["pivotX"];
			s->pivot.y = spriteTemplate["pivotY"];
			s->alpha = spriteTemplate["alpha"];
			s->visible = spriteTemplate["isVisible"];
			s->rotation = spriteTemplate["rotation"];
			s->width = spriteTemplate["width"];
			s->height = spriteTemplate["height"];
			offset += 20 + s->width;
			this->addChild(s);
		} else {
			AnimatedSprite* a = new AnimatedSprite(spriteTemplate["id"]);
			for (auto animation : spriteTemplate["animationInfo"]["animations"]){
				a->addAnimation(spriteTemplate["basePathFolder"], animation["animId"], animation["frameCount"], animation["frameRate"], animation["loop"]);
				a->play(animation["animId"]);
			}

			a->imgPath = spriteTemplate["basePathFolder"];
			a->position.x = spriteTemplate["posX"].get<int>() + offset;
			a->position.y = spriteTemplate["posY"].get<int>() + 60;
			a->pivot.x = spriteTemplate["pivotX"];
			a->pivot.y = spriteTemplate["pivotY"];
			a->alpha = spriteTemplate["alpha"];
			a->visible = spriteTemplate["isVisible"];
			a->rotation = spriteTemplate["rotation"];
			a->width = spriteTemplate["width"];
			a->height = spriteTemplate["height"];
			offset += 20 + a->width;
			this->addChild(a);
		}
	}

	this->width = offset + 100;
}
