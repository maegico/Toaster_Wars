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

//will make this return a struct
bool ModelLoaderManager::loadObj(std::string path, std::vector<glm::vec3> &vertices, std::vector<GLushort> &elements)
{
	std::ifstream is(path, std::ios::in);
	if (!is.is_open()) return false;

	std::vector<glm::vec3> things1;
	std::vector<glm::vec3> things2;

	std::string line;
	while (getline(is, line))
	{
		std::string tempF;
		std::string tempSh;

		if (line[0] == 'v')
		{
			if (line[1] == 't')
			{
				//s
			}
			else if (line[1] == 'n')
			{
				//s
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
				vertices.push_back(vector);
			}
		}
		else if (line[0] == 'f')
		{
			//remember to -1 the element, because obj index starts at 1, opengl starts at 0
			//also the first number in each set of num/num/num is the vertex number
			for (unsigned int i = 2; i < line.size(); i++)
			{
				if (line[i] != ' ' || line[i] != '/0')
				{
					if (line[i] != '/' && line[i] != ' ')
						tempSh += line[i];
					/*else
					{
						elements.push_back(std::stoi(tempSh));
						tempSh.clear();
					}*/
				}
				//reads in the elements and makes sure that they index starting at 0
				if (line[i+1] == ' ' || line[i+1] == '\0')
				{
					std::string temp;
					temp += tempSh[0];
					GLushort tempVar = std::stoi(temp);
					elements.push_back(tempVar-1);
					tempSh.clear();
				}
			}
		}
	}
	return true;
}