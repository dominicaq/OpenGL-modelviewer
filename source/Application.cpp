#include "Application.h"

const char* APP_TITLE = "3D engine";
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Scene
#include "GameObject/Shader.h"
#include "GameObject/Model.h"
#include "GameObject/Light.h"
#include "GameObject/Camera.h"

Application::Application() {
	currentWindow.CreateWindow(APP_TITLE, SCR_WIDTH, SCR_HEIGHT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void Application::Run() {
#pragma region Scene
	Camera cam;
	cam.CreateCamera(90.0f, 0.1f, 1000.0f);
	cam.transform.position = Vector3(0, 0, 2);

	//Shader
	Shader myShader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag");

	//Model
	Model torus;
	torus.loadModel("Resources/Models/torus.obj");
	torus.textures.push_back(Texture("Resources/Textures/bricks.jpg"));

	//Light Source
	Light light;
	light.color = Vector3(1.0f, 1.0f, 1.0f);
	light.transform.position = Vector3(1, 10, 10);

	float step = 0;
#pragma endregion

	while (!currentWindow.ShouldClose())
	{
		GameTime::Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

#pragma region Main Game
		step += GameTime::deltaTime();
		torus.transform.position.y = sin(step * 2.5) / 2;
		torus.transform.eulerAngles.z += GameTime::deltaTime() * 50;
		torus.transform.eulerAngles.x += GameTime::deltaTime() * 50;
		torus.transform.eulerAngles.z += GameTime::deltaTime() * 50;

#pragma region ImGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Transformations");

		ImGui::Text("Camera");
		ImGui::SliderFloat3("CPosition", (float*)&cam.transform.position, -50, 50);
		ImGui::SliderFloat3("CEuler Angle", (float*)&cam.transform.eulerAngles, -360, 360);

		ImGui::Text("Light");
		ImGui::SliderFloat3("LPosition", (float*)&light.transform.position, -50, 50);
		ImGui::End();
#pragma endregion

		myShader.setVec3("light.color", light.color);
		myShader.setVec3("light.position", light.transform.position);
		myShader.setVec3("viewPos", cam.transform.position);

		torus.Draw(cam, myShader);
#pragma endregion

		currentWindow.Update();
	}

	currentWindow.CleanUp();
}