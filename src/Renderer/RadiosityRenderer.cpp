#include "RadiosityRenderer.h"
#include "../Light/Light.h"
#include "RendererUtil.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()

Color RadiosityRenderer::getColor(Scene &scene, Ray &r, float &x, float &y) {
	RayHit hr = getHit(r);
	if (hr.object) {
		LightHit lh(r.direction, hr);
		Color finalColor(0, 0, 0);
		for (int i = 0; i < scene.lights.size(); i++) {
			lh.lightDir = scene.lights[i]->getDirection(lh);
			if (!intersects(scene, hr.point, lh.lightDir)) {
				finalColor += scene.lights[i]->diffuseColor(lh);
				finalColor += scene.lights[i]->specularColor(lh);
			}
		}
		finalColor = (finalColor * hr.getTexture());
		finalColor += hr.object->material->ambient * scene.ambientColor;
		finalColor += hr.object->radiosity(hr.uv);
		return finalColor;
	} else {
		return scene.backgroundColor(x, y);
	}
}
