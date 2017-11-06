#include "DefaultParser.h"

void DefaultParser::parseScene(json_spirit::Object &json, DefaultRenderer* r) {
  if (json.count("BACKGROUND")) {
    json_spirit::Object bg = json["BACKGROUND"].getObject();
    r->tl = parseColor(bg["UPPER_LEFT"]);
    r->tr = parseColor(bg["UPPER_RIGHT"]);
    r->bl = parseColor(bg["LOWER_LEFT"]);
    r->br = parseColor(bg["LOWER_RIGHT"]);
  }
  if (json.count("LIGHTS")) {
    json_spirit::Array lights = json["LIGHTS"].getArray();
    for (int i = 0; i < lights.size(); i++) {
      r->lights.push_back(parseLight(light[i]));
    }
  }
  parseInfo(json, renderer);
}