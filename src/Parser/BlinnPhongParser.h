#ifndef __BPPARSER_
#define __BPPARSER_

#include "DefaultParser.h"
#include "BlinnPhongRenderer.h"

class BlinnPhongParser : DefaultParser {
protected:
  BPMaterial parseMaterial(json_spirit::Value &value);
public:
  Renderer* parse(json_spirit::Object &json);
};

#endif