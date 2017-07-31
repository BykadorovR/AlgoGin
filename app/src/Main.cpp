#include "Shader.h"
#include "math.h"
#include "Camera.h"
#include "Texture.h"
#include "Lighting.h"
#include "SpritesHandler.h"
#include <iostream>
#include <GL/glew.h>
#include "KeyboardControl.h"

#define FLAT false // 2d or 3d

int frame, currenttime, timebase;
GLuint VBO, IBO;
GLuint a_position;
GLuint a_position_shadow;
GLuint u_color;
GLuint a_texcoord;
GLuint a_normal;
GLuint u_world;
GLuint program;
GLuint gSampler;
SpritesHandler* spr = new SpritesHandler();
Lighting* lighting = new Lighting();
Texture* texture0 = NULL;
Texture* texture1 = NULL;
Texture* texture2 = NULL;
Texture* texture3 = NULL;
Texture* texture4 = NULL;

std::string vs_path;
std::string fs_path;
std::string hudvs_path;
std::string hudfs_path;
std::string shadowvs_path;
std::string shadowfs_path;

GLuint depthTexture;
GLuint FramebufferName = 0;

Shader* simpleShader;
Shader* hudShader;
Shader* shadowShader;

Camera* cam = new Camera(1024.0f, 768.0f, 90.0f, 0.001f, 1000.0f, Vector3f(0.0f, 0.0f, -1.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f));
Camera* lightcam = new Camera(1024.0f, 768.0f, 90.0f, 0.001f, 1000.0f, Vector3f(0.0f, 0.0f, 3.0f), Vector3f(1.0f, -1.0f, -1.0f), Vector3f(0.0f, 1.0f, 0.0f));

Matrix4f BiasMatrix;
Matrix4f lightBiasedMatrix;

KeyboardControl KC;

void MoveCam()
{
	const float STEPSCALE = 0.05f;
	Vector3f newpos = cam->getPosition();
	Vector3f target = cam->getTarget();
	//target.y = 0.0f; //comment this line to fly

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
		glUniform3f(glGetUniformLocation(program, "eyePos"), newpos.x, newpos.y, newpos.z);
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

static void CreateTetraBuffers()
{
	/*unsigned int Indices[] =
	{ 1, 3, 0,
	2, 3, 1,
	0, 3, 2,
	2, 1, 0 };*/
	unsigned int Indices[] =
	{ 0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11 };
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	Vertex Vertices[12] = {
		/*0	Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		1	Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		2	Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(0.0f, 0.5f)),
		3	Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(1.0f, 1.0f)),*/
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),

		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(0.0f, 0.5f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),

		Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(1.0f, 1.0f)),
		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(0.0f, 0.5f)),

		Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(0.0f, 0.5f)),
		Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f))
	};
	Matrix4f m;
	m.InitRotateTransform(0, currenttime/10, currenttime / 10);
	for (int i = 0; i < 12; i++)
	{
		Vertices[i].pos = m*Vertices[i].pos;
	}
	CalcNormals(Indices, 12, Vertices, 12);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}


bool ShadowMapBuffer(int width, int height)
{
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	glDrawBuffer(GL_NONE); // No color buffer is drawn to.
						   // Always check that our framebuffer is ok
	glActiveTexture(GL_TEXTURE0 + 15);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
}

static void InitGLContext()
{
	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
	}

	//glFrontFace(GL_CW); //front faces are initialized clockwise
	//glCullFace(GL_BACK); 
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glutSetCursor(GLUT_CURSOR_NONE); //hide cursor
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);//move cursor

	//========

	simpleShader = new Shader(vs_path, fs_path);
	hudShader = new Shader(hudvs_path, hudfs_path);
	shadowShader = new Shader(shadowvs_path, shadowfs_path);

	simpleShader->compileShaders(); //once
	hudShader->compileShaders(); //once
	shadowShader->compileShaders();

	simpleShader->useProgram(); //in draw
	program = simpleShader->getProgram();

	texture0 = new Texture("../resources/claytile.png", 0);
	texture1 = new Texture("../resources/metal.png", 1);
	texture2 = new Texture("../resources/animtest.png", 2);
	texture3 = new Texture("../resources/alphatest.png", 3);
	texture4 = new Texture("../resources/wood.png", 4);

	if (KC.Windowed())
	{
		ShadowMapBuffer(1024, 768); // Find out how to get window size and screen resolution
	}
	else
	{
		ShadowMapBuffer(1280, 1024);
	}

	texture0->Bind();
	texture1->Bind();
	texture2->Bind();
	texture3->Bind();
	texture4->Bind();

	spr->Init(simpleShader, hudShader, cam);
	lighting->InitLighting(simpleShader);

	glUniform3f(glGetUniformLocation(program, "eyePos"), cam->getPosition().x, cam->getPosition().y, cam->getPosition().z);
	//delete(Indices);
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

//========================================DRAWING========================================

void DrawShadowMap()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glClear(GL_DEPTH_BUFFER_BIT);

	shadowShader->useProgram();

	glUniformMatrix4fv(glGetUniformLocation(shadowShader->getProgram(), "lightWorld"), 1, GL_TRUE, (const GLfloat*)(lightcam->getCameraMatrix())[0]);

	glEnableVertexAttribArray(a_position_shadow);

	CreateTetraBuffers();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position_shadow, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position_shadow);

	spr->DrawSprites(shadowShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

}

void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (!FLAT) glEnable(GL_DEPTH_TEST);

	simpleShader->useProgram();
	gSampler = glGetUniformLocation(program, "gSampler");
	GLuint transp = glGetUniformLocation(program, "transparency");

	glUniform1i(gSampler, 0);
	glUniform1i(glGetUniformLocation(program, "shadowMap"), 15);
	glUniform1f(transp, 1.0f);

	MoveCam();
	glUniformMatrix4fv(u_world, 1, GL_TRUE, (const GLfloat*)(cam->getCameraMatrix())[0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "lightBiasedMatrix"), 1, GL_TRUE, (const GLfloat*)(lightBiasedMatrix)[0]);

	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);
	glEnableVertexAttribArray(a_normal);

	CreateTetraBuffers();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(a_normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);
	glDisableVertexAttribArray(a_normal);
	
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);

	spr->DrawSprites();
	if (!FLAT) glDisable(GL_DEPTH_TEST);
	spr->DrawHUD();
	if (!FLAT) glEnable(GL_DEPTH_TEST);
}

static void RenderSceneCB()
{
	countFPS();

	lighting->GetOmniLightSource(0)->SetPosition(6 * cosf(currenttime / 1000.0f), 1, 6 * sinf(currenttime / 1000.0f));
	lighting->GetOmniLightSource(1)->SetPosition(6 * cosf(currenttime / 1000.0f + 2 * M_PI / 3), 1, 6 * sinf(currenttime / 1000.0f + 2 * M_PI / 3));
	lighting->GetOmniLightSource(2)->SetPosition(6 * cosf(currenttime / 1000.0f + 4 * M_PI / 3), 1, 6 * sinf(currenttime / 1000.0f + 4 * M_PI / 3));
	lighting->GetDirectLightSource(0)->SetDirection(cosf(-currenttime / 2000.0f), -1, sinf(-currenttime / 2000.0f));
	lightcam->setTarget(cosf(-currenttime / 2000.0f), -1, sinf(-currenttime / 2000.0f));
	lightcam->MakeOrthogonal(14.0f);
	lightBiasedMatrix = BiasMatrix*lightcam->getCameraMatrix();

	lighting->Reposition(simpleShader);

	spr->GetSprite(0)->Rotate(0.0, 0.0, 1.0);
	//spr->GetHUDSprite(0)->Rotate(0.0, 1.0, 0.0);
	//spr->GetHUDSprite(0)->Scale(0.999, 1.0002);
	spr->GetHUDSprite(1)->Rotate(0.0, 0.0, -1.0);
	spr->GetSprite(0)->NextAnimationFrame(currenttime);
	spr->GetSprite(1)->NextAnimationFrame(currenttime);
	spr->GetHUDSprite(0)->NextAnimationFrame(currenttime);
	spr->GetSprite(2)->SetRotation(90, 0, 0);
	spr->GetSprite(3)->SetRotation(0, 90, 0);

	DrawShadowMap();

	DrawScene();

	glutSwapBuffers();
}

//========================================END========================================

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
	shadowvs_path = "../../engine/content/shadowmap.vs";
	shadowfs_path = "../../engine/content/shadowmap.fs";

	simpleShader = new Shader(vs_path, fs_path);
	hudShader = new Shader(hudvs_path, hudfs_path);
	shadowShader = new Shader(shadowvs_path, shadowfs_path);

	InitGLContext();

	a_position = glGetAttribLocation(program, "Position");
	a_position_shadow = glGetAttribLocation(shadowShader->getProgram(), "Position");
	a_texcoord = glGetAttribLocation(program, "TexCoord");
	a_normal = glGetAttribLocation(program, "Normal");
	u_world = glGetUniformLocation(program, "gWorld");

	spr->CreateSprite(2, 2, 1, 0, 1, texture2);
	spr->CreateSprite(2, 2, -1, 0, 2, texture4);
	spr->CreateSprite(30, 30, 0, -1.1, 0, Vector2f(0, 0), Vector2f(20000, 20000), texture4);
	spr->CreateSprite(2, 2, 6, 0, 3, texture3);
	//spr->CreateHUDSprite(300, 300, 200, 200, Vector2f(200, 200), Vector2f(2400, 2400), texture2);
	spr->CreateHUDSprite(0.5, 0.5, -cam->getRatio() + 0.3, 0.7, texture4);
	spr->CreateHUDSprite(0.5, 0.5, -cam->getRatio() + 0.3, -0.7, texture3);
	spr->CreateHUDSprite(0.5, 0.5, cam->getRatio() - 0.3, -0.7, Vector2f(0, 0), Vector2f(50, 50), texture1);
	//TODO: add world matrix
	spr->GetSprite(0)->MakeAnimated(5, 1);
	spr->GetSprite(1)->MakeAnimated(5, 5);
	spr->GetHUDSprite(0)->MakeAnimated(5, 5);
	int anim[] = { 0,1,2,3,4,3,2,1 };
	int anim1[] = { 0,1,2,3,4,5,6,7,8,9 };
	spr->GetSprite(0)->CreateAnimation(8, anim, 1000);
	spr->GetSprite(1)->CreateAnimation(10, anim1, 100);
	spr->GetHUDSprite(0)->CreateAnimation(8, anim1, 100);
	spr->GetSprite(0)->FollowCamera(true);
	spr->GetSprite(1)->FollowCamera(true);
	spr->GetHUDSprite(2)->SetTransparency(0.5f);

	lighting->AddOmniLightSource(Vector3f(0.5f, 0.5f, 0), Vector3f(5, 1, 3), false);
	lighting->AddOmniLightSource(Vector3f(0.5f, 0, 0.5f), Vector3f(-5, 1, 3), false);
	lighting->AddOmniLightSource(Vector3f(0, 0.5f, 0.5f), Vector3f(0, 1, -6), false);
	lighting->AddDirectLightSource(Vector3f(1, 1, 1), Vector3f(1, -1, -1), false);

	lighting->InitLighting(simpleShader);

	glUniform3f(glGetUniformLocation(program, "eyePos"), cam->getPosition().x, cam->getPosition().y, cam->getPosition().z);
	
	lightcam->MakeOrthogonal(10.0f);

	BiasMatrix.InitBiasMatrix();

	lightBiasedMatrix = BiasMatrix*lightcam->getCameraMatrix();

	glutMainLoop();
	return 0;
}
