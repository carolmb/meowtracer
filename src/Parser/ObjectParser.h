#ifndef __POBJECT__
#define __POBJECT__

#include "MathParser.h"
#include "../Scene.h"
#include "../Object/Object.h"
#include "../Object/Material.h"

Object* parseObject(json_spirit::Object &json, Matrix4 &xform, std::string &type, Scene &scene);
Material* parseMaterial(json_spirit::Value &value);

#endif