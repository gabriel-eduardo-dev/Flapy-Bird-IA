#ifndef CLASS_BIRD_H
#define CLASS_BIRD_H

#include "Global.h"
#include "Pipe.h"
#include <algorithm> //sort
#include <cmath> //abs

class Bird : public Pipe
{
	public:

		static void Init(void);
		static void Update(void);
		static void DrawBirds(void);
		static void Delete(void);

		inline bool operator() (const Bird& a, const Bird& b)
		{
			return a.score > b.score;
		}

	private:

		Bird(void);

		static Bird* Birds;
		
		float x, y;
		unsigned short sprite;
		bool jump;
		bool isDead;
		float verticalSpeed;
		unsigned short pipeColision;
		unsigned long long int score;
		float rotate;
		float x_distance;
		float y_distance[2];
		float weights[3];
};

#endif