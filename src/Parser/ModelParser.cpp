#include "ModelParser.h"
#include "../Object/Triangle.h"
#include "ObjLoader.h"
#include <string>

void parseModel(json_spirit::Object &json, Matrix4 &xform, Scene &scene) {
  std::string fileName = json["FILE"].getString();
  ObjLoader loader(fileName);
  Material* m = scene.materials[json["MATERIAL"].getInt()];
  for(int i = 0; i < loader.vertices.size(); i += 3) {
    Vec3 v1 = loader.getCoord(i);
    Vec3 v2 = loader.getCoord(i+1);
    Vec3 v3 = loader.getCoord(i+2);
    Triangle triangle(xform, v1, v2, v3);
    if (triangle.bounds[0].Valid() && triangle.bounds[1].Valid()) {
      // Normals
      Vec3 n1 = loader.getNormal(i);
      Vec3 n2 = loader.getNormal(i+1);
      Vec3 n3 = loader.getNormal(i+2);
      triangle.setNormals(n1, n2, n3);
      // TODO: texture
      triangle.material = m;
      scene.objects.push_back(new Triangle(triangle));
    }
  }
}