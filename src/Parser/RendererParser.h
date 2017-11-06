#ifndef __RPARSER__
#define __RPARSER__

#include "../Vec3.h"
#include "../Transform.h"
#include <json_spirit/json_spirit.h>

class RendererParser {
protected:
	Vec3 parseVec3(json_spirit::Value &value);
  Transform parseTransform(json_spirit::Value &value);
	Object* parseObject(json_spirit::Value &value, Scene &scene);
	Camera* parseCamera(json_spirit::Value &value);
  void parseScene(json_spirit::Object &json, Renderer* r);
public:
	virtual Renderer* parse(json_spirit::Object &json) = 0;
};

#endif