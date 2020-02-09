#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"

#include <fstream>
#include <sstream>

int main()
{
	//Initialize hooks to windows.
	if (glfwInit() == false)
		return -1;

	//Setting window resolution
	GLFWwindow* window = glfwCreateWindow(1280, 720, "GameEngine", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		
		return -2;
	}

	glfwMakeContextCurrent(window);

	//Testing the OpenGL functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();

		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	printf("GL: %i.%i\n", major, minor);

	//DO STUFF
	float red = 1.0f;
	float green = 0.0f;
	float blue = 0.0f;

	glm::vec3 verticies[] =
	{
		glm::vec3(-0.25f, 0.25f, 0.25f),
		glm::vec3(-0.25f, -0.25f, 0.25f),
		glm::vec3(0.25f, 0.25f, 0.25f),
		glm::vec3(0.25f, -0.25f, 0.25f),
		glm::vec3(-0.25f, 0.25f, -0.25f),
		glm::vec3(-0.25f, -0.25f, -0.25f),
		glm::vec3(0.25f, 0.25f, -0.25f),
		glm::vec3(0.25f, -0.25f, -0.25f)

		//glm::vec3(-0.1f, -0.1f, -0.1f),
		//glm::vec3(-0.1f, -0.1f, 0.1f),
		//glm::vec3(-0.1f, 0.1f, 0.1f),
		//glm::vec3(0.1f, 0.1f, -0.1f),
		//glm::vec3(-0.1f, -0.1f, -0.1f),
		//glm::vec3(-0.1f, 0.1f, -0.1f),

		//glm::vec3(0.1f, -0.1f, 0.1f),
		//glm::vec3(-0.1f, -0.1f, -0.1f),
		//glm::vec3(0.1f, -0.1f, -0.1f),
		//glm::vec3(0.1f, 0.1f, -0.1f),
		//glm::vec3(0.1f, -0.1f, -0.1f),
		//glm::vec3(-0.1f, -0.1f, -0.1f),

		//glm::vec3(-0.1f, -0.1f, -0.1f),
		//glm::vec3(-0.1f, 0.1f, 0.1f),
		//glm::vec3(-0.1f, 0.1f, -0.1f),
		//glm::vec3(0.1f, -0.1f, 0.1f),
		//glm::vec3(-0.1f, -0.1f, 0.1f),
		//glm::vec3(-0.1f, -0.1f, -0.1f),

		//glm::vec3(-0.1f, 0.1f, 0.1f),
		//glm::vec3(-0.1f, -0.1f, 0.1f),
		//glm::vec3(0.1f, -0.1f, 0.1f),
		//glm::vec3(0.1f, 0.1f, 0.1f),
		//glm::vec3(0.1f, -0.1f, -0.1f),
		//glm::vec3(0.1f, 0.1f, -0.1f),

		//glm::vec3(0.1f, -0.1f, -0.1f),
		//glm::vec3(0.1f, 0.1f, 0.1f),
		//glm::vec3(0.1f, -0.1f, 0.1f),
		//glm::vec3(0.1f, 0.1f, 0.1f),
		//glm::vec3(0.1f, 0.1f, -0.1f),
		//glm::vec3(-0.1f, 0.1f, -0.1f),

		//glm::vec3(0.1f, 0.1f, 0.1f),
		//glm::vec3(-0.1f, 0.1f, -0.1f),
		//glm::vec3(-0.1f, 0.1f, 0.1f),
		//glm::vec3(0.1f, 0.1f, 0.1f),
		//glm::vec3(-0.1f, 0.1f, 0.1f),
		//glm::vec3(0.1f, -0.1f, 0.1f),
	};

	glm::mat4 projection = glm::perspective(1.507f, 16 / 9.0f, 0.1f, 50.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1.0f);

	unsigned int vertexShaderID = 0;
	unsigned int fragmentShaderID = 0;
	unsigned int shaderProgramID = 0;

	std::string shaderData;
	std::ifstream inFileStream("..\\Shaders\\SimpleVert.shader", std::ifstream::in);

	std::stringstream stringStream;
	
	if (inFileStream.is_open())
	{
		stringStream << inFileStream.rdbuf();
		shaderData = stringStream.str();
		inFileStream.close();
	}

	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	const char* data = shaderData.c_str();

	glShaderSource(vertexShaderID, 1, (const GLchar**)&data, 0);
	glCompileShader(vertexShaderID);

	GLint success = GL_FALSE;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		//printf("Vertex Shader Failed");

		//------------------------------
		//DEBUG
		//------------------------------
		GLint logLength = 0;
		glGetShaderiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetShaderInfoLog(shaderProgramID, logLength, 0, log);

		std::string errorMessage(log);
		errorMessage += "SHADER_FAILED_TO_COMPILE";
		printf(errorMessage.c_str());
		delete[] log;
		//------------------------------
		//------------------------------
		//------------------------------
	}

	std::ifstream inFileStreamFrag("..\\Shaders\\SimpleFrag.shader", std::ifstream::in);
	std::stringstream fragStringStream;

	if (inFileStreamFrag.is_open())
	{
		fragStringStream << inFileStreamFrag.rdbuf();
		shaderData = fragStringStream.str();
		inFileStreamFrag.close();
	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	data = shaderData.c_str();

	glShaderSource(fragmentShaderID, 1, (const GLchar**)&data, 0);
	glCompileShader(fragmentShaderID);

	success = GL_FALSE;
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		//printf("Fragment Shader Failed");

		//------------------------------
		//DEBUG
		//------------------------------
		GLint logLength = 0;
		glGetShaderiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetShaderInfoLog(shaderProgramID, logLength, 0, log);

		std::string errorMessage(log);
		errorMessage += "SHADER_FAILED_TO_COMPILE";
		printf(errorMessage.c_str());
		delete[] log;
		//------------------------------
		//------------------------------
		//------------------------------
	}

	shaderProgramID = glCreateProgram();

	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);

	glLinkProgram(shaderProgramID);

	success = GL_FALSE;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);

	if (!success)
	{
		//printf("Shader linking failed");

		//------------------------------
		//DEBUG
		//------------------------------
		GLint logLength = 0;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength];
		glGetProgramInfoLog(shaderProgramID, logLength, 0, log);

		std::string errorMessage(log);
		errorMessage += "SHADER_FAILED_TO_COMPILE";
		printf(errorMessage.c_str());
		delete[] log;
		//------------------------------
		//------------------------------
		//------------------------------
	}

	int indexBuffer[] 
	{
		0, 1, 2,
		2, 1, 3,

		4, 6, 5,
		6, 7, 5,

		4, 5, 0,
		0, 5, 1,

		2, 3, 6,
		6, 3, 7,

		1, 5, 3,
		3, 5, 7,

		4, 0, 6,
		6, 0, 2
	};

	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;

	float pointSize = 10.0f;
	bool resizeComplete = false;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(int), indexBuffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Keeps the window open until the escape key is pressed.
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		static int framecount = 0;
		framecount++;

		glClearColor(red, green, blue, 1);
		glEnable(GL_DEPTH_TEST); //Enables depth buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (pointSize >= 10.0f && resizeComplete == false)
			resizeComplete = true;
		else if (pointSize <= 1.0f && resizeComplete == true)
			resizeComplete = false;

		if (resizeComplete == true)
			pointSize -= 1.0f;
		else
			pointSize += 1.0f;

		glLineWidth(pointSize);

		//Color fading
		if (blue >= 1 && green <= 0 && red <= 1)
			red += 0.01f;
		else if (blue >= 1 && red <= 0)
			green -= 0.01f;
		else if (green >= 1 && red <= 0)
			blue += 0.01f;
		else if (green >= 1 && blue <= 0)
			red -= 0.01f;
		else if (red >= 1 && blue <= 0)
			green += 0.01f;
		else if (red >= 1 && green <= 0)
			blue -= 0.01f;

		model = glm::rotate(model, 0.015f, glm::vec3(0.5f, 0.5f, 0));

		glm::mat4 pv = projection * view;

		glm::vec4 color = glm::vec4(red - 0.5f, green - 0.5f, blue - 0.5f, 1.0f);
		
		glUseProgram(shaderProgramID);

		auto uniformLocation = glGetUniformLocation(shaderProgramID, "projection_view_matrix");
		glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(pv));
		uniformLocation = glGetUniformLocation(shaderProgramID, "model_matrix");
		glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(model));
		uniformLocation = glGetUniformLocation(shaderProgramID, "color");
		glUniform4fv(uniformLocation, 1, glm::value_ptr(color));

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}