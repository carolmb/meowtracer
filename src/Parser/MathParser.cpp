#include "MathParser.h"

Color parseColor(json_spirit::Value &value) {
  json_spirit::Array json = value.getArray();
  float r = json[0].getReal();
  float g = json[1].getReal();
  float b = json[2].getReal();
  return Color(r, g, b);
}

Vec3 parseVec3(json_spirit::Value &value) {
  json_spirit::Array arr = value.getArray();
  float x = arr[0].getReal();
  float y = arr[1].getReal();
  float z = arr[2].getReal();
  return Vec3(x, y, z);
}

Matrix4 parseTransform(json_spirit::Value &value) {
  json_spirit::Array arr = value.getArray();
  Matrix4 transform = Matrix4::Identity();
  for (int i = 0; i < arr.size(); i++) {
    json_spirit::Object json = arr[i].getObject();
    if (json.count("TRANSLATION")) {
      Vec3 v = parseVec3(json["TRANSLATION"]);
      Matrix4 t = Matrix4::Translation(v);
      transform = transform * t;
    } else if (json.count("SCALE")) {
      Vec3 v = parseVec3(json["SCALE"]);
      Matrix4 t = Matrix4::Scaling(v);
      transform = transform * t;
    } else if (json.count("ROTATION")) {
      Vec3 v = parseVec3(json["ROTATION"]);
      Matrix4 t = Matrix4::Rotation(v.x * PI/180, v.y * PI/180, v.z * PI/180);
      transform = transform * t;
    } else if (json.count("MATRIX")) {
      json_spirit::Array t = json["MATRIX"].getArray();
      Matrix4 m;
      for (int j = 0; j < 16; j++) {
        m[j / 4][j % 4] = t[j].getReal();
      }
      transform = transform * m;
    }
  }
  return transform;
}