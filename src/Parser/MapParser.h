#ifndef __MPARSER_
#define __MPARSER_

#include "RendererParser.h"

class MapParser : RendererParser {
public:
  Renderer* parse(json_spirit::Object &json);
};

#endif