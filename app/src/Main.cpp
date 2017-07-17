#include "Shader.h"
#include "math.h"
#include <iostream>
#include <GL/glew.h>
#include <Texture.h>
#include <MatrixHelper.h>

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
Texture* pTexture = NULL;
Texture* texture0 = NULL;
Texture* texture1 = NULL;

const std::string vs_path = "../../engine/content/simple.vs";
const std::string fs_path = "../../engine/content/simple.fs";

Shader* simpleShader = new Shader(vs_path, fs_path);

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//glUniform4f(u_color, 0.5f, 0.5f, 0.5f, 1);
	
	static float Scale = 0.0f;

	Scale += 0.0024f;

	MatrixHelper p;
	//p.setScale(Vector3f(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)));
	p.setScale(Vector3f(0.8f, 0.8f, 0.8f));
	p.setPosition(Vector3f(0.0f, 0.0f, 0.0f));
	p.setRotate(Vector3f(Scale*340, Scale*201, Scale*444));

	glUniformMatrix4fv(u_world, 1, GL_TRUE, (const GLfloat*)p.getMatrix()[0]);
	
	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(a_texcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	pTexture->Bind();

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);
	glDisableVertexAttribArray(a_texcoord);

	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
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
	  { 0, 1, 3,
		1, 2, 3,
		2, 0, 3,
		1, 0, 2 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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

	// Must be done after glut is initialized!
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	CreateVertexBuffer();
	CreateIndexBuffer();

	simpleShader->compileShaders(); //once
	simpleShader->useProgram(); //in draw


	program = simpleShader->getProgram();

	gSampler = glGetUniformLocation(program, "gSampler");
	a_position = glGetAttribLocation(program, "Position");
	a_texcoord = glGetAttribLocation(program, "TexCoord");
	u_world = glGetUniformLocation(program, "gWorld");
	glUniform1i(gSampler, 0);

	pTexture = new Texture("../resources/claytile.png");
	if (!pTexture->Load()) {
		return 1;
	}
	texture0 = new Texture("../resources/metal.png");
	if (!texture0->Load()) {
		return 1;
	}
	texture1 = new Texture("../resources/wood.png");
	if (!texture1->Load()) {
		return 1;
	}

	//TODO: add world matrix

	glutMainLoop();

	return 0;
}