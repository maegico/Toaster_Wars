#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
}

ShaderManager::ShaderManager(const ShaderManager& shaderManagerCopy)
{
}

ShaderManager::~ShaderManager()
{
}

char* ShaderManager::loadTextFile(const char* file)
{
	std::ifstream inFile(file, std::ios::binary);
	//checks if the file is in the stream
	if (inFile.is_open())
	{
		//go to the end of the file
		inFile.seekg(0, std::ios::end);
		//finds the length of the file and saves it
		int length = (int)inFile.tellg();
		//goes back to the beginning
		inFile.seekg(0, std::ios::beg);

		char* fileContents = new char[length + 1];

		//grab the characters from the stream and put them in file Contents
		inFile.read(fileContents, length);
		//ends the file in a zero
		fileContents[length] = 0;
		//closes the file
		inFile.close();

		return fileContents;
	}
	else
		return 0;
}

GLuint ShaderManager::loadShader(const char* file, GLenum shaderType)
{
	//call the above function and save it into loadedFile
	const char* loadedFile = loadTextFile(file);

	//if something happens and it doesn't read in the file
	if (loadedFile == NULL)
	{
		//write the problem to the console and return 0
		std::cout << "PROBLEM: Loaded File returned NULL" << std::endl;
		return 0;
	}

	//create the shader and save its index in shaderIndex
	GLuint shaderIndex = glCreateShader(shaderType);
	//put the code from loaded file into the shader at shaderIndex
	glShaderSource(shaderIndex, 1, &loadedFile, 0);
	//compiles the shader creating a .o object file
	glCompileShader(shaderIndex);

	//delete the character array holding the shader in memory
	delete[] loadedFile;

	//create an int to say whether the shader compiled
	GLint compiled = 0;
	//get the compile status
	glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &compiled);

	//if the shader compiled return the shader index
	if (compiled == GL_TRUE)
		return shaderIndex;

	GLint logLength = 0;
	//if it didn't compile get the info log
	glGetShaderiv(shaderIndex, GL_INFO_LOG_LENGTH, &logLength);

	//a char array to hold the log
	char* log = new char[logLength];
	//get the log and print it out
	glGetShaderInfoLog(shaderIndex, logLength, &logLength, log);
	//delete the shader
	glDeleteShader(shaderIndex);

	std::cout << log << std::endl;

	delete log;

	return 0;
}

GLuint ShaderManager::loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	//read in and compile the vertex shader
	GLuint vertexShaderIndex = loadShader(vertexFile, GL_VERTEX_SHADER);
	
	//if load shader failed print out an error message and return 0
	if (vertexShaderIndex == 0)
	{
		std::cout << "PROBLEM: Vertex Shader index = 0";
		return 0;
	}

	GLuint fragShaderIndex = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	//if load shader failed print out an error message and return 0
	if (fragShaderIndex == 0)
	{
		std::cout << "PROBLEM: Fragment Shader index = 0";
		return 0;
	}

	//returns the index of a shader program object
	GLuint progIndex = glCreateProgram();
	//attach the vertex shader, so that the linker can link it with the program
	glAttachShader(progIndex, vertexShaderIndex);
	//attach the fragment shader, so that the linker can link it with the program
	glAttachShader(progIndex, fragShaderIndex);
	//uses the linker to link the whole program
	glLinkProgram(progIndex);

	GLint linkConfirm = 0;
	//check if the program linked
	glGetProgramiv(progIndex, GL_LINK_STATUS, &linkConfirm);

	//if linked return the program Index
	if (linkConfirm)
		return progIndex;

	GLint logLength = 0;
	//get the info logs length
	glGetProgramiv(progIndex, GL_INFO_LOG_LENGTH, &logLength);

	char* log = new char[logLength];
	//save the log into the char* log
	glGetProgramInfoLog(progIndex, logLength, &logLength, log);
	std::cout << log << std::endl;
	//delete the program
	glDeleteProgram(progIndex);
	delete[] log;

	return 0;
}