/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include <iostream>

#include "Player.h"
#include "game.h"   // an external header in this project
#include "lib.h"	// an external header in the static lib project

Camera3D debugCamera;
bool debugCamOn = false;
Player* player;
std::vector<BoundingBox> boxes;

static void GameInit()
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(InitalWidth, InitalHeight, "Waveshooter");
    SetTargetFPS(60);

    player = new Player();
    debugCamera = { 
        { 0, 5, -1 }, 
        { 0, 0, 0 }, 
        { 0, 1, 0 }, 
        65.0f, 
        CAMERA_PERSPECTIVE };

    Model ground = LoadModelFromMesh(GenMeshCube(50, 1, 50));

    Model obstacle1 = LoadModelFromMesh(GenMeshCube(2, 3, 2));
    obstacle1.transform = MatrixTranslate(10, 1.5, 7);

    Model obstacle2 = LoadModelFromMesh(GenMeshCube(2, 3, 2));
    obstacle2.transform = MatrixTranslate(-5, 1.5, 2);

    Model obstacle3 = LoadModelFromMesh(GenMeshCube(2, 3, 2));
    obstacle3.transform = MatrixTranslate(-10, 1.5, -20);
    
    boxes.push_back(GetModelBoundingBox(ground));
    boxes.push_back(GetModelBoundingBox(obstacle1));
    boxes.push_back(GetModelBoundingBox(obstacle2));
    boxes.push_back(GetModelBoundingBox(obstacle3));
}

static void GameCleanup()
{
    CloseWindow();
}

static bool GameUpdate()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        DisableCursor();
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        EnableCursor();
    }
    if (IsKeyPressed(KEY_F))
    {
        debugCamOn = !debugCamOn;
    }

    if (debugCamOn)
    {
        UpdateCamera(&debugCamera, CAMERA_FREE);
    }
    else
    {
        player->Update();

        for (const BoundingBox& box : boxes)
        {
            player->CheckPlayerCollision(box);
        }
    }

    return true;
}

static void Draw3D()
{

    /*CollisionUtils::DrawFace(boxFaces[FaceType::FRONT]);
    CollisionUtils::DrawFace(boxFaces[FaceType::TOP]);*/

    if (debugCamOn)
    {
        BeginMode3D(debugCamera);
    }
    else
    {
        BeginMode3D(player->playerCamera);
    }
    
    for (const BoundingBox& box : boxes)
    {
        DrawBoundingBox(box, GREEN);
    }

    player->Draw();

    DrawLine3D({ 0, 0, 0 }, { 10, 0, 0 }, RED);
    DrawLine3D({ 0, 0, 0 }, { 0, 10, 0 }, GREEN);
    DrawLine3D({ 0, 0, 0 }, { 0, 0, 10 }, BLUE);

    EndMode3D();
}

static void GameDraw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    Draw3D();

    DrawText(TextFormat("Velocity: %0.2f, %0.2f, %0.2f", player->m_velocity.x, player->m_velocity.y, player->m_velocity.z), 10, 25, 35, RED);
    DrawText(TextFormat("Position: %0.2f, %0.2f, %0.2f", player->playerCamera.position.x, player->playerCamera.position.y, player->playerCamera.position.z), 10, 65, 35, RED);

    EndDrawing();
}

int main()
{
    GameInit();

    while (!WindowShouldClose())
    {
        if (!GameUpdate())
            break;

        GameDraw();
    }
    GameCleanup();

    return 0;
}