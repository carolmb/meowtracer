#ifndef __OBJLOADER__
#define __OBJLOADER__

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"
#include <string>
#include <vector>
#include <cmath>

using std::vector;
using std::string;

struct Vertex {
	int coord;
	int normal;
	int tex;
	int color;
	Vertex(int p, int n, int t, int c) 
		: coord(p), normal(n), tex(t), color(c) {}
};

struct Mesh {
	string name;
	vector<Vertex> vertices;
	vector<Vec3> coords;
	vector<Vec3> normals;
	vector<Vec3> colors;
	vector<Vec2> texUVs; 
	Mesh(string& ns, vector<Vertex> &v, vector<Vec3> &p, vector<Vec3> &n, vector<Vec3> &c, vector<Vec2> &t) 
		: name(ns), vertices(v), coords(p), normals(n), colors(c), texUVs(t) {}
};

class ObjLoader {

private:
	int row;
	string load(string& name);
	string loadFace(vector<string> &words);
	void clear();

public:

	vector<Mesh> meshes;

	vector<Vertex> vertices;
	vector<Vec3> coords;
	vector<Vec3> normals;
	vector<Vec3> colors;
	vector<Vec2> texUVs; 

	ObjLoader(string &name);

	Vec3 getCoord(int i) { 
		if (vertices[i].coord == 0) {
			std::cout << "Null vertex coordinates." << std::endl;
			return Vec3(NAN, NAN, NAN);
		}
		return coords[vertices[i].coord - 1]; 
	}

	Vec3 getNormal(int i) {
		return normals[vertices[i].normal]; 
	}

	Vec2 getTexUV(int i) {
		return texUVs[vertices[i].tex]; 
	}

	Vec3 getColor(int i) { 
		return colors[vertices[i].color]; 
	}

};

#endif