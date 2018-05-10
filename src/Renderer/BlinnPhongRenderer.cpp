#include "BlinnPhongRenderer.h"
#include "../Light/Light.h"
#include "RendererUtil.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color BlinnPhongRenderer::getColor(Scene &scene, Ray &r, float &x, float &y) {
	RayHit rh = getHit(r);
	if (rh.object) {
		Color finalColor(0, 0, 0);
		for (int i = 0; i < scene.lights.size(); i++) {
			LightHit lh = scene.lights[i]->getHit(r.direction, rh);
			if (!intersects(scene, lh)) {
				finalColor += scene.lights[i]->diffuseColor(lh);
				finalColor += scene.lights[i]->specularColor(lh);
			}
		}
		finalColor = (finalColor * rh.getTexture()) + rh.object->material->ambient * scene.ambientColor;
		return finalColor;
	} else {
		return scene.backgroundColor(x, y);
	}
}
