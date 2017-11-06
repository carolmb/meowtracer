#include "BlinnPhongParser.h"
#include "../Renderer/BlinnPhongRenderer.h"

Renderer* BlinnPhongParser::parse(json_spirit::Object &json) {
  Color ambient = parseVec3(json["AMBIENT"]);
  BlinnPhongRenderer* renderer = new BlinnPhongRenderer(ambient);
  parseScene(renderer);
  json_spirit::Array mat = json["MATERIALS"].getArray();
  for(int i = 0; i < mat.size(); i++) {
    materials.push_back(parseMaterial(mat[i]));
  }
  return renderer;
}

BPMaterial BlinnPhongParser::parseMaterial(json_spirit::Value &value) {
  json_spirit::Object json = value.getObject();
  BPMaterial m;
  m.diffuse = parseVec3(json["DIFFUSE"]);
  m.ambient = parseVec3(json["AMBIENT"]);
  m.specular = parseVec3(json["SPECULAR"]);
  m.shine = json["SHINE"].getDouble();
  return m;
}