#include "collisions_utils.h"
#include <iostream>

namespace CollisionUtils
{
	/*
	FaceType GetClosestFace(BoundingBox box, Vector3 position)
	{
		FaceType closestFace{};

		std::map<FaceType, Vector3> faces = {
			{ FaceType::FRONT,  { 0, 0, box.max.z } },
			{ FaceType::BACK,   { 0, 0, box.min.z } },
			{ FaceType::LEFT,   { box.min.x, 0, 0 } },
			{ FaceType::RIGHT,  { box.max.x, 0, 0 } },
			{ FaceType::BOTTOM, { 0, box.min.y, 0 }},
			{ FaceType::TOP,    { 0, box.max.y, 0 }}
		};

		float minDistance = Vector3Distance(position, faces[FaceType::FRONT]);

		for (const auto& pair : faces)
		{
			if (Vector3Distance(position, pair.second) < minDistance)
			{
				minDistance = Vector3Distance(position, pair.second);
				closestFace = pair.first;
			}
		}

		return closestFace;
	}

	std::map<FaceType, Vector3> GetFaceNormals(BoundingBox box)
	{
		std::map<FaceType, Vector3> faceNormals{};

		Vector3 leftBottomBack = { box.min.x, box.min.y, box.min.z };
		Vector3 leftBottomFront = { box.min.x, box.min.y, box.max.z };
		Vector3 leftTopBack = { box.min.x, box.max.y, box.min.z };
		Vector3 leftTopFront = { box.min.x, box.max.y, box.max.z };

		Vector3 rightBottomBack = { box.max.x, box.min.y, box.min.z };
		Vector3 rightBottomFront = { box.max.x, box.min.y, box.max.z };
		Vector3 rightTopBack = { box.max.x, box.max.y, box.min.z };
		Vector3 rightTopFront = { box.max.x, box.max.y, box.max.z };
	
		Vector3 bottomRightEdge = rightBottomFront - rightBottomBack;
		Vector3 backRightEdge = rightBottomBack - rightTopBack;
		Vector3 bottomFrontEdge = rightBottomFront - rightTopFront;
		Vector3 rightFrontEdge = rightBottomFront - leftBottomFront;
		Vector3 bottomBackEdge = leftBottomBack - rightBottomBack;

		Vector3 rightFaceNormal = Vector3Normalize(Vector3CrossProduct(bottomRightEdge, backRightEdge));
		faceNormals[FaceType::RIGHT] = rightFaceNormal;

		Vector3 frontFaceNormal = Vector3Normalize(Vector3CrossProduct(bottomFrontEdge, rightFrontEdge));
		faceNormals[FaceType::FRONT] = frontFaceNormal;

		Vector3 topFaceNormal = Vector3Normalize(Vector3CrossProduct(bottomBackEdge, bottomRightEdge));
		faceNormals[FaceType::TOP] = topFaceNormal;

		faceNormals[FaceType::LEFT] = { -rightFaceNormal.x, rightFaceNormal.y, rightFaceNormal.z };
		faceNormals[FaceType::BACK] = { frontFaceNormal.x, frontFaceNormal.y, -frontFaceNormal.z };
		faceNormals[FaceType::BOTTOM] = { topFaceNormal.x, -topFaceNormal.y, topFaceNormal.z };

		return faceNormals;
	}

	void DrawFace(Face face)
	{
		DrawLine3D(face.v1, face.v2, RED);
		DrawLine3D(face.v2, face.v3, RED);
		DrawLine3D(face.v3, face.v4, RED);
		DrawLine3D(face.v4, face.v1, RED);
	}

	std::map<FaceType, Face> GetFaces(BoundingBox box)
	{
		Vector3 leftBottomBack = { box.min.x, box.min.y, box.min.z };
		Vector3 leftBottomFront = { box.min.x, box.min.y, box.max.z };
		Vector3 leftTopBack = { box.min.x, box.max.y, box.min.z };
		Vector3 leftTopFront = { box.min.x, box.max.y, box.max.z };

		Vector3 rightBottomBack = { box.max.x, box.min.y, box.min.z };
		Vector3 rightBottomFront = { box.max.x, box.min.y, box.max.z };
		Vector3 rightTopBack = { box.max.x, box.max.y, box.min.z };
		Vector3 rightTopFront = { box.max.x, box.max.y, box.max.z };

		Face left = {
			leftTopFront,
			leftTopBack,
			leftBottomBack,
			leftBottomFront,
		};

		Face right = {
			rightTopFront,
			rightTopBack,
			rightBottomBack,
			rightBottomFront,
		};

		Face back = {
			leftTopBack,
			rightTopBack,
			rightBottomBack,
			leftBottomBack,
		};

		Face front = {
			leftTopFront,
			rightTopFront,
			rightBottomFront,
			leftBottomFront,
		};

		Face top = {
			rightTopFront,
			leftTopFront,
			leftTopBack,
			rightTopBack,
		};

		Face bottom = {
			rightBottomFront,
			leftBottomFront,
			leftBottomBack,
			rightBottomBack,
		};

		return { 
			{ LEFT, left },
			{ RIGHT, right },
			{ TOP, top },
			{ BOTTOM, bottom },
			{ FRONT, front },
			{ BACK, back },
		};
	}

	Vector3 GetNormalFromFace(BoundingBox box, FaceType side)
	{
		std::map<FaceType, Vector3> faceSides = GetFaceNormals(box);

		return faceSides[side];
	}
	*/

	float CheckCollisionsAxisX(const BoundingBox& box1, const BoundingBox& box2)
	{
		float overlapX{ };

		float sideX = std::max(abs(box2.max.x - box1.min.x), abs(box1.max.x - box2.min.x));

		if (sideX == abs(box2.max.x - box1.min.x))
		{
			overlapX = box2.min.x - box1.max.x;
		}
		else if (sideX == abs(box1.max.x - box2.min.x))
		{
			overlapX = box2.max.x - box1.min.x;
		}

		return overlapX;
	}

	float CheckCollisionsAxisY(const BoundingBox& box1, const BoundingBox& box2)
	{
		float overlapY{ };

		float sideY = std::max(abs(box2.max.y - box1.min.y), abs(box1.max.y - box2.min.y));

		if (sideY == abs(box2.max.y - box1.min.y))
		{
			overlapY = box2.min.y - box1.max.y;
		}
		else if (sideY == abs(box1.max.y - box2.min.y))
		{
			overlapY = box2.max.y - box1.min.y;
		}

		return overlapY;
	}

	float CheckCollisionsAxisZ(const BoundingBox& box1, const BoundingBox& box2)
	{
		float overlapZ{ };

		float sideZ = std::max(abs(box2.max.z - box1.min.z), abs(box1.max.z - box2.min.z));

		if (sideZ == abs(box2.max.z - box1.min.z))
		{
			overlapZ = box2.min.z - box1.max.z;
		}
		else if (sideZ == abs(box1.max.z - box2.min.z))
		{
			overlapZ = box2.max.z - box1.min.z;
		}

		return overlapZ;
	}
}