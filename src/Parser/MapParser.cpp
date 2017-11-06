#include "MapParser.h"
#include "../Renderer/MapRenderer.h"

Renderer* MapParser::parse(json_spirit::Object &json) {
  double maxDepth = json["MAXDEPTH"].getReal();
  Color fg = parseVec3(json["FGCOLOR"]);
  Color bg = parseVec3(json["BGCOLOR"]);
  MapRenderer* renderer = new MapRenderer(fg, bg, maxDepth);
  parseInfo(renderer);
  return renderer;
}