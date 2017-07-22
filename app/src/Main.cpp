#include "Shader.h"
#include "math.h"
#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <Texture.h>
#include <SpritesHandler.h>

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

const std::string vs_path = "../../engine/content/simple.vs";
const std::string fs_path = "../../engine/content/simple.fs";
const std::string hudvs_path = "../../engine/content/hudshader.vs";

Shader* simpleShader = new Shader(vs_path, fs_path);
Shader* hudShader = new Shader(hudvs_path, fs_path);

Camera cam = Camera(1024.0f, 768.0f, 90.0f, 0.001f, 1000.0f, Vector3f(0.0f, 0.0f, 1.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f));
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glUniform4f(u_color, 0.5f, 0.5f, 0.5f, 1);
	
	static float Scale = 0.0f;

	Scale += 0.0004f;

	/*MatrixHelper p;
	//p.setScale(Vector3f(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)));
	p.setScale(Vector3f(0.8f, 0.8f, 0.8f));
	p.setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	p.setRotate(Vector3f(Scale*340, Scale*201, Scale*444));
	//p.setPerspective(90.0f, 1024.0f, 768.0f, 0.001f, 1000.0f);*/

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
	spr->Get3DSprite(0)->Rotate(0.0, 0.0, 1.0);
	spr->GetHUDSprite(0)->Rotate(0.0, 0.0, -11.0);
	spr->GetHUDSprite(0)->Scale(1.0002, 0.999);
	spr->GetHUDSprite(1)->Rotate(0.0, 0.0, -1.0);
	spr->GetHUDSprite(2)->Rotate(0.0, 0.0, 1.0);

	spr->DrawSprites();
	spr->DrawHUD();

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
	case 27:
	{
		exit(0);
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
	case 27:
	{
		exit(0);
	}
	}
}

static void Keyboard_KeyDown(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 'w':
	{
		keyup = true;
		break;
	}
	case 's':
	{
		keydown = true;
		break;
	}
	case 'a':
	{
		keyleft = true;
		break;
	}
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
	case 'w':
	{
		keyup = false;
		break;
	}
	case 's':
	{
		keydown = false;
		break;
	}
	case 'a':
	{
		keyleft = false;
		break;
	}
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
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();
	CreateIndexBuffer();

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
	texture2 = new Texture("../resources/wood.png", 2);
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
	
	spr = new SpritesHandler(simpleShader, hudShader, Vector2f(1,1));
	spr->CreateSprite(1.5f, 2, 0, 0, 1, texture2);
	spr->CreateHUDSprite(300, 300, 200, 200, Vector2f(200, 200), Vector2f(2400, 2400), texture2);
	spr->CreateHUDSprite(300, 300, 520, 200, texture3);
	spr->CreateHUDSprite(300, 300, 840, 200, Vector2f(0, 0), Vector2f(50, 50), texture1);
	spr->GetHUDSprite(0)->SetRotation(0.0, 0.0, 45.0);
	spr->GetHUDSprite(1)->SetRotation(0.0, 0.0, 45.0);
	//TODO: add world matrix

	glutMainLoop();

	return 0;
}