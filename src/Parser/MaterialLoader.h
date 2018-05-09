#ifndef __MATLOADER__
#define __MATLOADER__

#include "../Math/Vec3.h"
#include "../Math/Vec2.h"
#include "../Object/Material.h"
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;

class MaterialLoader {
private:
	map<string, Material*> materials;

public:
	void load(string& name);
	Material* getMaterial(string& name);
};

void getWords(const string& s, vector<string>& v);

inline Vec2 toVec2(vector<string> &words) {
	return Vec2(stof(words[1]), stof(words[2]));
}

inline Vec3 toVec3(vector<string> &words) {
	return Vec3(stof(words[1]), stof(words[2]), stof(words[3]));
}

#endif