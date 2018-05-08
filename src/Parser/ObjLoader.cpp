#include "ObjLoader.h"
#include <fstream>

using std::vector;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::stof;

inline Vec2 toVec2(vector<string> &words) {
	return Vec2(stof(words[1]), stof(words[2]));
}

inline Vec3 toVec3(vector<string> &words) {
	return Vec3(stof(words[1]), stof(words[2]), stof(words[3]));
}

void getWords(const string& s, vector<string>& v) {
	string buff {""};
	for(auto c : s) {
		if (c != ' ') {
			buff += c; 
		} else if (buff != "") {
			v.push_back(buff); 
			buff = ""; 
		}
	}
	if(buff != "") 
		v.push_back(buff);
}

void getIDs(const string& word, vector<int>& v) {
	string buff {""};
	for(auto c : word) {
		if (c != '/') {
			buff += c; 
		} else {
			v.push_back(buff == "" ? 0 : stoi(buff));
			buff = ""; 
		}
	}
	v.push_back(buff == "" ? 0 : stoi(buff));
	while (v.size() < 4)
		v.push_back(0);
}

void ObjLoader::clear() {
	coords.clear();
	normals.clear();
	colors.clear();
	texUVs.clear();
	vertices.clear();
	normals.push_back(Vec3(NAN, NAN, NAN));
	texUVs.push_back(Vec2(0, 0));
	colors.push_back(Vec3(1, 1, 1));
}

string ObjLoader::loadFace(vector<string> &words) {
	if (words.size() < 4)
		return "Not enough face vertices.";
	vector<vector<int>> vert(0);
	for (uint i = 1; i < words.size(); i ++) {
		vector<int> ids;
		getIDs(words[i], ids);
		vert.push_back(ids);
	}
	for (uint i = 0; i < vert.size() - 2; i += 2) {
		vertices.push_back(Vertex(vert[i][0], vert[i][2], vert[i][1], vert[i][3]));
		vertices.push_back(Vertex(vert[i+1][0], vert[i+1][2], vert[i+1][1], vert[i+1][3]));
		vertices.push_back(Vertex(vert[i+2][0], vert[i+2][2], vert[i+2][1], vert[i+2][3]));
	}
	return "";
}

string ObjLoader::load(string &name) {
	string objFile = "meow/" + name;
	ifstream file(objFile);
	if (!file.is_open()) {
		cout << "Could not load OBJ: " << objFile;
		return "";
	}

	clear();

	string line;
	string meshName = "";
	for(row = 0; std::getline(file, line); row++) {
		vector<string> words;
		getWords(line, words);
		if (words.size() == 0)
			continue;

		if (words[0] == "g" || words[0] == "o") {
			// Object / Group
			if (meshName == "") {
				meshName = words.size() > 1 ? words[1] : "unnamed";
			} else {
				meshes.push_back(Mesh(meshName, vertices, coords, normals, colors, texUVs));
				clear();
				meshName = words.size() > 1 ? words[1] : "unnamed";
			}
		} else if (words[0] == "v") {
			// Coordinates
			if (words.size() < 4)
				return "Not enough vertex coordinates.";
			coords.push_back(toVec3(words));
		} else if (words[0] == "vn") {
			// Normal
			if (words.size() < 4)
				return "Not enough normal components.";
			Vec3 n = toVec3(words);
			normals.push_back(Vec3::Normalize(n));
		} else if (words[0] == "vt") {
			// Texture
			if (words.size() < 3)
				return "Not enough texture coordiantes.";
			texUVs.push_back(toVec2(words));
		} else if (words[0] == "vc") {
			// Color
			if (words.size() < 4)
				return "Not enough color components.";
			colors.push_back(toVec3(words));
		} else if (words[0] == "f") {
			// Face
			string err = loadFace(words);
			if (err != "")
				return err;
		}
	}

	return "";
}

ObjLoader::ObjLoader(string &name) {
	string err = load(name);
	if (err != "") {
		cout << "Line " << row << ": " << err << endl;
	}
}