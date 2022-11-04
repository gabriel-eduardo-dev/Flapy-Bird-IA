#include "headers/Configs.h"
#include "headers/Bird.h"
#include "headers/MoveMap.h"

static bool Pause = false;

static void Init(void);
static void Update(void);
static void Draw(void);
static void Finalize(void);

int main(int argc, char *argv[])
{
	Init();

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_R)) // Mata a população
		{
			Bird::Init();
			Pipe::Init();
		}
		if (IsKeyPressed(KEY_F)) // Toggle fulscreen
			ToggleFullscreen();

		if (IsKeyPressed(KEY_SPACE)) { // Pausa
			Pause = !Pause;
		}

		if (!Pause) {
			Update();
		}

		BeginDrawing();
			ClearBackground(WHITE);
			Draw();
		EndDrawing();
	}
	Finalize();
}

static void Init(void)
{
	Bird::Init();
	Pipe::Init();

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flapy Bird IA");
	SetTargetFPS(60);

	Image icon = LoadImage("src/images/icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	for (size_t i = 0; i < static_cast<int>(sizeof(tBird)/sizeof(tBird[0])); i++) {
		tBird[i] = LoadTexture(("src/images/bird" + std::to_string(i) + ".png").c_str());
	}

	tPipe = LoadTexture("src/images/pipe.png");
	tBackground = LoadTexture("src/images/background.png");
	tGround = LoadTexture("src/images/ground.png");
}

static void Update(void)
{
	Bird::Update();
	Pipe::Update();
	MoveMap();

	// se aumenta ou diminui a velocidade
	if (IsKeyDown(KEY_RIGHT))
	{
		FRAME_RATE += 5;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		FRAME_RATE -= 5;
	}
	if (FRAME_RATE != FRAME_RATE2)
	{
		SetTargetFPS(FRAME_RATE);
		FRAME_RATE2 = FRAME_RATE;
	}
}

static void Draw(void)
{
	DrawTextureRec(tBackground, Rectangle{ (float)BACKGROUND_POSX,0, (float)WINDOW_WIDTH, (float)BACKGROUND_HEIGHT }, Vector2{ 0, (float)-GROUND_HEIGHT + 5}, WHITE);
	Bird::Draw();
	Pipe::Draw();
	DrawTextureRec(tGround, Rectangle{ (float)GROUND_POSX,0, (float)WINDOW_WIDTH, (float)GROUND_HEIGHT }, Vector2{ 0, (float)WINDOW_HEIGHT - GROUND_HEIGHT }, WHITE);
	
	DrawText(TextFormat("Birds: %i", TOTAL_BIRDS - DEAD_BIRDS), WINDOW_WIDTH - 250, 50, 30, WHITE);
	DrawText(TextFormat("Generation: %i", GENERATION), WINDOW_WIDTH - 250, 80, 30, WHITE);
}

static void Finalize(void)
{
	Bird::Delete();
	Pipe::Delete();
	for (size_t i = 0; i < static_cast<int>(sizeof(tBird)/sizeof(tBird[0])); i++) {
		UnloadTexture(tBird[i]);
	}
	UnloadTexture(tPipe);
	UnloadTexture(tBackground);
	UnloadTexture(tGround);
}
