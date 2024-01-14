#include<iostream>
#include <windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"ShaderClass.h"
#include"VAOClass.h"
#include"VBOClass.h"
#include"EBOClass.h"
#include"TextureClass.h"
#include"STB/stb_image.h"

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
	float model01_points[] = {
		//position		//colors		//text coords
		0.5f,  0.5f,	1.0,1.0,0.0f,	1.0f,1.0f,
		0.5f, -0.5f,	1.0,0.0,0.0f,	1.0f,0.0f,
	   -0.5f, -0.5f,	0.0,0.0,1.0f,	0.0f, 0.0f,
	   -0.5f,  0.5f,	0.0,1.0,1.0f,	0.0f,1.0f
	};

	unsigned int model01_indices[] =
	{
		0,
		1,
		2,
		0,
		2,
		3
	};
	//write the vertex data 
	float model02_points[] = {
		//position		//colors		//text coords
		0.0f,  0.5f,	1.0,1.0,0.0f,	0.0f, 0.0f,
		0.5f, 0.0f,		1.0,0.0,0.0f,	1.0f,0.0f,
	   0.0f, -0.5f,		0.0,0.0,1.0f,	1.0f,1.0f,
	   -0.5f,  0.0f,	0.0,1.0,1.0f,	0.0f,1.0f
	};

	unsigned int model02_indices[] =
	{
		0,
		1,
		2,
		0,
		2,
		3
	};

	//create vertex and fragment objs and bundle them into a shader program and activate it
	

	
	unsigned int offset = 0;
	unsigned int stride = 7;

	//init textures for all the models

	//init texture_01
	TEXTURE texture_01("bridge.png");
	texture_01.setSlot(0); //activate slot 0 to write bridge image to slot 0
	texture_01.Bind_and_Write();

	//init vao for model 01
	VAO vao_01;
	VBO vbo_01(model01_points,sizeof(model01_points));
	EBO ebo_01(model01_indices, sizeof(model01_indices));
	offset = 0;
	vao_01.Link(vbo_01, 0, 2, stride, offset);
	offset = 2;
	vao_01.Link(vbo_01, 1, 3, stride, offset);
	offset = 5;
	vao_01.Link(vbo_01, 2, 2, stride, offset);

	
	//init vao for model 02
	VAO vao_02;
	VBO vbo_02(model02_points, sizeof(model02_points));
	EBO ebo_02(model02_indices, sizeof(model02_indices));
	offset = 0;
	vao_02.Link(vbo_02, 0, 2, stride, offset);
	offset = 2;
	vao_02.Link(vbo_01, 1, 3, stride, offset);
	offset = 5;
	vao_02.Link(vbo_01, 2, 2, stride, offset);



	Shader shader("default.vert", "default.frag");
	unsigned int scale_id = glGetUniformLocation(shader.getId(),"scale");
	unsigned int tex_slot_id = glGetUniformLocation(shader.getId(), "texture_slot");

	//deinit for texture_01
	texture_01.Unbind();
	//deinit for model 01
	vao_01.Unbind();
	vbo_01.Unbind();
	ebo_01.Unbind();

	//deinit for model 02
	vao_02.Unbind();
	vbo_02.Unbind();
	ebo_02.Unbind();
	






	


	int wnd_closed = glfwWindowShouldClose(window);

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0, 0, 0, 1); 
		glClear(GL_COLOR_BUFFER_BIT);


		// Use the shader program
		shader.Activate();

		//toggle between vao_01 and vao_02
		//vao_01.Bind();
		vao_02.Bind(); 
		
		glUniform1f(scale_id, 1.0f);
		glUniform1i(tex_slot_id, 0);
		
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

	vao_01.Delete();
	ebo_01.Delete();
	vbo_01.Delete();

	vao_02.Delete();
	ebo_02.Delete();
	vbo_02.Delete();
	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}