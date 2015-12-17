#include "GameWorld.h"
#include "Enemy.h"
#include "Player.h"
#include "OctTree.h"

std::vector<Shape*> GameWorld::shapePtrs = std::vector<Shape*>(0);
std::vector<GameObject*> GameWorld::gameObjPtrs = std::vector<GameObject*>(0);
CameraObject GameWorld::camera = CameraObject();
int GameWorld::numTri = 0;
GLuint GameWorld::progIndex = -1;
GLuint GameWorld::vAO;
float GameWorld::deltaTime = 0.0f;
float GameWorld::lastFoV = 0.0f;
glm::vec2 GameWorld::lastMousePos = glm::vec2(0, 0);
double GameWorld::lastTime = 0;
bool GameWorld::quit = false;
GameObject* player;
GameObject* enemy1;
GameObject* enemy2;
GameObject* pickup;
GameObject* lightning;
GameObject* bulletGO;
//OctTree tree;
vector<Enemy*> enemies;
vector<GameObject*> pickups;
vector<Bullet> temp;
Player play;
int score;
float enemyTimer;
float damageTimer;

GameWorld::GameWorld()
{
}

GameWorld::GameWorld(const GameWorld& gameWorldCopy)
{
}

GameWorld::~GameWorld()
{
	for (int i = 0; i < gameObjPtrs.size(); ++i)
	{
		delete gameObjPtrs[i];
	}
	for (int i = 0; i < shapePtrs.size(); ++i)
	{
		delete shapePtrs[i];
	}
}

bool GameWorld::init()
{
	//allows the use of new features
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		//printf("glew init error \n%s\n", glewGetErrorString(glewError));
		std::cout << "ERROR: GLEW did not initialize." << std::endl;
		return false;
	}

	glClearColor(0.5f, 0.75f, 0.5f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	progIndex = ShaderManager::loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (progIndex == 0)
	{
		std::cout << "PROBLEM: progIndex = 0" << std::endl;
		return false;
	}
	
	glUseProgram(progIndex);

	glGenVertexArrays(1, &vAO);
	glBindVertexArray(vAO);

	modelData model1 = { "Textures/default.png", "Models/cube.obj", std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };
	modelData toaster = { "Textures/toaster.png", "Models/toaster.obj",std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };
	modelData toast1 = { "Textures/toast1.png", "Models/toast1.obj",std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };
	modelData toast2 = { "Textures/toast2.png", "Models/toast2.obj",std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };
	modelData peanutButter = { "Textures/peanutButter.png", "Models/peanutButterPickup.obj",std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };
	modelData health = { "Textures/health.png", "Models/health.obj",std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };
	modelData bullet = { "Textures/bullet.png", "Models/bullet.obj",std::vector<glm::vec3>(), std::vector<glm::vec2>(), std::vector<glm::vec3>() };

	if (!ModelLoaderManager::loadObj(model1.modelPath, model1.verts, model1.uvs, model1.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}
	if (!ModelLoaderManager::loadObj(toaster.modelPath, toaster.verts, toaster.uvs, toaster.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}
	if (!ModelLoaderManager::loadObj(toast1.modelPath, toast1.verts, toast1.uvs, toast1.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}
	if (!ModelLoaderManager::loadObj(toast2.modelPath, toast2.verts, toast2.uvs, toast2.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}
	if (!ModelLoaderManager::loadObj(peanutButter.modelPath, peanutButter.verts, peanutButter.uvs, peanutButter.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}
	if (!ModelLoaderManager::loadObj(health.modelPath, health.verts, health.uvs, health.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}
	if (!ModelLoaderManager::loadObj(bullet.modelPath, bullet.verts, bullet.uvs, bullet.normals))
	{
		std::cout << "ERROR: loadObj failed." << std::endl;
		return false;
	}

	shapePtrs.push_back(new Shape(model1.verts, model1.uvs, model1.normals, model1.texturePath.c_str(), progIndex));
	shapePtrs.push_back(new Shape(toaster.verts, toaster.uvs, toaster.normals, toaster.texturePath.c_str(), progIndex));
	shapePtrs.push_back(new Shape(toast1.verts, toast1.uvs, toast1.normals, toast1.texturePath.c_str(), progIndex));
	shapePtrs.push_back(new Shape(toast2.verts, toast2.uvs, toast2.normals, toast2.texturePath.c_str(), progIndex));
	shapePtrs.push_back(new Shape(peanutButter.verts, peanutButter.uvs, peanutButter.normals, peanutButter.texturePath.c_str(), progIndex));
	shapePtrs.push_back(new Shape(health.verts, health.uvs, health.normals, health.texturePath.c_str(), progIndex));
	shapePtrs.push_back(new Shape(bullet.verts, bullet.uvs, bullet.normals, bullet.texturePath.c_str(), progIndex));

	glm::vec3 threeDZero = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec2 twoDZero = glm::vec2(0.0f, 0.0f);

	//tree = OctTree(vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));

	gameObjPtrs.push_back(new GameObject(shapePtrs[0], threeDZero, threeDZero, 0.05f, glm::vec3(1, 1, 0), 0, camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f)));
	player = new GameObject(shapePtrs[1], glm::vec3(-0.8f, 0.0f, 0.0f), threeDZero, 0.125f, glm::vec3(0, 0, 1), (-3.1415f/2.f), camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f));
	enemy1 = new GameObject(shapePtrs[2], threeDZero, vec3(-0.3f, 0.0f, 0.0f), 0.05f, glm::vec3(0, 0, 1), (-3.1415f / 2.f), camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f));
	enemy2 = new GameObject(shapePtrs[3], threeDZero, vec3(-0.3f, 0.0f, 0.0f), 0.05f, glm::vec3(0, 0, 1), (-3.1415f / 2.f), camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f));
	pickup = new GameObject(shapePtrs[4], threeDZero, vec3(-0.1f, 0.0f, 0.0f), 0.04f, glm::vec3(1, 1, 0), 0, camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f));
	lightning = new GameObject(shapePtrs[5], threeDZero, vec3(-0.1f,0.0f,0.0f), 0.04f, glm::vec3(0, 1, 0), (-3.1415f / 2.f), camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f));
	bulletGO = new GameObject(shapePtrs[6], threeDZero, threeDZero, 0.2f, glm::vec3(0, 0, 1), (-3.1415f / 2.f), camera.getFoV(), glm::vec3(1.0f, 0.0f, 0.0f));

	//tree.add(player->colliderPtr);

	play = Player(player, bulletGO);

	score = 0;
	enemyTimer = 0;
	damageTimer = 0;
	srand(time(0));

	return true;
}

GameObject* dropPickup(GameObject* obj)
{
	int chance = rand() % 100;
	GameObject* toReturn = nullptr;
	if (chance <= 60)
	{
		//nothing is dropped
	}
	else if (chance >= 61 && chance <= 90)
	{
		GameObject* toDrop = new GameObject(lightning);
		toDrop->setPosition(obj->getPosition());
		toReturn = toDrop;
	}
	else if (chance > 90)
	{
		GameObject* toDrop = new GameObject(pickup);
		toDrop->setPosition(obj->getPosition());
		toReturn = toDrop;
	}
	return toReturn;
}

bool GameWorld::update(GLFWwindow* windowPtr)
{

	player->setViewMatrixData(camera.getLocation(), camera.getOneAhead(), camera.getUp());
	for each(Bullet b in play.bullets)
	{
		b.setViewMatrixData(camera.getLocation(), camera.getOneAhead(), camera.getUp());
	}
	for each(Enemy* e in enemies)
	{
		e->setViewMatrixData(camera.getLocation(), camera.getOneAhead(), camera.getUp());
	}
	for each(GameObject* p in pickups)
	{
		if(p != NULL) p->setViewMatrixData(camera.getLocation(), camera.getOneAhead(), camera.getUp());
	}
	for each(Bullet b in temp)
	{
		b.setViewMatrixData(camera.getLocation(), camera.getOneAhead(), camera.getUp());
	}

	double currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	windowData wndData;
	glfwGetWindowSize(windowPtr, &(wndData.width), &(wndData.height));
	//to voom out and in - glfwGetMouseWheel() is depricated
	//camera.setFoV = lastFoV - 5 * glfwGetMouseWheel();

	play.update(deltaTime);
	player->update(wndData);

	for each(Enemy* e in enemies)
	{
		e->update(deltaTime);
	}
	for each(GameObject* p in pickups)
	{
		if(p != NULL) p->update(wndData, deltaTime);
	}
	for (int i = 0; i < temp.size(); i++)
	{
		Bullet b = temp[i];
		b.update(deltaTime);
		if(b.getPosition().x <= -1)
		{
			temp.erase(temp.begin() + i);
		}
	}

	enemyTimer += deltaTime;
	if (enemyTimer >= 3)
	{
		float yLoc = (rand() % 100) / 100.0f;
		int chance = rand() % 2;
		if (chance == 0) yLoc *= -1;
		switch (chance)
		{
		case 0:
			enemies.push_back(new Enemy(pickup, lightning, vec3(1.0f,yLoc,0.0f), new GameObject(enemy1), bulletGO));
			//tree.add(enemies.back()->getCollider());
			break;
		case 1:
			enemies.push_back(new Enemy(pickup, lightning, vec3(1.0f, yLoc, 0.0f), new GameObject(enemy2), bulletGO));
			//tree.add(enemies.back()->getCollider());
			break;
		default:
			enemies.push_back(new Enemy(pickup, lightning, vec3(1.0f, yLoc, 0.0f), new GameObject(enemy1), bulletGO));
			//tree.add(enemies.back()->getCollider());
			break;
		}
		enemyTimer = 0;
	}

	damageTimer += deltaTime;
	if (damageTimer >= 1)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			Enemy* e = enemies[i];
			bool test = e->changeHealth(-1,true);
			if (test)
			{
				pickups.push_back(dropPickup(e->getOBJ()));
				for each(Bullet b in e->bullets)
				{
					temp.push_back(b);
				}
				enemies.erase(enemies.begin() + i);
				score += 100;
			}
		}
		damageTimer = 0;
	}

	if (!play.playing)
	{
		cout << "You lose! Your score is: " << score << endl;
		quit = true;
	}

	lastTime = currentTime;

	//cout << score << endl;

	return quit;
}

void GameWorld::draw()
{
	//clears the buffer currently enabled for color writing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw here
	for (int i = 0; i < gameObjPtrs.size(); i++)
	{
		gameObjPtrs[i]->draw(GL_TRIANGLES);
	}

	player->draw(GL_TRIANGLES);
	for each(Bullet b in play.bullets)
	{
		b.draw();
	}
	for each(Enemy* e in enemies)
	{
		e->draw();
		for each(Bullet b in e->bullets)
		{
			b.draw();
		}
	}
	for each(GameObject* p in pickups)
	{
		if(p != NULL) p->draw(GL_TRIANGLES);
	}
	for each(Bullet b in temp)
	{
		b.draw();
	}

	glFlush();
}

glm::vec2 GameWorld::getCursorPos(GLFWwindow* windowPtr)
{
	double xpos, ypos;
	glm::vec2 cursorPos;
	int width, height;

	glfwGetCursorPos(windowPtr, &xpos, &ypos);

	glfwGetWindowSize(windowPtr, &width, &height);

	cursorPos.x = (((float)xpos / width) * 2) - 1;
	cursorPos.y = -1 * ((((float)ypos / height) * 2) - 1);

	return cursorPos;
}

void GameWorld::keyPress(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
{
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_PRESS)
		play.up = true;
	if ((key == GLFW_KEY_UP || key == GLFW_KEY_W) && action == GLFW_RELEASE)
		play.up = false;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_PRESS)
		play.down = true;
	if ((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && action == GLFW_RELEASE)
		play.down = false;
	if ((key == GLFW_KEY_SPACE) && action == GLFW_PRESS)
		play.shooting = true;
	if ((key == GLFW_KEY_SPACE) && action == GLFW_RELEASE)
		play.shooting = false;
	if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS)
		quit = true;
	if ((key == GLFW_KEY_L) && action == GLFW_PRESS)
		play.changeHealth(-10);
	if ((key == GLFW_KEY_P) && action == GLFW_PRESS)
		play.powerup = true;
}
void GameWorld::mouseMove(GLFWwindow* windowPtr, double xpos, double ypos)
{
	camera.turn((xpos - lastMousePos.x)/1000, (ypos - lastMousePos.y)/1000);

	lastMousePos.x = xpos;
	lastMousePos.y = ypos;
}

