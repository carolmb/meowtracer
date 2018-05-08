#ifndef __PATCH__
#define __PATCH__

#include "../Object/Trangle.h"

class Patch : public Triangle {
  public:

    // Patch id
    unsigned int id;
    
    /* Values used to calculate result color, names according to http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter39.html */
    // Already accumulated color
    Color accumulatedColor;
    // Color to be shot from patch
    Color residualColor;

    Patch(int i, Material* mat, Vec3 &v0, Vec3 &v1, Vec3 &v2) : material(mat), id(i) {
        residualColor = material->emmission * material->emissivity;
        accumulatedColor = material->emmission;
    }

    virtual ~Patch();
    virtual float getSize() const = 0;
    virtual float getArea() const = 0;
    virtual Vector getCenter() const = 0;
    virtual Vector getNormal() const = 0;
    virtual Vector getRandomPoint() const = 0;
    virtual Hemisphere getHemisphere() const = 0;
    virtual std::vector<VertexPointer> getVertices() const = 0;
    virtual Color getColor(const RayIntersection &rayIntersection) const = 0;
    
    virtual QSharedPointer<PatchCollection> split() const = 0;
    virtual RayIntersection intersectWithRay(const Ray &ray) const = 0;

    Color getEmissionEnergy() {
        return accumulatedColor * getArea();
    }

};

#endif