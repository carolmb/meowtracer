#include "ObjectParser.h"
#include "../Object/Sphere.h"
#include "../Object/Triangle.h"
#include "../Object/Material.h"
#include <string>

#if __cplusplus <= 199711L
  #error This library needs at least a C++11 compliant compiler
#endif

Object* parseSphere(json_spirit::Object &json, Matrix4 &xform) {
  float r = json["RADIUS"].getReal();
  Vec3 center = parseVec3(json["CENTER"]);
  return new Sphere(xform, center, r);
}

Object* parseEllipsoid(json_spirit::Object &json, Matrix4 &xform) {
  Vec3 center = parseVec3(json["CENTER"]);
  Vec3 axis = parseVec3(json["AXIS"]);
  Matrix4 t = Matrix4::Translation(center);
  xform = t * xform;
  Matrix4 s = Matrix4::Scaling(axis);
  xform = s * xform;
  return new Sphere(xform, Vec3(0, 0, 0), 1);
}

Object* parseTriangle(json_spirit::Object &json, Matrix4 &xform) {
  Vec3 p0 = parseVec3(json["P0"]);
  Vec3 p1 = parseVec3(json["P1"]);
  Vec3 p2 = parseVec3(json["P2"]);
  return new Triangle(xform, p0, p1, p2);
}

Object* parseObject(json_spirit::Object &json, Matrix4 &xform, std::string &type, Scene &scene) {
  Object* obj = 0;
  if (type == "sphere") {
    obj = parseSphere(json, xform);
  } else if (type == "ellipsoid") {
    obj = parseEllipsoid(json, xform);
  } else if (type == "triangle") {
    obj = parseTriangle(json, xform);
  } else {
    std::cout << "Object type not recognized: " << type << std::endl;
    return NULL;
  }
  if (json.count("MATERIAL")) {
    int material = json["MATERIAL"].getInt();
    obj->material = scene.materials[material];
  }
  if (json.count("TEXTURE")) {
    int texture = json["TEXTURE"].getInt();
    obj->texture = scene.textures[texture];
  }
  return obj;
}

Texture* parseTexture(json_spirit::Value &value) {
  json_spirit::Object json = value.getObject();
  std::string type = json["TYPE"].getString();
  if (type == "checkers") {
    Color c1 = parseColor(json["COLOR1"]);
    Color c2 = parseColor(json["COLOR2"]);
    int rx = json["REPEATX"].getInt();
    int ry = json["REPEATY"].getInt();
    return new CheckersTexture(c1, c2, rx, ry);
  } else if (type == "image") {
    std::string fileName = "meow/" + json["FILE"].getString();
    return new ImageTexture(fileName);
  } else if (type == "perlin") {
    float scale = json["SCALE"].getReal();
    return new PerlinTexture(scale);
  } else {
    std::cout << "Texture type not recognized: " << type << std::endl;
    return NULL;
  }
}

Material* parseMaterial(json_spirit::Value &value) {
  json_spirit::Object json = value.getObject();
  Material* m = new Material();
  if (json.count("AMBIENT")) {
    m->ambient = parseColor(json["AMBIENT"]);
  }
  if (json.count("DIFFUSE")) {
    m->diffuse = parseColor(json["DIFFUSE"]);
  }
  if (json.count("SPECULAR")) {
    m->specular = parseColor(json["SPECULAR"]);
  }
  if (json.count("SHINE")) {
    m->shininess = json["SHINE"].getReal();
  }
  if (json.count("REFRACTION")) {
    m->ref = json["REFRACTION"].getReal();
  }
  if (json.count("OUTLINECOLOR")) {
    m->outlineColor = parseColor(json["OUTLINECOLOR"]);
  }
  if (json.count("OUTLINEANGLE")) {
    m->outlineAngle = json["OUTLINEANGLE"].getReal();
  }
  if (json.count("COLORS")) {
    json_spirit::Array arr = json["COLORS"].getArray();
    for (int i = 0; i < arr.size(); i++) {
      m->colors.push_back(parseColor(arr[i]));
    }
  }
  if (json.count("INTERVALS")) {
    json_spirit::Array arr = json["INTERVALS"].getArray();
    for (int i = 0; i < arr.size(); i++) {
      m->times.push_back(arr[i].getReal());
    }
  }
  return m;
}