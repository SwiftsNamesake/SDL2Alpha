/*

NAME: Texture.h
DESC:

DATE: February 2 2015
AUTH: Jonatan H Sundqvist

===============================================================================================

SPEC |

TODO | - Resources header (?)

*/



//-------------------------------------------------------------------------------------------------
// We'll need these
//-------------------------------------------------------------------------------------------------
#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <gl/GLU.h>
#include <vector>
#include <string>

// My headers
#include "Utilities.h"

using namespace Utilities;

using std::vector;
using std::string;


//-------------------------------------------------------------------------------------------------
// Forward declarations
//-------------------------------------------------------------------------------------------------
namespace Texture {


// Classes
struct TextureArgs {
	string filename;
	GLint internalFormat;
	GLenum format;
	GLenum type;
	GLint minfiltering;
	GLint maxfiltering;
};


// Variables
const int texCount = 64;		// Maximum number of textures
GLuint textureIDs[texCount];	// Stores texture IDs

const double π = M_PI;

int texIndex = 0; //
int texNum = 2;   // What's this for? (cf. event loop; I think I'm using it for 'flicking' through textures)

vector<Texture::TextureArgs> queuedTextures; // Contains the arguments


// Functions
const string resourcePath(string);

int queueTexture(string, GLint, GLenum, GLenum, GLint, GLint);
int loadQueuedTextures();

int loadTexture(const char*, GLint, GLenum, GLenum, GLint, GLint);
int loadTexture(const char*, GLenum);
int loadTexture(const char*);
int displayTextureFormat(SDL_Surface*);
int deleteTextures();

// TODO: Query functions for textures (find, exists, bind, etc.) (?)


// Paths
namespace Strings {
	// Path
	string directory = "C:/Users/Jonatan/Desktop/Python/resources/images/";

	// Paintings
	const string monalisa   = resourcePath("paintings/texture.bmp");
	const string funky      = resourcePath("paintings/funkymona.png");
	const string riverbanks = resourcePath("paintings/cezanne.riverbanks.jpg");
	const string trainsmoke = resourcePath("paintings/train-smoke-1900.bmp");
	const string paris      = resourcePath("paintings/Chagall Paris - Tutt'Art@ (15).jpg");
	const string fiddler    = resourcePath("paintings/Image-Chagall_Fiddler.jpg");
	const string flowers    = resourcePath("paintings/jmgc25-wedding-flowers-in-the-style-of-marc-chagall-r1.jpg");
	const string victoire   = resourcePath("paintings/mont-sainte-victoire-3.jpg");
	const string munch      = resourcePath("paintings/Munch.jpg");
	const string marti      = resourcePath("paintings/ploaia_marti_19.jpg");
	const string chateau    = resourcePath("paintings/the-chateau-de-medan.jpg");
	const string wheatfield = resourcePath("paintings/Vincent_van_Gogh_(1853-1890)_-_Wheat_Field_with_Crows_(1890).jpg");

	// Minecraft
	const string dirt      = resourcePath("minecraft/dirt.png");
	const string sidegrass = resourcePath("minecraft/grass_side.png");
	const string topgrass  = resourcePath("minecraft/grass_top_green.png");
	const string greygrass = resourcePath("minecraft/grass_top_grey.png");

	const string sidespruce = resourcePath("minecraft/log_spruce.png");
	const string topspruce  = resourcePath("minecraft/log_spruce_top.png");

	const string sidetable  = resourcePath("minecraft/crafting_table_side.png");
	const string toptable   = resourcePath("minecraft/crafting_table_top.png");
	const string fronttable = resourcePath("minecraft/crafting_table_front.png");

	const string crackedbrick = resourcePath("minecraft/stonebrick_cracked.png");
	const string brick        = resourcePath("minecraft/stonebrick.png");
	const string cobble       = resourcePath("minecraft/cobblestone.png");
	const string smoothsandstone = resourcePath("minecraft/sandstone_smooth.png");

	const string birchplanks  = resourcePath("minecraft/planks_birch.png");
	const string jungleplanks = resourcePath("minecraft/planks_jungle.png");
	const string oakplanks    = resourcePath("minecraft/planks_oak.png");
	const string spruceplanks = resourcePath("minecraft/planks_spruce.png");

	const string junglesapling = resourcePath("minecraft/sapling_jungle.png");

	const string pumpkinface = resourcePath("minecraft/pumpkin_face_on.png");
	const string pumpkintop  = resourcePath("minecraft/pumpkin_top.png");

	const string glass = resourcePath("minecraft/glass_blue.png");
	const string ice  = resourcePath("minecraft/ice.png");

	const string diamond = resourcePath("minecraft/diamond_block.png");

	const string sword = resourcePath("minecraft/diamond_sword.png");

	// Custom
	const string redness = resourcePath("minecraft/redness.png");

};


// Texture indices
namespace Indices {

	// Paintings
	int monalisa	= queueTexture(Strings::monalisa, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int funky		= queueTexture(Strings::funky, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int riverbanks	= queueTexture(Strings::riverbanks, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int trainsmoke	= queueTexture(Strings::trainsmoke, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int paris		= queueTexture(Strings::paris, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int fiddler		= queueTexture(Strings::fiddler, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int flowers		= queueTexture(Strings::flowers, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int victoire	= queueTexture(Strings::victoire, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int munch		= queueTexture(Strings::munch, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int marti		= queueTexture(Strings::marti, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int chateau		= queueTexture(Strings::chateau, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int wheatfield	= queueTexture(Strings::wheatfield, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	// Minecraft
	//, GL_RGBA, format, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR
	int dirt		= queueTexture(Strings::dirt, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int sidegrass	= queueTexture(Strings::sidegrass, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int topgrass	= queueTexture(Strings::topgrass, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int greygrass	= queueTexture(Strings::greygrass, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int sidespruce = queueTexture(Strings::sidespruce, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int topspruce	= queueTexture(Strings::topspruce, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int toptable	= queueTexture(Strings::toptable, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int sidetable	= queueTexture(Strings::sidetable, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int fronttable	= queueTexture(Strings::fronttable, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int crackedbrick	= queueTexture(Strings::crackedbrick, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int brick			= queueTexture(Strings::brick, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int cobble			= queueTexture(Strings::cobble, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int smoothsandstone = queueTexture(Strings::smoothsandstone, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int birchplanks		= queueTexture(Strings::birchplanks, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int jungleplanks	= queueTexture(Strings::jungleplanks, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int oakplanks		= queueTexture(Strings::oakplanks, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int spruceplanks	= queueTexture(Strings::spruceplanks, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int junglesapling = queueTexture(Strings::junglesapling, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int pumpkinface = queueTexture(Strings::pumpkinface, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int pumpkintop	= queueTexture(Strings::pumpkintop, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int glass	= queueTexture(Strings::glass, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);
	int ice		= queueTexture(Strings::ice, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int diamond = queueTexture(Strings::diamond, GL_RGBA, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	int sword = queueTexture(Strings::sword, GL_RGBA, GL_BGR_EXT, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);

	// Custom
	int redness = queueTexture(Strings::redness, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR);


};


}



//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
const string Texture::resourcePath(string fn) {
	// Constructs the full path to a texture resource
	// TODO: Avoid hard-coding max length (?)
	using namespace Texture;
	return Strings::directory + fn;
	//return strcat(strcpy(new char[strlen(Strings::directory) + strlen(fn) + 1], Strings::directory), fn);
}



int Texture::displayTextureFormat(SDL_Surface* surface) {

	//
	SDL_PixelFormat* format = surface->format;

	OutputDebugLine("\nImage Format");
	OutputDebugLine("Width: %d\nHeight: %d", surface->w, surface->h);
	OutputDebugLine("Bit depth: %d", format->BitsPerPixel);
	OutputDebugLine("Format: %s", SDL_GetPixelFormatName(format->format));
	OutputDebugLine("Padding: {%d, %d}", format->padding[0], format->padding[1]);
	OutputDebugLine("Alpha mask: %d", format->Amask);
	OutputDebugLine("\n");

	return 0;

}




int Texture::queueTexture(const string filename, GLint internalFormat, GLenum format, GLenum type, GLint minfiltering, GLint maxfiltering) {

	// TODO: Coupling between this function and loadTexture
	// TODO: Handle errors (indirectly, since we can't detect errors until we invoke Texture::loadTexture)
	// TODO: Rename (?)

	// This function is necessary if we want to declare a namespace of texture indeces and initialize it statically. The alternative (which I resorted to originally)
	// is to create a separate function or constructor (incuring a lot of duplication) which initializes each member once OpenGL is ready for business.
	static int count = 0;

	// TODO: Vector of structs? Move semantics? Is this the best way to do it?

	Texture::queuedTextures.push_back({
		filename,
		internalFormat,
		format,
		type,
		minfiltering,
		maxfiltering
	});

	return count++;

}


int Texture::loadQueuedTextures() {

	//
	// TODO: Flag indicating whether queued textures have been processed (?)
	// TODO: Deal with overloads of Texture::loadTexture (?)
	for (Texture::TextureArgs& args : Texture::queuedTextures) {
		Texture::loadTexture(args.filename.c_str(), args.internalFormat, args.format, args.type, args.minfiltering, args.maxfiltering);
	}

	return 0;

}


int Texture::loadTexture(const char* filename, GLint internalFormat, GLenum format, GLenum type, GLint minfiltering, GLint maxfiltering) {

	//
	// Returns index for the created index (or a negative number for errors)
	// TODO: Detect if OpenGL hasn't been initialised yet.

	static int count = 0; // Number of previously initialized textures

	/*
	if (!SDL_WasInit(SDL_INIT_EVERYTHING)) {
		// TODO: We shouldn't have to init everything to load textures, should we?
		// TODO: Is it safe to initialize SDL more than once?
		OutputDebugString(L"Making sure SDL is initalized before we load a texture.\n");
		SDL_Init(SDL_INIT_EVERYTHING);
	};
	*/

	OutputDebugLine("Loading texture: %s", filename);

	if (count == 0) {
		OutputDebugLine("Generating textures.");
		glGenTextures(texCount, textureIDs);
	} else if (count >= texCount) {
		OutputDebugLine("No more textures can be created.");
		return -1;
	}

	OutputDebugLine("Loading texture number %d.", count);
	SDL_Surface* data = IMG_Load(filename);

	if (data == NULL) {
		OutputDebugLine("Failed to load image %s: ", filename, SDL_GetError());
		SDL_FreeSurface(data);
		return -1;
	}

	//SDL_CreateTextureFromSurface();
	glBindTexture(GL_TEXTURE_2D, textureIDs[count]);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data->w, data->h, 0, format, type, data->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxfiltering);

	SDL_FreeSurface(data);

	count++;
	texNum++;

	return count - 1;
	//return 0;

}

int Texture::loadTexture(const char* filename) { return Texture::loadTexture(filename, GL_RGBA, GL_BGR, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR); }

int Texture::loadTexture(const char* filename, GLenum format) { return Texture::loadTexture(filename); }

int Texture::deleteTextures() {
	glDeleteTextures(texCount, textureIDs);
	return 0;
}



//-------------------------------------------------------------------------------------------------
// Classes
//-------------------------------------------------------------------------------------------------
/*
struct Texture::TextureArgs {
	string filename;
	GLint internalFormat;
	GLenum format;
	GLenum type;
	GLint minfiltering;
	GLint maxfiltering;
};
*/