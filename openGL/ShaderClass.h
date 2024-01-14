#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
string get_file_contents(const char* file_ptr);

class Shader
{
	public:
		unsigned int shader_pgm_id;

		Shader(const char* vert_file_ptr, const char* frag_file_ptr);
		unsigned int compile_myShader(unsigned int type, const string& shaderString);
		void Activate();
		void Delete();

};
#endif // !SHADER_CLASS_H

