#include "headers/Configs.h"
#include "headers/Bird.h"
#include "headers/MoveMap.h"
#define RAYGUI_IMPLEMENTATION 
#include <raygui.h>

bool Pause = false;

void Init(void);
void Update(void);
void Draw(void);
void Finalize(void);

int main(void)
{
	Init();

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_R))
		{
			Bird::Init();
			Pipe::Init();
		}
		if (IsKeyPressed(KEY_F))
			ToggleFullscreen();

		if (IsKeyPressed(KEY_SPACE))
			Pause = !Pause;

		if (!Pause)
			Update();

		BeginDrawing();
			ClearBackground(WHITE);
			Draw();
		EndDrawing();
	}
	Finalize();
	return 0;
}

void Init(void)
{
	Bird::Init();
	Pipe::Init();

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flapy Bird IA");
	SetTargetFPS(60);

	GuiLoadStyle("images/Dark.rgs");

	Image icon = LoadImage("images/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
		
	tBird[0] = LoadTexture("images/bird0.png");
	tBird[1] = LoadTexture("images/bird1.png");
	tBird[2] = LoadTexture("images/bird2.png");
	tBird[3] = LoadTexture("images/bird3.png");
	tBird[4] = LoadTexture("images/bird4.png");
	tBird[5] = LoadTexture("images/bird5.png");
	tBird[6] = LoadTexture("images/bird6.png");
	tPipe = LoadTexture("images/pipe.png");
	tBackground = LoadTexture("images/background.png");
	tGround = LoadTexture("images/ground.png");
}

void Update(void)
{
	Bird::Update();
	Pipe::Update();
	MoveMap();

	if (FRAME_RATE != FRAME_RATE2)
	{
		SetTargetFPS(FRAME_RATE);
		FRAME_RATE2 = FRAME_RATE;
	}
}

void Draw(void)
{
	DrawTextureRec(tBackground, Rectangle{ (float)BACKGROUND_POSX,0, (float)WINDOW_WIDTH, (float)BACKGROUND_HEIGHT }, Vector2{ 0, (float)-GROUND_HEIGHT + 5}, WHITE);
	Bird::DrawBirds();
	Pipe::Draw();
	DrawTextureRec(tGround, Rectangle{ (float)GROUND_POSX,0, (float)WINDOW_WIDTH, (float)GROUND_HEIGHT }, Vector2{ 0, (float)WINDOW_HEIGHT - GROUND_HEIGHT }, WHITE);
	
	DrawText(TextFormat("Birds: %i", TOTAL_BIRDS - DEAD_BIRDS), WINDOW_WIDTH - 250, 50, 30, WHITE);
	DrawText(TextFormat("Generation: %i", GENERATION), WINDOW_WIDTH - 250, 80, 30, WHITE);

	FRAME_RATE = GuiSliderBar(Rectangle{ (float)WINDOW_WIDTH - 250, 25, 200, 25 }, "", "", FRAME_RATE, 60, 250);
}

void Finalize(void)
{
	Bird::Delete();
	Pipe::Delete();

	UnloadTexture(tBird[0]);
	UnloadTexture(tBird[1]);
	UnloadTexture(tBird[2]);
	UnloadTexture(tBird[3]);
	UnloadTexture(tBird[4]);
	UnloadTexture(tBird[5]);
	UnloadTexture(tBird[6]);
	UnloadTexture(tPipe);
	UnloadTexture(tBackground);
	UnloadTexture(tGround);

	std::cout << GetWorkingDirectory() << std::endl;
}