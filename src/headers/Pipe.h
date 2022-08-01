#ifndef CLASS_PIPE_H
#define CLASS_PIPE_H

#include "Global.h"

class Pipe
{
	public:

		static void Init(void);
		static void Update(void);
		static void Draw(void);
		static void Delete(void);

	public:

		float x;
		float height;
		bool direction;
		static Pipe* Pipes;	Pipe();
};

#endif