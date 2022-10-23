#include "headers/Pipe.h"

Pipe *Pipe::Pipes = new Pipe[MAX_PIPES];
unsigned short last, index;

std::uniform_int_distribution<int> dist_pipe_height(64, WINDOW_HEIGHT - GROUND_HEIGHT - 64 * 3 - PIPE_IDENT);
std::uniform_int_distribution<int> dist_pipe_direction(0, 1);

Pipe::Pipe(void)
: x(0)
{}

void Pipe::Delete(void)
{
	delete[] Pipes;
}

void Pipe::Init(void)
{
	for (int i = 0; i < MAX_PIPES ; i++)
	{
		Pipes[i] = Pipe();

		if (i == 0)
			Pipes[i].x = WINDOW_WIDTH - 200;
		else
			Pipes[i].x = Pipes[i - 1].x + PIPE_DISTANCE;

		Pipes[i].height = dist_pipe_height(mt);
		Pipes[i].direction = dist_pipe_direction(mt);
		
	}
	index = MAX_PIPES - 1;
}

void Pipe::Update(void)
{
	for (int i = 0; i < MAX_PIPES; i++)
	{
		Pipes[i].x -= MapVel;

#ifdef PIPE_MOVE
		//Pipe up and down
		if (Pipes[i].direction)
			Pipes[i].height -= MapVel - 2.2f;

		else
			Pipes[i].height += MapVel - 2.2f;

		//Pipe colission with the map
		if (Pipes[i].height < 64)
			Pipes[i].direction = false;

		else if (Pipes[i].height > WINDOW_HEIGHT - GROUND_HEIGHT - 64 - PIPE_IDENT)
			Pipes[i].direction = true;
#endif
		//When Pipe goes outiside of map
		if (Pipes[i].x + PIPE_WIDTH < 0)
		{	
			last = Pipes[index].x;
			Pipes[i].x = last + PIPE_DISTANCE;
			Pipes[i].height = dist_pipe_height(mt);
			Pipes[i].direction = dist_pipe_direction(mt);

			index++;
			if (index == MAX_PIPES)
				index = 0;

			last = Pipes[i].x;
		}
	}
}

void Pipe::Draw(void)
{
	for (int i = 0; i < MAX_PIPES; i++)
	{

		DrawTextureRec(tPipe, Rectangle{ 0, 0, (float)PIPE_WIDTH, -(float)Pipes[i].height }, Vector2{ (float)Pipes[i].x, 0}, WHITE);
		DrawTextureRec(tPipe, Rectangle{ 0, 0, (float)PIPE_WIDTH, (float)WINDOW_HEIGHT }, Vector2{ (float)Pipes[i].x, (float)Pipes[i].height + PIPE_IDENT }, WHITE);
	}
}
