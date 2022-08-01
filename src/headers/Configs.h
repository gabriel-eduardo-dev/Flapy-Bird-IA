#include <random>
#include <raylib.h>

int WINDOW_WIDTH  = 1440;
int WINDOW_HEIGHT = 900;
//------------------------------------------------------------------------------------------------------------------------------
float          GRAVITY     = 0.25f;
unsigned short MapVel	   = 3;
unsigned int   GENERATION  = 0;
float		   FRAME_RATE  = 60;
float		   FRAME_RATE2 = FRAME_RATE;
//------------------------------------------------------------------------------------------------------------------------------
//Bird
float		   FLAP_SPEED	 = -6.5f;
unsigned int   TOTAL_BIRDS	 = 5000;
unsigned short BIRD_WIDTH	 = 92; //don't touch
unsigned short BIRD_HEIGHT   = 63; //don't touch
unsigned short BIRD_MAXFRAME = 3;  //don't touch
unsigned int   DEAD_BIRDS	 = 0;
//------------------------------------------------------------------------------------------------------------------------------
//Pipes
unsigned short PIPE_WIDTH	 = 138; //don't touch
unsigned short PIPE_HEIGHT   = 793; //don't touch
unsigned short MAX_PIPES	 = 4;
unsigned short PIPE_IDENT    = BIRD_HEIGHT * 3.78f;
unsigned short PIPE_DISTANCE = PIPE_WIDTH  * 3;
//------------------------------------------------------------------------------------------------------------------------------
//Background
unsigned short BACKGROUND_POSX   = 0;
unsigned short BACKGROUND_WIDTH  = 768; //don't touch
unsigned short BACKGROUND_HEIGHT = 896; //don't touch
//------------------------------------------------------------------------------------------------------------------------------
//Ground
unsigned short GROUND_POSX   = 0;
unsigned short GROUND_WIDTH  = 768; //don't touch
unsigned short GROUND_HEIGHT = 128; //don't touch
//------------------------------------------------------------------------------------------------------------------------------
//Textures
Texture2D tBird[7], tPipe, tBackground, tGround;
//------------------------------------------------------------------------------------------------------------------------------
//Random
std::random_device rd;
std::mt19937_64 mt(rd());
