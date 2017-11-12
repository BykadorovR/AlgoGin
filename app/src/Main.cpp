/*#include "Shader.h"
#include "MatrixHelper.h"
#include "math.h"

GLuint VBO, IBO;
GLint a_position;
GLint u_color;
GLuint u_world;
GLuint program;
const std::string vs_path = "../../engine/content/simple.vs";
const std::string fs_path = "../../engine/content/simple.fs";


static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUniform4f(u_color, 0.5f, 0.5f, 0.5f, 1);
	
	static float Scale = 0.0f;

	Scale += 0.0001f;

	MatrixHelper p;
	//p.setScale(Vector3f(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)));
	p.setPosition(Vector3f(sinf(Scale), 0.0f, 0.0f));
	p.setRotate(Vector3f(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f));

	glUniformMatrix4fv(u_world, 1, GL_TRUE, (const GLfloat*)p.getMatrix()[0]);

	glEnableVertexAttribArray(a_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(a_position);

	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[4];
	Vertices[0] = Vector3f(-.5f, -.5f, 0.0f);
	Vertices[1] = Vector3f(0.0f, -.5f, .5f);
	Vertices[2] = Vector3f(.5f, -.5f, 0.0f);
	Vertices[3] = Vector3f(0.0f, .5f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void CreateIndexBuffer()
{
	unsigned int Indices[] = 
	  { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 2, 1 };

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
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

	CreateVertexBuffer();
	CreateIndexBuffer();
	Shader simpleShader(vs_path, fs_path);
	simpleShader.compileShaders(); //once
	simpleShader.useProgram(); //in draw
	program = simpleShader.getProgram();
	
	a_position = glGetAttribLocation(program, "Position");
	u_color = glGetUniformLocation(program, "ResultColor");
	u_world = glGetUniformLocation(program, "gWorld");
	//TODO: add world matrix
	glutMainLoop();

	return 0;
}
*/
#include "NeuralNetwork.h"
const int nodesCount = 5;
int main() {
	Layer input(nodesCount, inputLayer);
	ActivationFunc firstLayer;
	input.InitNeurons(&firstLayer)
	//Create layer and say how many nodes in every layer
	//default function for all nodes and opportunity to change for 
	//every node. Call LayerBinder, it init all links between nodes
	//and after pass X and Y to LayerBinder
	return 0;
}