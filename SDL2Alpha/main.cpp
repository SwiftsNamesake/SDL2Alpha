/*
	
	NAME: SDL2Alpha
	DESC: 

	DATE: May 4 2014
	AUTH: Jonatan H Sundqvist

	===============================================================================================

	SPEC | 

	TODO | - Interaction (selecting and manipulating geometry, creating objects)

*/



//-------------------------------------------------------------------------------------------------
// Headers
//-------------------------------------------------------------------------------------------------
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <map>
#include <vector>

// My headers
#include "Texture.h"
#include "Geometry.h"
#include "Utilities.h"


using namespace Utilities;



//-------------------------------------------------------------------------------------------------
// Forward declarations
//-------------------------------------------------------------------------------------------------
void InitGL();
void SetViewport(int, int);
void Render();
void Animate();



//-------------------------------------------------------------------------------------------------
// Classes
//-------------------------------------------------------------------------------------------------
class Orchestra {
	
	typedef int Token;
	typedef std::map<Token, Mix_Music*> MusicBank;

	public:
	
	Orchestra() {

		//
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
			OutputDebugString(L"Failed to initialize mixer.\n");
		}

		this->sounds = MusicBank();

	}

	~Orchestra() {
		//
		Mix_CloseAudio();
	}
	

	Token loadMusic(const char* path) {

		//
		static int count = 0; // TODO: Better way to produce tokens (?)
		Mix_Music* sound = Mix_LoadMUS(path); // 

		if (sound == NULL) {
			OutputDebugString(L"Failed to load music.\n");
			return 0;
		} else {
			this->sounds[++count] = sound;
			return count;
		}

	
	}


	int playMusic(Token tok) {
		
		//
		auto iter = this->sounds.find(tok);

		if ((iter != this->sounds.end()) && (Mix_PlayMusic(iter->second, -1) != -1)) {
			//
			return 1;
		} else if (iter == this->sounds.end()) {
			OutputDebugString(L"Failed to play music (invalid token).\n");
			return 0;
		} else {
			OutputDebugString(L"Failed to play music (Mix_PlayMusic failed).\n");
			return 0;
		}

	}


	private:
	
	MusicBank sounds;

};



//-------------------------------------------------------------------------------------------------
// Globals
//-------------------------------------------------------------------------------------------------
SDL_Window* window;
SDL_GLContext context;
SDL_TimerID timerID;

//GLfloat light[] = { 10.5, 20.0, -6.0, 1.0 };
GLfloat light[] = { 0.0, 8.0, 5.0, 1.0 };

const int WIDTH	 = 720 * 1.4;
const int HEIGHT = 420 * 1.4;
const int FPS	 = 30;
bool running = true;

Geometry::GeometryState polygon(6, -0.12f, 1.3, -6.58f, 0.0f, 0.0f, 0.0f);
Geometry::GeometryState square(4, -0.12f, 1.3, -6.58f, 0.0f, 0.0f, 0.0f);
Geometry::GeometryState painting(4, 0.0f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f);

Geometry::Polygon interactive({ { 0.0f, 0.0f, 0.0f } });

Geometry::Camera camera;




//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
void InitGL() {

	//
	OutputDebugString(L"Initialising OpenGL.\n");

	// Background colour
	glShadeModel(GL_SMOOTH);					// Smooth shadows (?)
	glClearColor(0.04f, 0.32f, 0.55f, 0.0f);	// Background colour
	glClearDepth(1.0f);							// Something to do with the Z-buffer

	// Anti-aliasing
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	
	OutputDebugLine("Setting multi sample buffers: %s.", SDL_GetError());

	glHint(GL_POINT_SMOOTH, GL_NICEST);
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	OutputDebugLine("Enabling anti-aliasing: %s.", SDL_GetError());

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	//glEnable(GL_MULTISAMPLE);
	//glDisable(GL_MULTISAMPLE);

	// Depth-testing
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,)
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_TEST);

	// Load textures (moved to struct)
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 2);

	// Alpha-blending
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Illumination
	//glLightfv(GL_LIGHT0, GL_POSITION, light);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Verify that anti-aliasing is enabled
	int Buffers, Samples;
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &Buffers);
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &Samples);
	OutputDebugLine("buf = %d\nsamples = %d", Buffers, Samples);

}

void SetViewport(int width, int height) {
	GLfloat ratio;
	ratio = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Render() {

	glClearColor(0.04f, 0.32f, 0.55f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glTranslatef(-1.32f, 0.0f, -6.58f);

	// Triangle
	//prism(3, 0);

	//painting.applyTransformations();
	camera.applyTransformations();
	glLightfv(GL_LIGHT0, GL_POSITION, light);

	// Polygon
	//polygon.applyTransformations();
	/*
	glDisable(GL_LIGHTING);
	glTranslatef(4.0f, 6.0f, -7.0f);
	prism(polygon.sides, 0);
	glTranslatef(-4.0f, -6.0f, 7.0f);
	glEnable(GL_LIGHTING);
	*/

	// Draw axes
	Geometry::axes(light[0], light[1], light[2], 2.0f, 2.0f);
	Geometry::axes(0.0f, 0.0f, 0.0f, 2.0f, 2.0f);

	// Draw textured quad
	//glBindTexture(GL_TEXTURE_2D, textureIDs[texIndex]);
	glEnable(GL_TEXTURE_2D);

	Geometry::building();

	camera.applyTransformations();
	painting.applyTransformations();


	//interactive.render(); //polygon

	using namespace Texture;
	using namespace Geometry;

	Geometry::cube(Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::topgrass, Indices::dirt);

	glTranslatef(0.0f, Y+2.0f, 0.0f);
	cube(Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::topgrass, Indices::dirt);

	glTranslatef(0.0f, -(Y+2.0f), Y+2.0f);
	cube(Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::topgrass, Indices::dirt);

	glTranslatef(0.0f, 3.0f, 0.0f);
	cube(Indices::sidetable, Indices::sidetable, Indices::fronttable, Indices::sidetable, Indices::toptable, Indices::spruceplanks);
	
	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::oakplanks, Indices::oakplanks, Indices::oakplanks, Indices::junglesapling, Indices::oakplanks, Indices::oakplanks);
	
	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::glass, Indices::glass, Indices::glass, Indices::glass, Indices::glass, Indices::glass);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::pumpkinface, Indices::pumpkinface, Indices::pumpkinface, Indices::pumpkinface, Indices::pumpkintop, Indices::pumpkintop);
	
	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::cobble, Indices::cobble, Indices::cobble, Indices::cobble, Indices::cobble, Indices::cobble);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::brick, Indices::brick, Indices::brick, Indices::brick, Indices::brick, Indices::brick);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::smoothsandstone, Indices::smoothsandstone, Indices::smoothsandstone, Indices::smoothsandstone, Indices::smoothsandstone, Indices::smoothsandstone);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::redness, Indices::redness, Indices::redness, Indices::redness, Indices::redness, Indices::redness);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::birchplanks, Indices::birchplanks, Indices::birchplanks, Indices::birchplanks, Indices::birchplanks, Indices::birchplanks);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::jungleplanks, Indices::jungleplanks, Indices::jungleplanks, Indices::jungleplanks, Indices::jungleplanks, Indices::jungleplanks);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::crackedbrick, Indices::crackedbrick, Indices::crackedbrick, Indices::crackedbrick, Indices::crackedbrick, Indices::crackedbrick);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::diamond, Indices::diamond, Indices::diamond, Indices::diamond, Indices::diamond, Indices::diamond);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::sword, Indices::sword, Indices::sword, Indices::sword, Indices::sword, Indices::sword);

	glTranslatef(3.0f, 0.0f, 0.0f);
	cube(Indices::ice, Indices::ice, Indices::ice, Indices::ice, Indices::ice, Indices::ice);

	glTranslatef(-3.0f * 13, -3.0f, 0.0f);

	for (int i = 0; i < 20; ++i) {
		glTranslatef(2.0f, 0.0f, 0.0f);
		cube(Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::sidegrass, Indices::topgrass, Indices::dirt);
	}

	static float rY = 0.0f;
	rY += 5.0f;

	glTranslatef(Y+2.0f, 0.0f, -(Y+2.0f));
	glRotatef(rY, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f+sine(rY), 2.0f+cosine(rY), 2.0f+sine(rY));
	cube(Indices::sidespruce, Indices::sidespruce, Indices::sidespruce, Indices::sidespruce, Indices::topspruce, Indices::topspruce);

	glDisable(GL_TEXTURE_2D);


	SDL_GL_SwapWindow(window);

}

void Animate() {
	
	static float yRot = 0.0f;
	static float yRPS = 0.4f;

	static float dY = 0.08f;
	static int stills = 0;

	if (stills == 0) Y += dY;

	camera.X += dX; // Responds to arrow keys (Left/Right)
	camera.Z += dZ; // Responds to arrow keys (Up/Down)

	//if ((Y <= 0) || (Y >= 3.0f)) dY *= (-1.0f);

	if (Y <= 0) {
		stills++;
		if (stills > FPS*3) {
			dY *= (-1.0f);
			stills = 0;
		}
	} else if (Y >= 3.0f) {
		dY *= (-1.0f);
	}
	

	//painting.rY += yRPS * 360.0f / FPS;

}

Uint32 tick(Uint32 elapsed, void* data) {
	
	static int FRAMES = 0;

	if (SDL_GetTicks() > FRAMES*1000.0f / FPS) {
		FRAMES++;
		Animate();
		Render();
	}
	
	return (Uint32)0;

}



//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
//int disabled(int argc, char* args[]) {
int main(int argc, char* args[]) {

	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	window = SDL_CreateWindow("SDL Alpha", 40, 50, WIDTH, HEIGHT, SDL_WINDOW_OPENGL); // SDL_WINDOW_RESIZABLE
	context = SDL_GL_CreateContext(window);

	InitGL();
	SetViewport(WIDTH, HEIGHT);
	Render();

	// Load queued textures now that OpenGL is ready
	Texture::loadQueuedTextures();

	//
	timerID = SDL_AddTimer((Uint32)(1000.0 / FPS), tick, NULL);
	
	bool panning = false; // TODO: Move this somewhere (no scattered state)

	// SDL_mixer
	Orchestra orchestra;
	int rhapsody = orchestra.loadMusic("C:/Users/Jonatan/Music/HungarianRhapsody.wav");
	orchestra.playMusic(rhapsody);

	// Event loop
	while (running) {
		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					return 0;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = true;
							return 0;
						case SDLK_LEFT:
							Texture::texIndex = (Texture::texIndex == 0) ? Texture::texNum - 1 : Texture::texIndex - 1;
							dX = 0.2f;
							break;
						case SDLK_RIGHT:
							dX = -0.2f;
							Texture::texIndex = (Texture::texIndex == (Texture::texNum - 1)) ? 0 : Texture::texIndex + 1;
							break;
						case SDLK_UP:
							dZ = 0.2f;
							break;
						case SDLK_DOWN:
							dZ = -0.2f;
							break;
						case SDLK_SPACE:
							camera.rX = 0.0f;
							camera.rY = 0.0f;
							camera.rZ = 0.0f;
							camera.Z = -12.0f;
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
						case SDLK_RIGHT:
							dX = 0.0f;
							break;
						case SDLK_UP:
						case SDLK_DOWN:
							dZ = 0.0f;
							break;
						case SDLK_0:

							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					panning = (event.button.button == 1) ? true : panning;
					OutputDebugString(L"Adding vertex.\n");
					interactive.vertices.push_back({ event.motion.x/100, 0.0f, event.motion.y/100 });
					break;
				case SDL_MOUSEBUTTONUP:
					panning = (event.button.button == 1) ? false : panning;
					break;
				case SDL_MOUSEMOTION:
					polygon.sides = 3 + 10 * event.motion.x / WIDTH;
					polygon.rZ = 360.0f * event.motion.y / HEIGHT;
					if (panning) {
						camera.rX += 360.0f * (event.motion.yrel) / HEIGHT;
						camera.rY += 360.0f * (event.motion.xrel) / WIDTH;
						//painting.rY = 360.0f * (event.motion.x - WIDTH*0.5) / (WIDTH * 0.5);
						//painting.rX = 360.0f * (event.motion.y - HEIGHT*0.5) / (HEIGHT * 0.5);
					}
					dCentre = 5.0f * (event.motion.y - HEIGHT*0.5) / (HEIGHT * 0.5);
					break;
				case SDL_MOUSEWHEEL:
					camera.Z += 0.6f * event.wheel.y;
					break;
			}

			//OutputDebugLine("Event received: 0x%x", event.type);

		}

		tick(0, 0);

	}


	SDL_Quit();

	return 0;

}