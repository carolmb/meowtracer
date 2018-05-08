#include "ModelParser.h"
#include "../Object/Triangle.h"
#include "OBJ_Loader.h"
#include <string>

Vec3 parseVertex(objl::Loader &loader, int _i) {
  uint i = loader.LoadedIndices[_i];
  objl::Vertex v = loader.LoadedVertices[i];
  return Vec3(v.Position.X, v.Position.Y, v.Position.Z);
}

Vec3 parseNormal(objl::Loader &loader, int _i) {
  uint i = loader.LoadedIndices[_i];
  objl::Vertex v = loader.LoadedVertices[i];
  return Vec3(v.Normal.X, v.Normal.Y, v.Normal.Z);
}

void parseModel(json_spirit::Object &json, Matrix4 &xform, Scene &scene) {
  std::string fileName = json["FILE"].getString();
  objl::Loader loader;
  loader.LoadFile("meow/" + fileName);
  Material* m = scene.materials[json["MATERIAL"].getInt()];
  for(int i = 0; i < loader.LoadedIndices.size(); i += 3) {
    Vec3 v1 = parseVertex(loader, i);
    Vec3 v2 = parseVertex(loader, i+1);
    Vec3 v3 = parseVertex(loader, i+2);
    Triangle triangle(xform, v1, v2, v3);
    if (triangle.bounds[0].Valid() && triangle.bounds[1].Valid()) {
      // Normals
      Vec3 n1 = parseNormal(loader, i);
      Vec3 n2 = parseNormal(loader, i+1);
      Vec3 n3 = parseNormal(loader, i+2);
      triangle.setNormals(n1, n2, n3);
      // TODO: texture
      triangle.material = m;
      scene.objects.push_back(new Triangle(triangle));
    }
  }
}