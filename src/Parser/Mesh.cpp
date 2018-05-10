#include "Mesh.h"

using std::stoi;
using std::stof;
using std::cout;
using std::endl;

template<typename T>
T getElement(vector<T> &v, int i, int off = 0) {
	int n = v.size() - off;
	if (i < 0) {
		i = (-i - 1) % n;
		cout << n - 1 - i << " " << v.size() << endl;
		return v[n - 1 - i];
	} else {
		return v[i - off];
	}
}

Vec3 Mesh::getCoord(int i) { 
	if (vertices[i].coord == 0) {
		cout << "Null vertex coordinates." << endl;
		return Vec3(NAN, NAN, NAN);
	}
	return getElement(coords, vertices[i].coord, 1);
}

Vec3 Mesh::getNormal(int i) {
	return getElement(normals, vertices[i].normal);
}

Vec2 Mesh::getTexUV(int i) {
	return getElement(texUVs, vertices[i].tex);
}

Vec3 Mesh::getColor(int i) { 
	return getElement(colors, vertices[i].color);
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

void Mesh::clear() {
	coords.clear();
	normals.clear();
	colors.clear();
	texUVs.clear();
	vertices.clear();
	normals.push_back(Vec3(NAN, NAN, NAN));
	texUVs.push_back(Vec2(0, 0));
	colors.push_back(Vec3(1, 1, 1));
}

string Mesh::loadFace(vector<string> &words) {
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