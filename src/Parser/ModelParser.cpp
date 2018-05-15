#include "ModelParser.h"
#include "../Object/Triangle.h"
#include "ObjLoader.h"
#include <string>

using std::cout;
using std::endl;

void parseModel(json_spirit::Object &json, Matrix4 &xform, Scene &scene) {
  std::string fileName = json["FILE"].getString();
  ObjLoader loader(fileName);
  Material* mat = json.count("MATERIAL") ? scene.materials[json["MATERIAL"].getInt()] : 0;
  Texture* tex = json.count("TEXTURE") ? scene.textures[json["TEXTURE"].getInt()] : 0;
  for (int m = 0; m < loader.meshes.size(); m++) {
    Mesh& mesh = loader.meshes[m];
    Material* meshMat = mat == 0 ? mesh.material : mat;
    for(int i = 0; i < mesh.vertices.size(); i += 3) {
      Vec3 v1 = mesh.getCoord(i);
      Vec3 v2 = mesh.getCoord(i+1);
      Vec3 v3 = mesh.getCoord(i+2);
      Triangle triangle(xform, v1, v2, v3);
      if (triangle.bounds[0].Valid() && triangle.bounds[1].Valid()) {
        Vec3 n1 = mesh.getNormal(i);
        Vec3 n2 = mesh.getNormal(i+1);
        Vec3 n3 = mesh.getNormal(i+2);
        Color c1 = mesh.getColor(i);
        Color c2 = mesh.getColor(i+1);
        Color c3 = mesh.getColor(i+2);
        triangle.setNormals(n1, n2, n3);
        triangle.setRadiosity(c1, c2, c3);
        triangle.texture = tex;
        triangle.material = meshMat;
        scene.objects.push_back(new Triangle(triangle));
      }
    }
  }
}