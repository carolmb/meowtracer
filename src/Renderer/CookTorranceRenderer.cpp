#include "CookTorranceRenderer.h"
#include "../Light/Light.h"
#include "RendererUtil.h"
#include <limits>
#include <iostream>
#define INF std::numeric_limits<float>::infinity()
#define N 1

Color CookTorranceRenderer::getColor(Scene &scene, Ray &r, float &x, float &y) {
	RayHit hr = getHit(r);
	if (hr.object) {
		LightHit lh(r.direction, hr);
		Color finalColor(0, 0, 0);
		for (int i = 0; i < N; i++) {
			for (int l = 0; l < scene.lights.size(); l++) {
				lh.lightDir = scene.lights[l]->getDirection(lh);
				lh.lightDir = Vec3::Normalize(lh.lightDir);
				if (!intersects(scene, hr.point, lh.lightDir)) {
					finalColor += scene.lights[l]->fresnel(lh);
				}
			}
		}
		finalColor = (finalColor / N) + hr.object->material->ambient * scene.ambientColor;
		return finalColor + hr.object->material->emissive;
	} else {
		return scene.backgroundColor(x, y);
	}
}
