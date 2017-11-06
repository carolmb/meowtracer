#ifndef __DPARSER_
#define __DPARSER_

#include "RendererParser.h"

class DefaultParser : RendererParser {
protected:
 void parseScene(json_spirit::Object &json, DefaultRenderer* r);
};

#endif