#include<iostream>
#include <windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"ShaderClass.h"
#include"VAOClass.h"
#include"VBOClass.h"
#include"EBOClass.h"

using namespace std;



int main()
{
	cout << "hello world" << endl;
	glfwInit();


	//tell which opengl version to use while creating window 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "test_window_title", NULL, NULL);
	if (window == NULL)
	{
		cout << "failed to cerate window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	const GLubyte* glVersion = glGetString(GL_VERSION);
	if (glVersion) {
		std::cout << "OpenGL Version: " << glVersion << std::endl;
	}
	else {
		std::cerr << "Failed to get OpenGL version" << std::endl;
	}


	//write the vertex data 
	float points01[] = {
		0.5f,  0.5f,1.0f,0.0f,0.0f,
		0.5f, -0.5f,0.0f,1.0f,0.0f,
	   -0.5f, -0.5f,1.0f,0.0f,1.0f,
		-0.5f, 0.5f,0.0f,0.0f,1.0f,
	};

	unsigned int indices[] =
	{
		0,
		1,
		2,
		0,
		2,
		3

	};

	//create vertex and fragment objs and bundle them into a shader program and activate it
	

	Shader shader("default.vert", "default.frag");

	VAO vao;
	vao.Bind();

	VBO vbo(points01,sizeof(points01));
	EBO ebo(indices,sizeof(indices));

	vao.Link(vbo, 0, 2, 5);
	vao.Link(vbo, 1, 3, 5);

	vbo.Unbind();
	ebo.Unbind();

	vao.Unbind();






	


	int wnd_closed = glfwWindowShouldClose(window);

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0, 0, 0, 1); 
		glClear(GL_COLOR_BUFFER_BIT);


		// Use the shader program
		shader.Activate();

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			cout << "OpenGL Error: " << error << endl;
		}
		else
		{
			cout << "triangle drawn successfully!" << endl;
		}




		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao.Delete();
	ebo.Delete();
	vbo.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}