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

GLuint VBO, IBO;
GLuint a_position;
GLuint u_color;
GLuint a_texcoord;
GLuint u_world;
GLuint program;
GLuint gSampler;
SpritesHandler* spr = NULL;
Texture* pTexture = NULL;
Texture* texture0 = NULL;
Texture* texture1 = NULL;

const std::string vs_path = "../../engine/content/simple.vs";
const std::string fs_path = "../../engine/content/simple.fs";
const std::string hudvs_path = "../../engine/content/hudshader.vs";

Shader* simpleShader = new Shader(vs_path, fs_path);
Shader* hudShader = new Shader(hudvs_path, fs_path);

Camera cam = Camera(1024.0f, 768.0f, 90.0f, 0.001f, 1000.0f, Vector3f(0.0f, 0.0f, 1.5f), Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f));

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//glUniform4f(u_color, 0.5f, 0.5f, 0.5f, 1);
	
	static float Scale = 0.0f;

	Scale += 0.0004f;

	MatrixHelper p;
	//p.setScale(Vector3f(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)));
	p.setScale(Vector3f(0.8f, 0.8f, 0.8f));
	p.setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	p.setRotate(Vector3f(Scale*340, Scale*201, Scale*444));
	//p.setPerspective(90.0f, 1024.0f, 768.0f, 0.001f, 1000.0f);

	simpleShader->useProgram();
	gSampler = glGetUniformLocation(simpleShader->getProgram(), "gSampler");
	glUniform1i(gSampler, 0);
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


static void SpecialKeyboardCB(int Key, int x, int y)
{
	const float STEPSCALE = -0.05f;
	Vector3f newpos = cam.getPosition();
	Vector3f target = cam.getTarget();

	switch (Key) {
	case GLUT_KEY_UP:
	{
		Vector3f Forw = target;
		Forw.y = 0;
		Forw.Normalize();
		Forw *= STEPSCALE;
		newpos.x += Forw.x;
		newpos.z += Forw.z;
	}
	break;
	case GLUT_KEY_DOWN:
	{
		Vector3f Backw = target;
		Backw.y = 0;
		Backw.Normalize();
		Backw *= STEPSCALE;
		newpos.x -= Backw.x;
		newpos.z -= Backw.z;
	}
	break;
	case GLUT_KEY_LEFT:
	{
		Vector3f Left = target.Cross(Vector3f(0.0f , 1.0f, 0.0f));
		Left.y = 0;
		Left.Normalize();
		Left *= STEPSCALE;
		newpos.x += Left.x;
		newpos.z += Left.z;
	}
	break;
	case GLUT_KEY_RIGHT:
	{
		Vector3f Right = Vector3f(0.0f, 1.0f, 0.0f).Cross(target);
		Right.y = 0;
		Right.Normalize();
		Right *= STEPSCALE;
		newpos.x += Right.x;
		newpos.z += Right.z;
	}
	break;
	}
	cam.setPosition(newpos.x, newpos.y, newpos.z);
}


static void KeyboardCB(unsigned char Key, int x, int y)
{
	switch (Key) {
	case 27:
		exit(0);
	}
}

static void PassiveMouseCB(int x, int y)
{
	cam.OnMouse(x, y);
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutSpecialFunc(SpecialKeyboardCB);
	glutPassiveMotionFunc(PassiveMouseCB);
	glutKeyboardFunc(KeyboardCB);
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

	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(cam.getWidth()/2, cam.getHeight()/2);

	InitializeGlutCallbacks();

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CreateVertexBuffer();
	CreateIndexBuffer();

	simpleShader->compileShaders(); //once
	hudShader->compileShaders(); //once
	simpleShader->useProgram(); //in draw

	program = simpleShader->getProgram();

	a_position = glGetAttribLocation(program, "Position");
	a_texcoord = glGetAttribLocation(program, "TexCoord");
	u_world = glGetUniformLocation(program, "gWorld");

	pTexture = new Texture("../resources/claytile.png", 0);
	if (!pTexture->Load()) {
		return 1;
	}
	texture0 = new Texture("../resources/alphatest.png", 1);
	if (!texture0->Load()) {
		return 1;
	}
	texture1 = new Texture("../resources/wood.png", 2);
	if (!texture1->Load()) {
		return 1;
	}
	pTexture->Bind();
	texture0->Bind();
	texture1->Bind();
	
	spr = new SpritesHandler(simpleShader, hudShader, Vector2f(1,1));
	spr->CreateSprite(1.5f, 2, 0, 0, 1, texture1);
	spr->CreateHUDSprite(300, 300, 200, 200, Vector2f(200, 200), Vector2f(2400, 2400), texture1);
	spr->CreateHUDSprite(300, 300, 520, 200, texture0);
	spr->CreateHUDSprite(300, 300, 840, 200, Vector2f(0, 0), Vector2f(50, 50), texture0);
	spr->GetHUDSprite(0)->SetRotation(0.0, 0.0, 45.0);
	spr->GetHUDSprite(1)->SetRotation(0.0, 0.0, 45.0);
	//TODO: add world matrix

	glutMainLoop();

	return 0;
}