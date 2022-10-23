#include <raylib.h>
#include <random>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
//------------------------------------------------------------------------------------------------------------------------------
extern float		  GRAVITY;
extern unsigned short MapVel;
extern unsigned int   GENERATION;
//------------------------------------------------------------------------------------------------------------------------------
//Bird
extern float		  FLAP_SPEED;
extern unsigned int   TOTAL_BIRDS;
extern unsigned short BIRD_WIDTH;
extern unsigned short BIRD_HEIGHT;
extern unsigned short BIRD_MAXFRAME;
extern unsigned int   GENERATION;
extern unsigned int   DEAD_BIRDS;
//#define BIRD_SHOW_COLISION
//------------------------------------------------------------------------------------------------------------------------------
//Pipes
extern unsigned short MAX_PIPES;
extern unsigned short PIPE_IDENT;
extern unsigned short PIPE_DISTANCE;
extern unsigned short PIPE_WIDTH;
extern unsigned short PIPE_HEIGHT;
#define PIPE_MOVE
//------------------------------------------------------------------------------------------------------------------------------
//Background
extern unsigned short BACKGROUND_WIDTH;
extern unsigned short BACKGROUND_HEIGHT;
//------------------------------------------------------------------------------------------------------------------------------
//Ground
extern unsigned short GROUND_WIDTH;
extern unsigned short GROUND_HEIGHT;
//------------------------------------------------------------------------------------------------------------------------------
//Textures
extern Texture2D tBird[7];
extern Texture2D tPipe; 
extern Texture2D tBackground;
extern Texture2D tGround;
//------------------------------------------------------------------------------------------------------------------------------
//Ramdom
extern std::random_device rd;
extern std::mt19937_64 mt;
