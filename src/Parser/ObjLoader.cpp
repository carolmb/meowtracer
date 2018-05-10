#include "ObjLoader.h"
#include <fstream>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

string ObjLoader::load(string &name) {
	string objFile = "meow/" + name;
	ifstream file(objFile);
	if (!file.is_open()) {
		cout << "Could not load OBJ: " << objFile;
		return "";
	}
	mesh.clear();
	string line;
	string meshName = "";
	string mat = "";
	for(row = 0; std::getline(file, line); row++) {
		vector<string> words;
		getWords(line, words);
		if (words.size() == 0)
			continue;

		if (words[0] == "g" || words[0] == "o") {
			// Object / Group
			if (meshName != "") {
				mesh.name = meshName;
				mesh.material = materialLoader.getMaterial(mat);
				meshes.push_back(mesh);
				mesh.clear();
			}
			meshName = words.size() > 1 ? words[1] : "unnamed";
		} else if (words[0] == "v") {
			// Coordinates
			if (words.size() < 4)
				return "Not enough vertex coordinates.";
			mesh.coords.push_back(toVec3(words));
		} else if (words[0] == "vn") {
			// Normal
			if (words.size() < 4)
				return "Not enough normal components.";
			Vec3 n = toVec3(words);
			mesh.normals.push_back(Vec3::Normalize(n));
		} else if (words[0] == "vt") {
			// Texture
			if (words.size() < 3)
				return "Not enough texture coordinates.";
			mesh.texUVs.push_back(toVec2(words));
		} else if (words[0] == "vc") {
			// Color
			if (words.size() < 4)
				return "Not enough color components.";
			mesh.colors.push_back(toVec3(words));
		} else if (words[0] == "f") {
			// Face
			string err = mesh.loadFace(words);
			if (err != "")
				return err;
		} else if (words[0] == "usemtl") {
			// Set material
			if (!mesh.vertices.empty()) {
				mesh.name = meshName;
				mesh.material = materialLoader.getMaterial(mat);
				meshes.push_back(mesh);
				mesh.clear();
			}
			mat = words[1];
		} else if (words[0] == "mtllib") {
			// Load materials
			materialLoader.load(words[1]);
		}
	}
	mesh.name = meshName;
	mesh.material = materialLoader.getMaterial(mat);
	meshes.push_back(mesh);
	return "";
}

ObjLoader::ObjLoader(string &name) {
	string err = load(name);
	if (err != "") {
		cout << "Line " << row << ": " << err << endl;
	}
}