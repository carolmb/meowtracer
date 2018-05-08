#define __OBJLOADER__
#ifndef __OBJLOADER__

#include <../Math/Vec3>
#include <string>

	struct Vertex {
		// Position Vector
		// Normal Vector
		Vector3 Normal;
		Vector2 TextureCoordinate;
	};

class ObjLoader {

public:

	ObjLoader(std::string &name) {

	}

}

#endif