#include "MaterialLoader.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::string;
using std::map;

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

Material* MaterialLoader::getMaterial(string& name) {
	return materials.count(name) ? materials[name] : 0;
}

void MaterialLoader::load(string& name) {
	string objFile = "meow/" + name;
	ifstream file(objFile);
	if (!file.is_open()) {
		cout << "Could not load MTL: " << objFile;
	}
/*
	Material mat;
	string matName = "";
	for(row = 0; std::getline(file, line); row++) {
		vector<string> words;
		getWords(line, words);
		if (words.size() == 0)
			continue;

		if (words[0] == "newmtl") {
			if (matName == "") {
				matName = words.size() > 1 ? words[1] : "unnamed";
			} else {
				Material* m = new Material(mat);
				materials[matName] = m;
				clear();
				matName = words.size() > 1 ? words[1] : "unnamed";
			}
		} else if (words[0] == "Ka") {
			mat.diffuse = toVec3(words);
		} else if (words[1] == "Ks") {
			mat.specular = toVec3(words);
		}
	}
*/
}

