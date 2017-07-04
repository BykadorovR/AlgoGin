#include "Primitives.h"
#include "Shader.h"

GLuint VBO;
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

	glEnableVertexAttribArray(a_position);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(a_position);

	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(.0f, .0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, .0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
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
	Shader simpleShader(vs_path, fs_path);
	simpleShader.compileShaders(); //once
	simpleShader.useProgram(); //in draw
	program = simpleShader.getProgram();
	
	a_position = glGetAttribLocation(program, "Position");
	u_color = glGetUniformLocation(program, "ResultColor");
	//TODO: add world matrix
	glutMainLoop();

	return 0;
}