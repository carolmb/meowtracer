#include "Renderer.h"
#include "RendererUtil.h"
#include <iostream>
#include <stack>
#include <cstdlib>

Tree* accelerate(std::vector<Object*> &objects, Vec3 bounds[2], int depth);

void clusterBounds(std::vector<Object*> &objects, Vec3 bounds[2]) {
	bounds[0] = Vec3(-INF, -INF, -INF);
	bounds[1] = Vec3(INF, INF, INF);
	for (int i = 0; i < objects.size(); i++) {
		Vec3 obj[2] = objects[i]->bounds;
		bounds[0].x = fmin(bounds[0].x, obj[0].x);
		bounds[0].y = fmin(bounds[0].y, obj[0].y);
		bounds[0].z = fmin(bounds[0].z, obj[0].z);
		bounds[1].x = fmax(bounds[1].x, obj[1].x);
		bounds[1].y = fmax(bounds[1].y, obj[1].y);
		bounds[1].z = fmax(bounds[1].z, obj[1].z);
	}
}

Tree* accelerate(std::vector<Object*> &objects, Vec3 bounds[2], int depth) {
	Tree *tree = new Tree;
	tree->objects = objects;
	return tree;

	/*
	if (objects.size() == 0)
		return 0;

	Tree* tree = new Tree;

	if (objects.size() == 1) {
		tree->bounds[0] = objects[0]->bounds[0];
		tree->bounds[1] = objects[0]->bounds[1];
		return tree;
	}

	Vec3 cbounds[2];
	clusterBounds(objects, cbounds);
	bounds[0].x = fmax(cbounds[0].x, bounds[0].x);
	bounds[0].y = fmax(cbounds[0].y, bounds[0].y);
	bounds[0].z = fmax(cbounds[0].z, bounds[0].z);
	bounds[1].x = fmin(cbounds[1].x, bounds[1].x);
	bounds[1].y = fmin(cbounds[1].y, bounds[1].y);
	bounds[1].z = fmin(cbounds[1].z, bounds[1].z);

	tree->bounds[0] = bounds[0];
	tree->bounds[1] = bounds[1];

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
		Vec3 b[2] = {v[i], v[i] + size};
		for (int o = 0; o < objects.size(); o++)
			if (hitsBox(objects[o]->bounds, b))
				objs2.push_back(objects[o]);
		tree->children[i] = accelerate(objs2, b, depth - 1);
	}
	return tree;*/
}

Color* Renderer::render(Scene &scene, int width, int height) {
	Vec3 b[2];
	clusterBounds(scene.objects, b);
	tree = accelerate(scene.objects, b, 1);

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
	std::cout << std::endl;
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

RayHit Renderer::getHit(Ray& r) {
	return getHit(tree->objects, r);
	/*
	RayHit minhr;
	minhr.t = INF;

	std::stack<Tree*> trees;
	trees.push(tree);
	while (!trees.empty()) {
		Tree* tree = trees.top();
		trees.pop();
		if (hitsBox(tree->bounds, r) >= 0) {
			if (tree->objects.size() > 0) {
				RayHit hr = getHit(tree->objects, r);
				if (!std::isnan(hr.t) && hr.t < minhr.t && hr.t > 0) {
					minhr = hr;
				}
			}
			for (int i = 0; i < 8; i++) {
				if (tree->children[i])
					trees.push(tree->children[i]);
			}
		}
	}
	return minhr;
	*/
}