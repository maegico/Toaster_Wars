#include "ModelLoaderManager.h"


ModelLoaderManager::ModelLoaderManager()
{
}

ModelLoaderManager::ModelLoaderManager(const ModelLoaderManager& modelLoaderManagerCopy)
{
}

ModelLoaderManager::~ModelLoaderManager()
{
}

std::vector<std::string> ModelLoaderManager::split(const char* str, char c1, char c2)
{
	//the tokenized string
	std::vector<std::string> result;

	do
	{
		//sets a pointer to the first character of the token
		const char* begin = str;

		//while the current character isn't equal to c and str isn't NULL
			//go to the next character
		while (*str != c1 && *str != c2 && *str)
			str++;

		//create a string using the characters between begin and str
		result.push_back(std::string(begin, str));

	//check if the next character isn't NULL
	} while (0 != *str++);

	return result;
}

//will make this return a struct
bool ModelLoaderManager::loadObj(std::string path, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &uvs, std::vector<glm::vec3> &normals)
{
	std::vector<glm::vec3> vertTemp;
	std::vector<glm::vec2> uvTemp;
	std::vector<glm::vec3> normalTemp;

	std::vector<GLushort> vertIndices;
	std::vector<GLushort> uvIndices;
	std::vector<GLushort> normalIndices;

	char* delimiters = " /";
	std::vector<std::string> splitStr;

	std::ifstream is(path, std::ios::in);
	if (!is.is_open()) return false;

	std::string line;
	while (getline(is, line))
	{
		std::string tempF;
		std::string tempSh;

		if (line[0] == 'v')
		{
			if (line[1] == 't')
			{
				glm::vec2 vector;
				int tempI = 0;

				for (unsigned int i = 3; i < line.size(); i++)
				{
					if (line[i] != ' ')
					{
						tempF += line[i];
					}

					if (line[i + 1] == ' ' || line[i + 1] == '\0')
					{
						vector[tempI] = std::stof(tempF);
						tempF.clear();
						tempI++;
					}
				}
				uvTemp.push_back(vector);
			}
			else if (line[1] == 'n')
			{
				glm::vec3 vector;
				int tempI = 0;

				for (unsigned int i = 3; i < line.size(); i++)
				{
					if (line[i] != ' ')
					{
						tempF += line[i];
					}

					if (line[i + 1] == ' ' || line[i + 1] == '\0')
					{
						vector[tempI] = std::stof(tempF);
						tempF.clear();
						tempI++;
					}
				}
				normalTemp.push_back(vector);
			}
			else
			{
				glm::vec3 vector;
				int tempI = 0;

				for (unsigned int i = 2; i < line.size(); i++)
				{
					if (line[i] != ' ')
					{
						tempF += line[i];
					}

					if (line[i+1] == ' ' || line[i+1] == '\0')
					{
						vector[tempI] = std::stof(tempF);
						tempF.clear();
						tempI++;
					}
				}
				vertTemp.push_back(vector);
			}
		}
		else if (line[0] == 'f')
		{
			splitStr = split(line.c_str(), ' ', '/');

			vertIndices.push_back(std::stoi(splitStr[1]) - 1);
			vertIndices.push_back(std::stoi(splitStr[4]) - 1);
			vertIndices.push_back(std::stoi(splitStr[7]) - 1);

			uvIndices.push_back(std::stoi(splitStr[2]) - 1);
			uvIndices.push_back(std::stoi(splitStr[5]) - 1);
			uvIndices.push_back(std::stoi(splitStr[8]) - 1);

			normalIndices.push_back(std::stoi(splitStr[3]) - 1);
			normalIndices.push_back(std::stoi(splitStr[6]) - 1);
			normalIndices.push_back(std::stoi(splitStr[9]) - 1);

			splitStr.clear();
		}
	}

	for (int i = 0; i < vertIndices.size(); i++)
	{
		vertices.push_back(vertTemp[vertIndices[i]]);
	}

	for (int i = 0; i < uvIndices.size(); i++)
	{
		uvs.push_back(uvTemp[uvIndices[i]]);
	}

	for (int i = 0; i < normalIndices.size(); i++)
	{
		normals.push_back(normalTemp[normalIndices[i]]);
	}

	return true;
}