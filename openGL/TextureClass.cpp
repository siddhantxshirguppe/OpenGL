#include"TextureClass.h"
#include"STB/stb_image.h"
#include<glad/glad.h>

TEXTURE::TEXTURE(std::string image_path)
{
	//create and bind the texture buffer
	glGenTextures(1, &texture_id);
	glBindTexture(GL_PROXY_TEXTURE_2D, texture_id);

	//load the image


	const char* img_path_cstr = image_path.c_str();
	m_img_bytes = stbi_load(img_path_cstr, &m_img_width, &m_img_height, &m_img_channels,0);
}

void TEXTURE::setSlot(int slot_num)
{
	glActiveTexture(GL_TEXTURE0 + slot_num);
}

void TEXTURE::Bind_and_Write()
{
	glBindTexture(GL_PROXY_TEXTURE_2D, texture_id);

	//4 required calls 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //gives a pixelated style 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //gives a pixelated style 


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //gives repeated texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //gives repeated texture

	//write the image data to buffer 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_img_width, m_img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_img_bytes);

	//unbind for safety 
	glBindTexture(GL_PROXY_TEXTURE_2D, 0);
}

void TEXTURE::Unbind()
{
	glBindTexture(GL_PROXY_TEXTURE_2D, 0);
}

void TEXTURE::Delete()
{
	glDeleteTextures(1, &texture_id);
}