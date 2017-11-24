#ifndef __MATHP__
#define __MATHP__

#include "../Math/Matrix4.h"
#include <json_spirit/json_spirit.h>
#define PI 3.14159265359

Vec3 parseVec3(json_spirit::Value &value);
Color parseColor(json_spirit::Value &value);
Matrix4 parseTransform(json_spirit::Value &value);

#endif