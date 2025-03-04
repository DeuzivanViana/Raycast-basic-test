#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>

#include <raylib.h>

#define LAMP_RADIUS 21
#define OBSTACLE_RADIUS 40
#define RAYLINE_DISTANCE 512.f * 4.f

struct RayLine
{
	Vector2 start, end;
	float angle;
};

int main(int, char*[])
{
	InitWindow(480, 720, "ray-tracing");

	Vector2 lamp_position = {0.f};
	Vector2 obstacle = {300.f, 200.f};
	int lines_to_draw = 360 * 32;

	while(!WindowShouldClose())
	{
		std::vector<RayLine> rays;
		lamp_position = GetMousePosition();
		if(IsKeyReleased(KEY_A))
		{
			lines_to_draw = 360 * 32;
		}
		if(IsKeyReleased(KEY_S))
		{
			lines_to_draw = 180;
		}

		for(int i = 0; i < lines_to_draw; i++)
		{
			float angle = i * DEG2RAD * (360.f / lines_to_draw);
			rays.push_back(RayLine{
				{
					lamp_position.x + static_cast<float>(std::cos(angle)) * LAMP_RADIUS,
					lamp_position.y + static_cast<float>(std::sin(angle)) * LAMP_RADIUS
				},
				{
					lamp_position.x + static_cast<float>(std::cos(angle)) * RAYLINE_DISTANCE,
					lamp_position.y + static_cast<float>(std::sin(angle)) * RAYLINE_DISTANCE
				}, angle
			});
		}
		BeginDrawing();
		ClearBackground(BLACK);


		DrawCircleV(lamp_position, LAMP_RADIUS, WHITE);
		for(int i = 0; i < rays.size(); i++)
		{
			RayLine line = rays[i];
			
			
			if(CheckCollisionCircleLine(obstacle, OBSTACLE_RADIUS, rays[i].start, rays[i].end))
			{
				float distance = std::sqrt(std::pow(
					lamp_position.y - obstacle.y
					
					, 2) + std::pow(
						
						lamp_position.x - obstacle.x,
						2));
						
					line.end.x += static_cast<float>(std::cos(line.angle)) * (distance - RAYLINE_DISTANCE);
					line.end.y += static_cast<float>(std::sin(line.angle)) * (distance - RAYLINE_DISTANCE);
				}
					
				DrawLineV(line.start, line.end, WHITE);
			}
				
			DrawCircleV(obstacle, OBSTACLE_RADIUS, RED);
			EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}
