#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexShader.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "Object.h"
#include "Cube.h"

const int WIDTH_SCREEN = 800;
const int HEIGHT_SCREEN = 800;

const float CAMERA_FOV = 60.0f;
float cameraSpeed = 1.f;
glm::vec3 worldFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 worldRight = glm::vec3(1.0f, 0.0f, 0.0f);


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = worldFront;
glm::vec3 cameraUp = worldUp;
glm::vec3 cameraRight = worldRight;


bool hasMouseMoved = false;
double mPosX = 0.f, mPosY = 0.f;

double deltaX = 0.f;
double deltaY = 0.f;

glm::vec3 cowObjective = glm::vec3(-7.f, 0.f, 10.f);
glm::vec3 cowDefault = glm::vec3(-7.f, 0.f, 0.f);
glm::vec3 cowDirNorm = glm::normalize(cowObjective - cowDefault);
float cowAngle = 45.f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float cameraSpeedByDeltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraFront * cameraSpeedByDeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraFront * cameraSpeedByDeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cameraPos += cameraUp * cameraSpeedByDeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraPos -= cameraUp * cameraSpeedByDeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeedByDeltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeedByDeltaTime;
    }
}

double yaw, pitch = 0.f;

void processMouseInput(GLFWwindow* window, double posx, double posy) {
    if (!hasMouseMoved) {
        hasMouseMoved = true;
        mPosX = posx;
        mPosY = posy;
    }

    deltaX = posx - mPosX;
    deltaY = posy - mPosY;

    yaw -= deltaX;
    pitch -= deltaY;

    mPosX = posx;
    mPosY = posy;
}

void UpdateCamera() {
    glm::mat4 transform = glm::mat4(1.f);

    transform = glm::rotate(transform, glm::radians((float)yaw), worldUp);
    cameraFront = transform * glm::vec4(worldFront, 1.0f);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));

    transform = glm::mat4(1.f);
    transform = glm::rotate(transform, glm::radians((float)pitch), cameraRight);
    cameraFront = transform * glm::vec4(cameraFront, 1.0f);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "Cpp3D", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW Wwindow" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, processMouseInput);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }



    glEnable(GL_DEPTH_TEST);

    Shader shader = Shader("./Assets/Vertex.shader", "./Fragment.shader");
    Object* obj = new Object("./Assets/pumpkin_tall_10k.obj");
    Object* cow = new Object("./Assets/cow-nonormals.obj");

    float cubeVertis[] = {
         -0.5f, -0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,

         -0.5f, -0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f,

         -0.5f,  0.5f,  0.5f,
         -0.5f,  0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
         -0.5f, -0.5f, -0.5f,
         -0.5f, -0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,

          0.5f,  0.5f,  0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,

         -0.5f, -0.5f, -0.5f,
          0.5f, -0.5f, -0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
         -0.5f, -0.5f,  0.5f,
         -0.5f, -0.5f, -0.5f,

         -0.5f,  0.5f, -0.5f,
          0.5f,  0.5f, -0.5f,
          0.5f,  0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,
         -0.5f,  0.5f, -0.5f,
    };

    Cube cvwn = Cube();

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, obj->subMesh.global.size() * sizeof(glm::vec3), obj->subMesh.global.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----------------------------------------------------------------------------------

    unsigned int VBOCow, VAOCow;
    glGenVertexArrays(1, &VAOCow);
    glGenBuffers(1, &VBOCow);

    glBindVertexArray(VAOCow);

    glBindBuffer(GL_ARRAY_BUFFER, VBOCow);
    glBufferData(GL_ARRAY_BUFFER, cow->subMesh.global.size() * sizeof(glm::vec3), cow->subMesh.global.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----------------------------------------------------------------------------------

    unsigned int VBOTexCube, VAOTexCube;
    glGenVertexArrays(1, &VAOTexCube);
    glGenBuffers(1, &VBOTexCube);

    glBindVertexArray(VAOTexCube);

    glBindBuffer(GL_ARRAY_BUFFER, VBOTexCube);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 8, cvwn._vertis, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----------------------------------------------------------------------------------

    unsigned int VBOlight, VAOlight;
    glGenVertexArrays(1, &VAOlight);
    glGenBuffers(1, &VBOlight);

    glBindVertexArray(VAOlight);

    glBindBuffer(GL_ARRAY_BUFFER, VBOlight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertis), cubeVertis, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //----------------------------------------------------------------------------------

    Shader shaderLight("./Assets/LightVertex.shader", "./Assets/LightFrag.shader");
    glm::vec3 lightPosition(2, 2, 2);


    float i = 0;

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nbChannels;
    unsigned char* data = stbi_load("./Assets/tiles_0064_color_1k.jpg", &width, &height, &nbChannels, 0);

    if (data) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture!" << std::endl;
    }
    stbi_image_free(data);


    float lastTime = (float)glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        float currenttime = (float)glfwGetTime();
        float deltaTime = currenttime - lastTime;
        lastTime = currenttime;

        processInput(window, cameraSpeed * deltaTime * 1.f);

        // Render
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.Use();
        shader.SetVector3("lightPos", lightPosition);
        shader.SetVector3("viewPos", cameraPos);

        shader.SetVector3("material.ambientColor", 1.0f, 0.5f, 0.31f);
        shader.SetVector3("material.diffuseColor", 1.0f, 0.5f, 0.31f);
        shader.SetVector3("material.specularColor", .5f, 0.5f, 0.5f);
        shader.SetFloat("material.shininess", 32.f);

        shader.SetVector3("light.ambientIntensity", 0.2f, 0.2f, 0.2f);
        shader.SetVector3("light.diffuseIntensity", 0.5f, 0.5f, 0.5f);
        shader.SetVector3("light.specularIntensity", 1.f, 1.f, 1.f);

        glm::mat4 projection = glm::mat4(1.f);
        projection = glm::perspective(glm::radians(CAMERA_FOV), (float)WIDTH_SCREEN / (float)HEIGHT_SCREEN, 0.1f, 100.f);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        UpdateCamera();
        
        shader.SetMatrix4("projection", projection);
        shader.SetMatrix4("view", view);

        i++;

        //----------------------------------------------------------------------------------
        // PUMPKIN

        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
        shader.SetMatrix4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, obj->subMesh.global.size());
        glBindVertexArray(0);

        //----------------------------------------------------------------------------------
        // COW
        
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(-7.f, 0.f, 0.f));
        model = glm::rotate(model, glm::radians(cowAngle), glm::vec3(1.f, 0.f, 0.f));
        cowAngle += 45.f;

        shader.SetVector3("material.ambientColor", 0.f, 0.f, 1.f);
        shader.SetVector3("material.diffuseColor", 0.f, 0.f, 1.f);
        shader.SetMatrix4("model", model);

        glBindVertexArray(VAOCow);
        glDrawArrays(GL_TRIANGLES, 0, cow->subMesh.global.size());
        glBindVertexArray(0);

        //----------------------------------------------------------------------------------
        // TEXTURED CUBE

        shader.SetVector3("material.diffuseColor", .5f, 0.f, 0.5f);
        shader.SetVector3("material.ambientColor", .5f, .5f, 0.f);
        shader.SetInt("texture1", 0);
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.0f));
        shader.SetMatrix4("model", model);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAOTexCube);
        glDrawArrays(GL_TRIANGLES, 0, 48 * 6);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        //----------------------------------------------------------------------------------
        //LIGHT CUBE

        shaderLight.Use();
        
        shaderLight.SetMatrix4("projection", projection);
        shaderLight.SetMatrix4("view", view);
        model = glm::mat4(1.0f);
        float posy = sin(glm::radians(i/10)) * 100.f;
        float posz = cos(glm::radians(i/10)) * 100.f;
        lightPosition = glm::vec3(0.f, posy, posz);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        shaderLight.SetMatrix4("model", model);

        glBindVertexArray(VAOlight);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &VAOCow);
    glDeleteBuffers(1, &VBOCow);

    glDeleteVertexArrays(1, &VAOTexCube);
    glDeleteBuffers(1, &VBOTexCube);

    glDeleteVertexArrays(1, &VAOlight);
    glDeleteBuffers(1, &VBOlight);
    shaderLight.Shutdown();

    glfwTerminate();
    return 0;
};