#include "headers/Bird.h"

Bird *Bird::Birds = new Bird[TOTAL_BIRDS];
float FrameTime;
unsigned short Bird_Frame;
int MAX_RANGE = 1000;
float range[3];

std::uniform_int_distribution<int>  dist_birdX(0, WINDOW_WIDTH / 2);
std::uniform_int_distribution<int> dist_birdY(0, WINDOW_HEIGHT - GROUND_HEIGHT - BIRD_HEIGHT - 100);
std::uniform_int_distribution<int>  dist_birdSprite(0, 6);
std::uniform_real_distribution<float> dist_weights(-MAX_RANGE, MAX_RANGE);

Bird::Bird(void) :
	x				(dist_birdX(mt)),
	y				(dist_birdY(mt)),
	sprite			(dist_birdSprite(mt)),
	jump			(false),
	isDead			(false),
	verticalSpeed	(0),
	pipeColision	(0),
	score			(0)
{}

void Bird::Delete(void)
{
	delete[] Birds;
}

void Bird::Init(void)
{
	DEAD_BIRDS = 0;
	GENERATION++;

	if (GENERATION == 1)
	{
		for (unsigned int i = 0; i < TOTAL_BIRDS; i++)
		{
			Birds[i] = Bird();
			for (int j = 0; j < 3; j++)
				Birds[i].weights[j] = dist_weights(mt);
		}
	}
	else
	{
		std::sort(Birds, Birds + TOTAL_BIRDS, Bird());

		range[0] = std::abs(Birds[0].weights[0]);
		range[1] = std::abs(Birds[0].weights[1]);
		range[2] = std::abs(Birds[0].weights[2]);

		std::uniform_real_distribution<float> dist_weights_0(-(range[0] + (MAX_RANGE / GENERATION), range[0] + (MAX_RANGE / GENERATION)));
		std::uniform_real_distribution<float> dist_weights_1(-(range[1] + (MAX_RANGE / GENERATION), range[1] + (MAX_RANGE / GENERATION)));
		std::uniform_real_distribution<float> dist_weights_2(-(range[2] + (MAX_RANGE / GENERATION), range[2] + (MAX_RANGE / GENERATION)));

		for (unsigned int i = 0; i < TOTAL_BIRDS; i++)
		{
			Birds[i] = Bird();
			if (i % 2 == 0)
			{
				Birds[i].weights[0] = dist_weights_0(mt);
				Birds[i].weights[1] = dist_weights_1(mt);
				Birds[i].weights[2] = dist_weights_2(mt);
			}
			else
				for (int j = 0; j < 3; j++)
					Birds[i].weights[j] = dist_weights(mt);
		}
	}
}

void Bird::Update(void)
{
	FrameTime += GetFrameTime();
	if (FrameTime > 0.1f)
	{
		Bird_Frame++;
		FrameTime = 0;
		if (Bird_Frame == BIRD_MAXFRAME)
			Bird_Frame = 0;
	}

	for (unsigned int i = 0; i < TOTAL_BIRDS; i++)
	{
		if (!Birds[i].isDead)
		{
			if (!Birds[i].jump)
			{
				float total = 0;

				Birds[i].x_distance = Pipes[Birds[i].pipeColision].x - (Birds[i].x + BIRD_WIDTH);
				Birds[i].y_distance[0] = (Pipes[Birds[i].pipeColision].height) - Birds[i].y;
				Birds[i].y_distance[1] = (Pipes[Birds[i].pipeColision].height + PIPE_IDENT) - Birds[i].y;

				total = Birds[i].x_distance * Birds[i].weights[0];
				total += Birds[i].y_distance[0] * Birds[i].weights[1];
				total += Birds[i].y_distance[1] * Birds[i].weights[2];

				if (total > 0)
					Birds[i].jump = true;
			}

			//Update Pos

			if (Birds[i].jump && Birds[i].verticalSpeed > FLAP_SPEED)
				Birds[i].verticalSpeed = FLAP_SPEED;
			else {
				Birds[i].jump = false;
				Birds[i].verticalSpeed += GRAVITY;
			}

			Birds[i].y += Birds[i].verticalSpeed;
			Birds[i].rotate = Birds[i].verticalSpeed * 2.5f;

			//Colisions
			if ((Birds[i].x + BIRD_WIDTH > Pipes[Birds[i].pipeColision].x && Birds[i].x < Pipes[Birds[i].pipeColision].x + PIPE_WIDTH   //btw 
				&& 
				((Birds[i].y < Pipes[Birds[i].pipeColision].height) // up
				||
				Birds[i].y + BIRD_HEIGHT > Pipes[Birds[i].pipeColision].height + PIPE_IDENT)) // down

				|| (Birds[i].y + BIRD_HEIGHT > WINDOW_HEIGHT - GROUND_HEIGHT) // Ground
				|| (Birds[i].y < 0)) // Sky
			{
				Birds[i].isDead = true;
				DEAD_BIRDS++;
			}

			//Change Pipe colision
			if (Birds[i].x > Pipes[Birds[i].pipeColision].x + PIPE_WIDTH - 20)
			{
				Birds[i].pipeColision++;

				if (Birds[i].pipeColision == MAX_PIPES)
						Birds[i].pipeColision = 0;
			}
			Birds[i].score++;
		}   
		else if (Birds[i].x > -BIRD_WIDTH)
		{
				
			if (Birds[i].y + BIRD_HEIGHT < WINDOW_HEIGHT - GROUND_HEIGHT)
			{
				Birds[i].y += Birds[i].verticalSpeed;
				Birds[i].verticalSpeed += GRAVITY;
				Birds[i].rotate = Birds[i].verticalSpeed * 4;
			}
			Birds[i].x -= MapVel + 0.2f;
		}

	}
	if (DEAD_BIRDS == TOTAL_BIRDS)
	{
		Bird::Init();
		Pipe::Init();
	}
}

void Bird::DrawBirds(void)
{
	for (unsigned int i = 0; i < TOTAL_BIRDS; i++)
	{
		if (Birds[i].x > -BIRD_WIDTH)
		{
#ifdef BIRD_SHOW_COLISION
			DrawRectanglePro(Rectangle{ (float)Birds[i].x ,(float)Birds[i].y + Birds[i].rotate , (float)BIRD_WIDTH, (float)BIRD_HEIGHT }, Vector2{ 0,0 }, 0, RED);
#endif		
			DrawTexturePro(tBird[Birds[i].sprite], Rectangle{float(Bird_Frame * BIRD_WIDTH),0, (float)BIRD_WIDTH, (float)BIRD_HEIGHT}, Rectangle{(float)Birds[i].x + Birds[i].rotate, (float)Birds[i].y, (float)BIRD_WIDTH, (float)BIRD_HEIGHT}, Vector2{ 0, 0 }, Birds[i].rotate, WHITE);
		}
		else
			DrawTexturePro(tBird[Birds[i].sprite], Rectangle{ float(Bird_Frame * BIRD_WIDTH),0, (float)BIRD_WIDTH, (float)BIRD_HEIGHT }, Rectangle{ (float)Birds[i].x + Birds[i].rotate, (float)Birds[i].y, (float)BIRD_WIDTH, (float)BIRD_HEIGHT }, Vector2{ 0, 0 }, Birds[i].rotate, WHITE);
	}
}
