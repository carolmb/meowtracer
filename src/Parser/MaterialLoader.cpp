#include "MaterialLoader.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;
using std::map;
using std::stoi;
using std::stof;

void getWords(const string& s, vector<string>& v) {
	string buff {""};
	for(auto c : s) {
		if (c != ' ' and c != '\t') {
			buff += c; 
		} else if (buff != "") {
			v.push_back(buff); 
			buff = ""; 
		}
	}
	if(buff != "") 
		v.push_back(buff);
}

Material* MaterialLoader::getMaterial(string& name) {
	return materials.count(name) ? materials[name] : 0;
}

void MaterialLoader::load(string& name) {
	string objFile = "meow/" + name;
	ifstream file(objFile);
	if (!file.is_open()) {
		cout << "Could not load MTL: " << objFile;
	}
	Material mat;
	string matName = "";
	string line;
	while (std::getline(file, line)) {
		vector<string> words;
		getWords(line, words);
		if (words.size() == 0)
			continue;
		if (words[0] == "newmtl") {
			if (matName != "") {
				materials[matName] = new Material(mat);
				mat = Material();
			}
			matName = words[1];
		} else if (words[0] == "Ka") {
			mat.ambient = toVec3(words);
		} else if (words[0] == "Kd") {
			mat.diffuse = toVec3(words);
		} else if (words[0] == "Ks") {
			mat.specular = toVec3(words);
		} else if (words[0] == "Ke") {
			mat.emissive = toVec3(words);
		} else if (words[0] == "illum") {
			mat.illum = stoi(words[1]);
		} else if (words[0] == "Ni") {
			mat.ref = stof(words[1]);
		} else if (words[0] == "Ns") {
			mat.shininess = stof(words[1]);
		} else if (words[0] == "d") {
			mat.opacity = stof(words[1]);
		}
	}
	materials[matName] = new Material(mat);
}

