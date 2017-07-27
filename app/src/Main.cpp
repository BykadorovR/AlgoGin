#include "Shader.h"
#include "math.h"
#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <Texture.h>
#include <SpritesHandler.h>
#include "KeyboardControl.h"

#define FLAT false // 2d or 3d

bool windowed = true;
int frame, currenttime, timebase;
GLuint VBO, IBO;
GLuint a_position;
GLuint u_color;
GLuint a_texcoord;
GLuint u_world;
GLuint program;
GLuint gSampler;
SpritesHandler* spr = new SpritesHandler();
Texture* texture0 = NULL;
Texture* texture1 = NULL;
Texture* texture2 = NULL;
Texture* texture3 = NULL;
Texture* texture4 = NULL;

std::string vs_path;
std::string fs_path;
std::string hudvs_path;
std::string hudfs_path;

Shader* simpleShader;
Shader* hudShader;

Camera* cam = new Camera(1024.0f, 768.0f, 90.0f, 0.001f, 1000.0f, Vector3f(0.0f, 0.0f, -1.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f));
//Camera cam = Camera(1024.0f, 768.0f);
KeyboardControl KC;

static void InitializeGlutCallbacks();

void MoveCam()
{
	const float STEPSCALE = 0.05f;
	Vector3f newpos = cam->getPosition();
	Vector3f target = cam->getTarget();
	target.y = 0.0f; //comment this line to fly

	if (KC.KeyUp())
	{
		Vector3f Forw = target;
		Forw.Normalize();
		Forw *= STEPSCALE;
		newpos += Forw;
	}
	if (KC.KeyDown())
	{
		Vector3f Backw = target;
		Backw.Normalize();
		Backw *= STEPSCALE;
		newpos -= Backw;
	}
	if (KC.KeyLeft())
	{
		Vector3f Left = target.Cross(Vector3f(0.0f, 1.0f, 0.0f));
		Left.Normalize();
		Left *= STEPSCALE;
		newpos += Left;
	}
	if (KC.KeyRight())
	{
		Vector3f Right = Vector3f(0.0f, 1.0f, 0.0f).Cross(target);
		Right.Normalize();
		Right *= STEPSCALE;
		newpos += Right;
	}
	if (newpos != cam->getPosition())
	{
		cam->setPosition(newpos.x, newpos.y, newpos.z);
	}
}

static void PassiveMouseCB(int x, int y)
{
	if (x != (glutGet(GLUT_WINDOW_WIDTH) / 2) || y != (glutGet(GLUT_WINDOW_HEIGHT) / 2))
	{
		cam->rotate((x - glutGet(GLUT_WINDOW_WIDTH) / 2) * 0.001f, (y - glutGet(GLUT_WINDOW_HEIGHT) / 2) * 0.001f);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	}
}

static void SpecialKeyboard_KeyDown(int Key, int x, int y)
{
	KC.SpecialKeyboard_KeyDown(Key, x, y);
}

static void SpecialKeyboard_KeyUp(int Key, int x, int y)
{
	KC.SpecialKeyboard_KeyUp(Key, x, y);
}

static void Keyboard_KeyDown(unsigned char Key, int x, int y)
{
	KC.Keyboard_KeyDown(Key, x, y);
}

static void Keyboard_KeyUp(unsigned char Key, int x, int y)
{
	KC.Keyboard_KeyUp(Key, x, y);
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
	{ 1, 3, 0,
		2, 3, 1,
		0, 3, 2,
		2, 1, 0 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void InitGLContext()
{
	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}

	//glFrontFace(GL_CW); //front faces are initialized clockwise
	//glCullFace(GL_BACK); 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glutSetCursor(GLUT_CURSOR_NONE); //hide cursor
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);//move cursor

	CreateVertexBuffer();
	CreateIndexBuffer();

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
	texture1 = new Texture("../resources/metal.png", 1);
	texture2 = new Texture("../resources/animtest.png", 2);
	texture3 = new Texture("../resources/alphatest.png", 3);
	texture4 = new Texture("../resources/wood.png", 4);

	texture0->Bind();
	texture1->Bind();
	texture2->Bind();
	texture3->Bind();
	texture4->Bind();

	spr->Init(simpleShader, hudShader, cam);
}

void countFPS()
{
	frame++;
	//get the current time
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	//check if a second has passed
	if (currenttime - timebase > 1000)
	{
		std::string title = std::to_string(frame*1000.0 / (currenttime - timebase));
		glutSetWindowTitle(title.c_str());
		timebase += 1000;
		frame = 0;
	}
}

static void RenderSceneCB()
{
	countFPS();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!FLAT) glEnable(GL_DEPTH_TEST);

	simpleShader->useProgram();
	gSampler = glGetUniformLocation(simpleShader->getProgram(), "gSampler");
	GLuint transp = glGetUniformLocation(simpleShader->getProgram(), "transparency");
	glUniform1i(gSampler, 0);
	glUniform1f(transp, 1.0f);

	MoveCam();
	glUniformMatrix4fv(u_world, 1, GL_TRUE, (const GLfloat*)(cam->getCameraMatrix())[0]);

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);

	spr->GetSprite(0)->Rotate(0.0, 0.0, 1.0);
	spr->GetHUDSprite(0)->Rotate(0.0, 0.0, -11.0);
	spr->GetHUDSprite(0)->Scale(0.999, 1.0002);
	spr->GetHUDSprite(1)->Rotate(0.0, 0.0, -1.0);
	spr->GetSprite(0)->NextAnimationFrame(currenttime);
	spr->GetSprite(1)->NextAnimationFrame(currenttime);
	spr->GetHUDSprite(0)->NextAnimationFrame(currenttime);

	spr->DrawSprites();
	if (!FLAT) glDisable(GL_DEPTH_TEST);
	spr->DrawHUD();
	if (!FLAT) glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	ilInit();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 04");
	InitializeGlutCallbacks();

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

	InitGLContext();

	spr->CreateSprite(2, 2, 0, 0, 1, texture2);
	spr->CreateSprite(2, 2, 0, 0, 2, texture4);
	spr->CreateSprite(2, 2, 0, 0, 3, texture3);
	//spr->CreateHUDSprite(300, 300, 200, 200, Vector2f(200, 200), Vector2f(2400, 2400), texture2);
	spr->CreateHUDSprite(0.5, 0.5, -cam->getRatio() + 0.3, 0.7, texture2);
	spr->CreateHUDSprite(0.5, 0.5, -cam->getRatio() + 0.3, -0.7, texture3);
	spr->CreateHUDSprite(0.5, 0.5, cam->getRatio() - 0.3, -0.7, Vector2f(0, 0), Vector2f(50, 50), texture1);
	//TODO: add world matrix
	spr->GetSprite(0)->MakeAnimated(5, 1);
	spr->GetSprite(1)->MakeAnimated(5, 5);
	spr->GetHUDSprite(0)->MakeAnimated(5, 1);
	int anim[] = { 0,1,2,3,4,3,2,1 };
	int anim1[] = { 0,1,2,3,4,5,6,7,8,9 };
	spr->GetSprite(0)->CreateAnimation(8, anim, 1000);
	spr->GetSprite(1)->CreateAnimation(10, anim1, 100);
	spr->GetHUDSprite(0)->CreateAnimation(8, anim, 1000);
	spr->GetSprite(0)->FollowCamera(true);
	spr->GetSprite(1)->FollowCamera(true);
	spr->GetSprite(2)->SetTransparency(0.5f);
	spr->GetHUDSprite(2)->SetTransparency(0.5f);
	glutMainLoop();

	return 0;
}
