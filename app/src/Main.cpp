#include "Shader.h"
#include "math.h"
#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <Texture.h>
#include <SpritesHandler.h>

#define FLAT false // 2d or 3d

struct Vertex
{
	Vector3f m_pos;
	Vector2f m_tex;
	Vertex() {}
	Vertex(Vector3f pos, Vector2f tex)
	{
		m_pos = pos;
		m_tex = tex;
	}
};

bool keyup = false;
bool keydown = false;
bool keyleft = false;
bool keyright = false;

int animframe, frame, currenttime, timebase;
GLuint VBO, IBO;
GLuint a_position;
GLuint u_color;
GLuint a_texcoord;
GLuint u_world;
GLuint program;
GLuint gSampler;
SpritesHandler* spr = NULL;
Texture* texture0 = NULL;
Texture* texture1 = NULL;
Texture* texture2 = NULL;
Texture* texture3 = NULL;

std::string vs_path;
std::string fs_path;
std::string hudvs_path;
std::string hudfs_path;

Shader* simpleShader;
Shader* hudShader;

Camera cam = Camera(1024.0f, 768.0f, 90.0f, 0.001f, 1000.0f, Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f));
//Camera cam = Camera(1024.0f, 768.0f);
Vector2f screenCerter = Vector2f(cam.getWidth() / 2, cam.getHeight() / 2);

void MoveCam()
{
	const float STEPSCALE = -0.05f;
	Vector3f newpos = cam.getPosition();
	Vector3f target = cam.getTarget();
	target.y = 0.0f; //comment this line to fly

	if (keyup)
	{
		Vector3f Forw = target;
		Forw.Normalize();
		Forw *= STEPSCALE;
		newpos += Forw;
	}
	if (keydown)
	{
		Vector3f Backw = target;
		Backw.Normalize();
		Backw *= STEPSCALE;
		newpos -= Backw;
	}
	if (keyleft)
	{
		Vector3f Left = target.Cross(Vector3f(0.0f, 1.0f, 0.0f));
		Left.Normalize();
		Left *= STEPSCALE;
		newpos += Left;
	}
	if (keyright)
	{
		Vector3f Right = Vector3f(0.0f, 1.0f, 0.0f).Cross(target);
		Right.Normalize();
		Right *= STEPSCALE;
		newpos += Right;
	}
	if (newpos != cam.getPosition())
	{
		cam.setPosition(newpos.x, newpos.y, newpos.z);
	}
}


static void RenderSceneCB()
{
	frame++;
	//get the current time
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	//check if a second has passed
	if (currenttime - timebase > 1000)
	{
		std::string title = std::to_string(frame*1000.0 / (currenttime - timebase));
		glutSetWindowTitle(title.c_str());
		timebase = currenttime;
		frame = 0;
		animframe++;
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!FLAT) glEnable(GL_DEPTH_TEST);

	//glUniform4f(u_color, 0.5f, 0.5f, 0.5f, 1);

	simpleShader->useProgram();
	gSampler = glGetUniformLocation(simpleShader->getProgram(), "gSampler");
	glUniform1i(gSampler, 0);

	MoveCam();
	glUniformMatrix4fv(u_world, 1, GL_TRUE, (const GLfloat*)(cam.getCameraMatrix())[0]);

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);

	//spr->GetHUDSprite(2)->Translate(-1.0, 1.0, 0);
	spr->GetSprite(0)->Rotate(0.0, 0.0, 1.0);
	spr->GetHUDSprite(0)->Rotate(0.0, 0.0, -11.0);
	spr->GetHUDSprite(0)->Scale(0.999, 1.0002);
	spr->GetHUDSprite(1)->Rotate(0.0, 0.0, -1.0);
	spr->GetHUDSprite(2)->Rotate(0.0, 0.0, 1.0);

	spr->GetSprite(0)->SetAnimationFrame(animframe, 0);
	spr->GetSprite(1)->SetAnimationFrame(animframe, 0);
	spr->GetHUDSprite(0)->SetAnimationFrame(animframe, 0);

	spr->DrawSprites();
	if (!FLAT) glDisable(GL_DEPTH_TEST);
	spr->DrawHUD();
	if (!FLAT) glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

static void SpecialKeyboard_KeyDown(int Key, int x, int y)
{
	switch (Key)
	{
	case GLUT_KEY_UP:
	{
		keyup = true;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		keydown = true;
		break;
	}
	case GLUT_KEY_LEFT:
	{
		keyleft = true;
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		keyright = true;
		break;
	}
	}
}

static void SpecialKeyboard_KeyUp(int Key, int x, int y)
{
	switch (Key)
	{
	case GLUT_KEY_UP:
	{
		keyup = false;
		break;
	}
	case GLUT_KEY_DOWN:
	{
		keydown = false;
		break;
	}
	case GLUT_KEY_LEFT:
	{
		keyleft = false;
		break;
	}
	case GLUT_KEY_RIGHT:
	{
		keyright = false;
		break;
	}
	}
}

static void Keyboard_KeyDown(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'W':
	case 'w':
	{
		keyup = true;
		break;
	}
	case 'S':
	case 's':
	{
		keydown = true;
		break;
	}
	case 'A':
	case 'a':
	{
		keyleft = true;
		break;
	}
	case 'D':
	case 'd':
	{
		keyright = true;
		break;
	}
	case 27:
	{
		exit(0);
	}
	}
}

void Keyboard_KeyUp(unsigned char Key, int x, int y)
{
	switch (Key) {
	case 'W':
	case 'w':
	{
		keyup = false;
		break;
	}
	case 'S':
	case 's':
	{
		keydown = false;
		break;
	}
	case 'A':
	case 'a':
	{
		keyleft = false;
		break;
	}
	case 'D':
	case 'd':
	{
		keyright = false;
		break;
	}
	}
}

static void PassiveMouseCB(int x, int y)
{
	if (x != screenCerter.x || y != screenCerter.y)
	{
		cam.rotate((x - screenCerter.x) * 0.001f, (y - screenCerter.y) * 0.001f);
		glutWarpPointer(screenCerter.x, screenCerter.y);
	}
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutKeyboardFunc(Keyboard_KeyDown); // keys that generate ascii codes
	glutKeyboardUpFunc(Keyboard_KeyUp);
	glutSpecialFunc(SpecialKeyboard_KeyDown); // press arrows, f1-f12, home, pagedown, etc.
	glutSpecialUpFunc(SpecialKeyboard_KeyUp);
	glutPassiveMotionFunc(PassiveMouseCB);
}

static void CreateVertexBuffer()
{
	Vertex Vertices[4] = { 
		Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(0.0f, 0.5f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(1.0f, 1.0f)) };


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
	unsigned int Indices[] = 
	{	1, 3, 0,
		2, 3, 1,
		0, 3, 2,
		2, 1, 0 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	ilInit();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(cam.getWidth(), cam.getHeight());
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 04");

	glutSetCursor(GLUT_CURSOR_NONE); //hide cursor
	glutWarpPointer(cam.getWidth()/2, cam.getHeight()/2); //place cursor

	InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	glFrontFace(GL_CCW); //front faces are initialized counter clockwise
	//glCullFace(GL_BACK); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();
	CreateIndexBuffer();

	if (FLAT)
	{
		vs_path = "../../engine/content/sprites2d.vs";
		fs_path = "../../engine/content/sprites2d.fs";
	}
	else
	{
		vs_path = "../../engine/content/simple.vs";
		fs_path = "../../engine/content/simple.fs";
	}
	hudvs_path = "../../engine/content/hudshader.vs";
	hudfs_path = "../../engine/content/hudshader.fs";
	simpleShader = new Shader(vs_path, fs_path);
	hudShader = new Shader(hudvs_path, hudfs_path);

	simpleShader->compileShaders(); //once
	hudShader->compileShaders(); //once

	simpleShader->useProgram(); //in draw
	program = simpleShader->getProgram();
	a_position = glGetAttribLocation(program, "Position");
	a_texcoord = glGetAttribLocation(program, "TexCoord");
	u_world = glGetUniformLocation(program, "gWorld");

	texture0 = new Texture("../resources/claytile.png", 0);
	if (!texture0->Load()) {
		return 1;
	}
	texture1 = new Texture("../resources/metal.png", 1);
	if (!texture1->Load()) {
		return 1;
	}
	texture2 = new Texture("../resources/animtest.png", 2);
	if (!texture2->Load()) {
		return 1;
	}
	texture3 = new Texture("../resources/alphatest.png", 3);
	if (!texture3->Load()) {
		return 1;
	}
	texture0->Bind();
	texture1->Bind();
	texture2->Bind();
	texture3->Bind();
	
	spr = new SpritesHandler(simpleShader, hudShader, cam.getWidth(), cam.getHeight());
	spr->Create2DSprite(768, 768, 0, 384, 1, texture2);
	spr->Create2DSprite(768, 768, -256, 384, 3, texture2);
	spr->Create2DSprite(768, 768, 256, 384, 2, texture3);
	//spr->CreateHUDSprite(300, 300, 200, 200, Vector2f(200, 200), Vector2f(2400, 2400), texture2);
	spr->CreateHUDSprite(300, 300, 200, 200, texture2);
	spr->CreateHUDSprite(300, 300, 520, 200, texture3);
	spr->CreateHUDSprite(300, 300, 840, 200, Vector2f(0, 0), Vector2f(50, 50), texture1);
	spr->GetHUDSprite(0)->SetRotation(0.0, 0.0, 45.0);
	//spr->GetHUDSprite(1)->SetRotation(0.0, 0.0, 45.0);
	//TODO: add world matrix
	spr->GetSprite(0)->SetAnimation(5, 1);
	spr->GetSprite(1)->SetAnimation(5, 1);
	spr->GetHUDSprite(0)->SetAnimation(5, 1);

	glutMainLoop();

	return 0;
}