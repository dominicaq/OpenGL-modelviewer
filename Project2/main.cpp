#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Display.h"

#include "Maths/glm.h"

#include "GameObject/Shader.h"
#include "Model.h"
#include "GameObject/Light.h"

#include <iostream>
#include <vector>
#include "Time.h"

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar* message,const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

int main()
{
    Display windowDisplay("My OpenGL window", SCR_WIDTH, SCR_HEIGHT, 144);
    Camera cam(90.0f, 0.1f, 1000.0f);
    cam.transform.position = Vector3(0, 0, 2);

    Shader myShader("Shaders/vertexShader.vert", "Shaders/fragmentShader.frag");

#pragma region test model

    Texture texture0("Resources/backpack/diffuse.jpg");

    Model testModel;
    testModel.loadModel("Resources/backpack/backpack.obj");
    testModel.transform.position = Vector3(-1, 0, -5);
    testModel.textures.push_back(texture0);

#pragma endregion

    Model torus;
    torus.loadModel("Resources/Models/torus.obj");
    torus.textures.push_back(Texture("Resources/Textures/bricks.jpg"));

    // Light Source
    Model bulb;
    bulb.loadModel("Resources/Models/lightbulb.obj");
    bulb.textures.push_back(Texture("Resources/Textures/gold.png"));
    bulb.transform.scale = Vector3(0.25, 0.25, 0.25);
    Light light;
    light.color = Vector3(1.0f, 1.0f, 1.0f);
    light.transform.position = Vector3(1, 10, 10);

    //glEnable(GL_DEBUG_OUTPUT);
    //glDebugMessageCallback(MessageCallback, 0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    
    float step = 0;
    while (!windowDisplay.IsClosed())
    {
        Time::Update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

        step += Time::deltaTime();
        torus.transform.position.y = sin(step * 2.5) / 2;
        torus.transform.eulerAngles.z += Time::deltaTime() * 50;
        torus.transform.eulerAngles.x += Time::deltaTime() * 50;
        torus.transform.eulerAngles.z += Time::deltaTime() * 50;
 
#pragma region ImGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Transformations");

        ImGui::Text("Camera");
        ImGui::SliderFloat3("CPosition", (float*)&cam.transform.position, -50, 50);
        ImGui::SliderFloat3("CEuler Angle", (float*)&cam.transform.eulerAngles, -360, 360);

        ImGui::Text("Model");
        ImGui::SliderFloat3("Position", (float*)&testModel.transform.position, -50, 50);
        ImGui::SliderFloat3("Euler Angle", (float*)&testModel.transform.eulerAngles, -360, 360);

        ImGui::Text("Light");
        ImGui::SliderFloat3("LPosition", (float*)&light.transform.position, -50, 50);
        ImGui::End();
#pragma endregion

        myShader.setVec3("light.color", light.color);
        myShader.setVec3("light.position", light.transform.position);

        myShader.setVec3("viewPos", cam.transform.position);
        bulb.transform.position = light.transform.position;
        bulb.Draw(cam, myShader);
        testModel.Draw(cam, myShader);
        torus.Draw(cam, myShader);
        windowDisplay.Update();
    }

    //testModel.DeleteModel();
    windowDisplay.~Display();
    return 0;
}