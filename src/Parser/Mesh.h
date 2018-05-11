#ifndef __MESH__
#define __MESH__

#include "../Object/Material.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::vector;

struct Vertex {
	
	int coord;
	int normal;
	int tex;
	int color;

	Vertex() {}

	Vertex(int p, int n, int t, int c) 
		: coord(p), normal(n), tex(t), color(c) {}
		
};

struct Mesh {
public:

	string name = "";
	Material* material = 0;
	vector<Vertex> vertices;
	vector<Vec3> coords;
	vector<Vec3> normals;
	vector<Vec3> colors;
	vector<Vec2> texUVs; 

	Mesh() {}

	Mesh(string& ns, Material* mat, vector<Vertex> &v, vector<Vec3> &p, vector<Vec3> &n, vector<Vec3> &c, vector<Vec2> &t) 
		: name(ns), material(mat), vertices(v), coords(p), normals(n), colors(c), texUVs(t) {}

	Vec3 getCoord(int i);
	Vec3 getNormal(int i);
	Vec2 getTexUV(int i);
	Vec3 getColor(int i);

	string loadFace(vector<string> &words);
	void clear();

};

#endif