#ifndef __PSCENE_
#define __PSCENE_

#include "MathParser.h"
#include "../Scene.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"
#include "../Light/Light.h"

void parseLight(Scene &scene, json_spirit::Value &value);
Camera* parseCamera(json_spirit::Value &value);
Renderer* parseRenderer(json_spirit::Value &value);

#endif