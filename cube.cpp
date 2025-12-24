#include "raylib.h"
#include <math.h>

Vector3 RotateX(Vector3 v, float a)
{
    float c = cosf(a), s = sinf(a);
    return (Vector3){v.x, v.y*c - v.z*s, v.y*s + v.z*c};
}

Vector3 RotateY(Vector3 v, float a)
{
    float c = cosf(a), s = sinf(a);
    return (Vector3){v.x*c + v.z*s, v.y, -v.x*s + v.z*c};
}

int main(void)
{
    const int screenWidth = 800, screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rotating Cube");
    SetTargetFPS(60);

    Camera3D camera = {0};
    camera.position = (Vector3){20,20,20};
    camera.target   = (Vector3){0,0,0};
    camera.up       = (Vector3){0,1,0};
    camera.fovy     = 45;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cube[8] = {
        {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
        {-1,-1,1},  {1,-1,1},  {1,1,1},  {-1,1,1}
    };

    while (!WindowShouldClose())
    {
        float t = GetTime();
        Vector3 rotated[8];

        for (int i = 0; i < 8; i++)
        {
            Vector3 v = cube[i];
            v = RotateX(v, t);
            v = RotateY(v, t*0.5f);
            v.x *= 5; v.y *= 5; v.z *= 5;
            rotated[i] = v;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        DrawLine3D(rotated[0], rotated[1], BLACK);
        DrawLine3D(rotated[1], rotated[2], BLACK);
        DrawLine3D(rotated[2], rotated[3], BLACK);
        DrawLine3D(rotated[3], rotated[0], BLACK);
        DrawLine3D(rotated[4], rotated[5], BLACK);
        DrawLine3D(rotated[5], rotated[6], BLACK);
        DrawLine3D(rotated[6], rotated[7], BLACK);
        DrawLine3D(rotated[7], rotated[4], BLACK);
        DrawLine3D(rotated[0], rotated[4], BLACK);
        DrawLine3D(rotated[1], rotated[5], BLACK);
        DrawLine3D(rotated[2], rotated[6], BLACK);
        DrawLine3D(rotated[3], rotated[7], BLACK);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
