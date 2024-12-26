#pragma once

#include "collisions_utils.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>

#define PLAYER_H


class Player
{
private:
	Vector3 m_position;
	float m_accelY;
	// Vector3 m_velocity;
	
	void CollisionResponse(const BoundingBox& other)
	{
		Vector3 desiredPosition = m_position + m_velocity;

		BoundingBox projectedBox{};
		projectedBox.min = { desiredPosition.x - 0.5f, desiredPosition.y - 0.5f, desiredPosition.z - 0.5f };
		projectedBox.max = { desiredPosition.x + 0.5f, desiredPosition.y + 0.5f, desiredPosition.z + 0.5f };

		float overlapX = CollisionUtils::CheckCollisionsAxisX(projectedBox, other);
		float overlapY = CollisionUtils::CheckCollisionsAxisY(projectedBox, other);
		float overlapZ = CollisionUtils::CheckCollisionsAxisZ(projectedBox, other);

		float leastOverlap = std::min({ std::abs(overlapX), std::abs(overlapY), std::abs(overlapZ) });

		if (leastOverlap == std::abs(overlapX))
		{
			playerCamera.position.x += overlapX;
			playerCamera.target.x += overlapX;
		}

		if (leastOverlap == std::abs(overlapY))
		{

			playerCamera.position.y += overlapY;
			playerCamera.target.y += overlapY;

			m_accelY = 0.0f;
		}

		if (leastOverlap == std::abs(overlapZ))
		{
			playerCamera.position.z += overlapZ;
			playerCamera.target.z += overlapZ;
		}
	}

	Vector2 HandleInput()
	{
		float speed = 0.1f;
		float forwardInput = 0.0f;
		float rightInput = 0.0f;

		if (IsKeyDown(KEY_W))
		{
			forwardInput += speed;
		}
		if (IsKeyDown(KEY_S))
		{
			forwardInput -= speed;
		}
		if (IsKeyDown(KEY_D))
		{
			rightInput += speed;
		}
		if (IsKeyDown(KEY_A))
		{
			rightInput -= speed;
		}

		return { forwardInput, rightInput };
	}

	void UpdateBoundingBox()
	{
		boundingBox.min = { playerCamera.position.x - 0.5f, playerCamera.position.y - 0.5f, playerCamera.position.z - 0.5f };
		boundingBox.max = { playerCamera.position.x + 0.5f, playerCamera.position.y + 0.5f, playerCamera.position.z + 0.5f };
	}

public:
	Player()
		: m_position{ 0, 0, 0 }, m_accelY{ 0 }, m_velocity{ 0, 0, 0 }, boundingBox{ GetMeshBoundingBox(GenMeshCube(1, 1, 1)) }, playerCamera{ { 1, 5.5f, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, 65.0f, CAMERA_PERSPECTIVE }
	{ }

	Player(const Player& other)
		: m_velocity{ other.m_velocity }, m_accelY{ 0 }, m_position{ other.m_position }, boundingBox{ other.boundingBox }, playerCamera{ other.playerCamera }
	{ }

	~Player()
	{ }

	void Draw()
	{
		DrawBoundingBox(boundingBox, BLUE);
	}

	void DrawNewBoundingBox(BoundingBox newBox)
	{
		DrawBoundingBox(newBox, YELLOW);
	}

	Vector3 GetBoundingBoxPosition()
	{
		float x = ((boundingBox.max.x - boundingBox.min.x) / 2.0f) + boundingBox.min.x;
		float y = ((boundingBox.max.y - boundingBox.min.y) / 2.0f) + boundingBox.min.y;
		float z = ((boundingBox.max.z - boundingBox.min.z) / 2.0f) + boundingBox.min.z;

		return { x, y, z };
	}

	void CheckPlayerCollision(const BoundingBox& other)
	{
		if (CheckCollisionBoxes(boundingBox, other))
		{
			CollisionResponse(other);
			UpdateBoundingBox();
		}
	}

	void Update()
	{
		m_position = playerCamera.position;

		Vector2 input = HandleInput();

		m_velocity = { input.y, 0, input.x };

		m_velocity.y -= 9.8 * GetFrameTime();

		if (IsKeyPressed(KEY_SPACE))
		{
			m_accelY += 350.0f * GetFrameTime();
			m_velocity.y += m_accelY;
		}

		Vector2 mouseDelta = GetMouseDelta();
		UpdateCameraPro(&playerCamera, m_velocity, { mouseDelta.x * 2.25f * GetFrameTime(), mouseDelta.y * 2.25f * GetFrameTime(), 0 }, 0.0f);
		UpdateBoundingBox();

	}

public:
	// PlayerCamera playerCamera;
	Vector3 m_velocity;
	Camera3D playerCamera;
	BoundingBox boundingBox;
};