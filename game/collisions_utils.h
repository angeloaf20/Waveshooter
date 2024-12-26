#pragma once
#include <map>
#include <vector>

#include "raylib.h"
#include "raymath.h"

enum FaceType
{
	None = 0,
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

struct Face
{
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Vector3 v4;
};

namespace CollisionUtils
{
	/*
	//FaceType GetClosestFace(BoundingBox box, Vector3 position);
	//std::map<FaceType, Vector3> GetFaceNormals(BoundingBox box);
	//void DrawFace(Face face);
	//// Faces are ordered Left, Right, Back, Front, Top, Bottom
	//std::map<FaceType, Face> GetFaces(BoundingBox box);
	//Vector3 GetNormalFromFace(BoundingBox box, FaceType side);
	*/
	float CheckCollisionsAxisX(const BoundingBox& box1, const BoundingBox& box2);
	float CheckCollisionsAxisY(const BoundingBox& box1, const BoundingBox& box2);
	float CheckCollisionsAxisZ(const BoundingBox& box1, const BoundingBox& box2);
}