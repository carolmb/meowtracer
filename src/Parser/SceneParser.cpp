#include "SceneParser.h"
#include "../Scene.h"
#include "../Renderer/NormalRenderer.h"
#include "../Renderer/MapRenderer.h"
#include "../Renderer/DiffuseRenderer.h"
#include "../Renderer/DielectricRenderer.h"
#include "../Renderer/BlinnPhongRenderer.h"
#include "../Renderer/CookTorranceRenderer.h"
#include "../Renderer/CelRenderer.h"
#include "../Renderer/RadiosityRenderer.h"
#include "../Camera/OrthogonalCamera.h"
#include "../Camera/PerspectiveCamera.h"
#include "../Light/DirectionalLight.h"
#include "../Light/PointLight.h"
#include "../Light/SpotLight.h"
#include "../Light/SphereLight.h"

void parseLight(Scene& scene, json_spirit::Value &value) {
  Light* light;
  json_spirit::Object json = value.getObject();
  std::string type = json["TYPE"].getString();
  Color color = parseColor(json["COLOR"]);
  Matrix4 xform = json.count("TRANSFORM") ? parseTransform(json["TRANSFORM"]) : Matrix4::Identity();
  if (type == "directional") {
    Vec3 dir = parseVec3(json["DIRECTION"]);
    dir = Vec3::Normalize(dir);
    light = new DirectionalLight(xform, color, dir);
  } else if (type == "point") {
    Point3 origin = parseVec3(json["ORIGIN"]);
    light = new PointLight(xform, color, origin);
  } else if (type == "spot") {
    Point3 origin = parseVec3(json["ORIGIN"]);
    Vec3 dir = parseVec3(json["DIRECTION"]);
    float angle = cos(json["ANGLE"].getReal() * PI / 180.0);
    light = new SpotLight(xform, color, origin, dir, angle);
  } else if (type == "sphere") {
    Point3 origin = parseVec3(json["ORIGIN"]);
    Vec3 dir = parseVec3(json["DIRECTION"]);
    float angle = cos(json["ANGLE"].getReal() * PI / 180.0);
    float size = json["SIZE"].getReal();
    light = new SphereLight(xform, color, origin, dir, angle, size);
  } else if (type == "grid") {
    int gridX = json["GRIDX"].getInt();
    int gridY = json["GRIDY"].getInt();
    Vec3 h = parseVec3(json["HORIZONTAL"]) / gridX;
    Vec3 v = parseVec3(json["VERTICAL"]) / gridY;
    Point3 o = parseVec3(json["ORIGIN"]) + h / 2 + v / 2;
    Vec3 dir = parseVec3(json["DIRECTION"]);
    float angle = cos(json["ANGLE"].getReal() * PI / 180.0);
    color /= gridX * gridY;
    for(int i = 0; i < gridX; i++)
      for(int j = 0; j < gridY; j++) {
        Point3 origin = o + h * i + v * j;
        scene.lights.push_back(new SpotLight(xform, color, origin, dir, angle));
      }
    return;
  } else {
    std::cout << "Light type not recognized: " << type << std::endl;
  }
  scene.lights.push_back(light);
}

Camera* parseCamera(json_spirit::Value &value) {
  json_spirit::Object json = value.getObject();
  std::string type = json["TYPE"].getString();
  Matrix4 xform = json.count("TRANSFORM") ? parseTransform(json["TRANSFORM"]) : Matrix4::Identity();
  Point3 center = parseVec3(json["CENTER"]);
  float w = json["WIDTH"].getReal();
  float h = json["HEIGHT"].getReal();
  Vec3 hor(w, 0, 0);
  Vec3 ver(0, h, 0);
  Point3 p = center - Vec3(w / 2, h / 2, 0);
  if (type == "perspective") {
    Point3 viewer = parseVec3(json["VIEWER"]);
    Point3 lens = center + viewer;
    return new PerspectiveCamera(xform, hor, ver, p, lens);
  } else if (type == "parallel") {
    Vec3 dir = json.count("DIRECTION") ? parseVec3(json["DIRECTION"]) : Vec3(0, 0, -1);
    return new OrthogonalCamera(xform, hor, ver, p, dir);
  } else {
    std::cout << "Camera type not recognized: " << type << std::endl;
    return NULL;
  }
}

Renderer* parseRenderer(json_spirit::Value &value) {
  json_spirit::Object json = value.getObject();
  std::string type = json["TYPE"].getString();
  int samples = json["SAMPLES"].getInt();
  int treeDepth = json.count("TREEDEPTH") ? json["TREEDEPTH"].getInt() : 0;
  if (type == "normal") {
    return new NormalRenderer(samples, treeDepth);
  } else if (type == "map") {
    Color fg = parseColor(json["FOREGROUND"]);
    Color bg = parseColor(json["BACKGROUND"]);
    float d = json["MAXDEPTH"].getReal();
    return new MapRenderer(samples, treeDepth, fg, bg, d);
  } else if (type == "diffuse") {
    int depth = json["RAYDEPTH"].getInt();
    return new DiffuseRenderer(samples, treeDepth, depth);
  } else if (type == "blinnphong") {
    return new BlinnPhongRenderer(samples, treeDepth);
  } else if (type == "cooktorrance") {
    return new CookTorranceRenderer(samples, treeDepth);
  } else if (type == "radiosity") {
    return new RadiosityRenderer(samples, treeDepth);
  } else if (type == "cel") {
    return new CelRenderer(samples, treeDepth);
  } else if (type == "dielectric") {
    int depth = json["RAYDEPTH"].getInt();
    return new DielectricRenderer(samples, treeDepth, depth);
  } else {
    std::cout << "Renderer type not recognized: " << type << std::endl;
    return NULL;
  }
}