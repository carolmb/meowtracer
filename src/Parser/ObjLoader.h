#ifndef __OBJLOADER__
#define __OBJLOADER__

#include "MaterialLoader.h"
#include "Mesh.h"

using std::vector;
using std::string;

class ObjLoader {

private:
	int row;
	string load(string& name);
public:
	MaterialLoader materialLoader;
	vector<Mesh> meshes;
	Mesh mesh;
	ObjLoader(string &name);
};

#endif