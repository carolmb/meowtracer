#ifndef __PMODEL__
#define __PMODEL__

#include "MathParser.h"
#include "../Scene.h"
#include "../Object/Object.h"
#include "../Object/Material.h"

void parseModel(json_spirit::Object &json, Matrix4 &xform, Scene &scene);

#endif