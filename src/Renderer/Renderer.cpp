#include "Renderer.h"
#include "RendererUtil.h"
#include <iostream>
#include <stack>
#include <cstdlib>

using std::cout;
using std::endl;

Tree* accelerate(std::vector<Object*> &objects, Vec3 bounds[2], int depth);

void clusterBounds(std::vector<Object*> &objects, Vec3 bounds[2]) {
	bounds[0] = Vec3(INF, INF, INF);
	bounds[1] = Vec3(-INF, -INF, -INF);
	for (int i = 0; i < objects.size(); i++) {
		Vec3 obj[2] = objects[i]->bounds;
		bounds[0] = Vec3::Minimize(bounds[0], obj[0]);
		bounds[1] = Vec3::Maximize(bounds[1], obj[1]);
	}
}

Tree* accelerate(std::vector<Object*> &objects, Vec3 bounds[2], int depth) {
	if (objects.size() == 0)
		return 0;

	Tree* tree = new Tree;
		for (int i = 0; i < 8; i++)
			tree->children[i] = 0;

	if (objects.size() == 1) {
		tree->bounds[0] = objects[0]->bounds[0];
		tree->bounds[1] = objects[0]->bounds[1];

		return tree;
	} else {
		Vec3 cbounds[2];
		clusterBounds(objects, cbounds);
		bounds[0] = Vec3::Maximize(bounds[0], cbounds[0]);
		bounds[1] = Vec3::Minimize(bounds[1], cbounds[1]);
		tree->bounds[0] = bounds[0];
		tree->bounds[1] = bounds[1];
	}

	if (depth == 0) {
		tree->objects = objects;
		return tree;
	}

	Vec3 size = bounds[1] - bounds[0];
	Vec3 middle = bounds[0] + size / 2;
	
	Vec3 v[8];
	v[0] = bounds[0];
	v[1] = Vec3(bounds[0].x, bounds[0].y, middle.z);
	v[2] = Vec3(bounds[0].x, middle.y, bounds[0].z);
	v[3] = Vec3(bounds[0].x, middle.y, middle.z);
	v[4] = Vec3(middle.x, bounds[0].y, bounds[0].z);
	v[5] = Vec3(middle.x, bounds[0].y, middle.z);
	v[6] = Vec3(middle.x, middle.y, bounds[0].z);
	v[7] = middle;
	for (int i = 0; i < 8; i++) {
		std::vector<Object*> objs2;
		Vec3 bounds2[2] = {v[i], v[i] + size / 2};
		for (int o = 0; o < objects.size(); o++)
			if (hitsBox(objects[o]->bounds, bounds2)) {
				objs2.push_back(objects[o]);
			}
		tree->children[i] = accelerate(objs2, bounds2, depth - 1);
		//std::cout << objs2.size() << std::endl;
	}
	return tree;
}

Color* Renderer::render(Scene &scene, int width, int height) {
	{
		Vec3 bounds[2];
		clusterBounds(scene.objects, bounds);
		tree = accelerate(scene.objects, bounds, treeDepth);
	}

	Color* colors = new Color[width * height];
	float progress = 0;
	int totalProgress = width * height;
	int progressi = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Color c(0, 0, 0);
			if (sampleCount > 1) 
				for(int s = 0; s < sampleCount; s++) {
					float pixelx = 1.0 * rand() / RAND_MAX + i;
					float pixely = 1.0 * rand() / RAND_MAX + (height - j - 1);
					float x = pixelx / (width - 1);
					float y = pixely / (height - 1);
					Ray ray = scene.camera->getRay(x, y);
					ray.normalize();
					c += getColor(scene, ray, x, y) / sampleCount;
				}
			else {
				float pixelx = 0.5 + i;
				float pixely = 0.5 + (height - j - 1);
				float x = pixelx / (width - 1);
				float y = pixely / (height - 1);
				Ray ray = scene.camera->getRay(x, y);
				ray.normalize();
				c += getColor(scene, ray, x, y) / sampleCount;
			}
			int newProgress = int(++progress * 100 / totalProgress);
			if (newProgress != progressi) {
				progressi = newProgress;
				std::cout << "\rProgress: " << progressi << '%' << std::flush; 
			}
			colors[j * width + i] = c;
		}
	}
	cout << std::endl;
	return colors;
}

RayHit Renderer::getHit(std::vector<Object*> objects, Ray& ray) {
	RayHit minhr;
	minhr.t = INF;
	for (int i = 0; i < objects.size(); i++) {
		RayHit hr = objects[i]->hit(ray);
		if (!std::isnan(hr.t) && hr.t < minhr.t && hr.t > 0) {
			minhr = hr;
			minhr.object = objects[i];
		}
	}
	return minhr;
}

bool Renderer::intersects(Scene &scene, Point3 &p, Vec3 &l) {
  Ray ray(p, l);
  RayHit hr = getHit(ray);
  return !std::isnan(hr.t) && hr.t > 0.00001 && hr.t <= 1;
}

RayHit Renderer::getHit(Ray& r) {
	RayHit minhr;
	minhr.t = INF;
	if (!tree)
		return minhr;

	std::stack<Tree*> trees;
	trees.push(tree);
	while (!trees.empty()) {
		Tree* tree = trees.top();
		trees.pop();
		if (hitsBox(tree->bounds, r)) {
			if (tree->objects.size() > 0) {
				RayHit hr = getHit(tree->objects, r);
				if (!std::isnan(hr.t) && hr.t < minhr.t && hr.t > 0) {
					minhr = hr;
				}
			} else {
				for (int i = 0; i < 8; i++) {
					if (tree->children[i])
						trees.push(tree->children[i]);
				}
			}
		}
	}
	return minhr;
}