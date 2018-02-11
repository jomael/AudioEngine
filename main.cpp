#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstddef>

#include "openglbacked.hpp"

#include "al/AudioSystem.hpp"
#include "al/ALListener.hpp"

audio::al::AudioSystem *g_audioSystem = nullptr;
audio::al::AudioListener *g_audioListener = nullptr;

void loadAudio()
{
    g_audioSystem = new audio::al::AudioSystem();
    g_audioListener = new audio::al::AudioListener();
    g_audioSystem->loadFromFile("wind", "resources/wind.ogg");
    g_audioSystem->loadFromFile("thunder","resources/thunder2_mono.wav");
}

void playAudio()
{
    std::shared_ptr<audio::al::AudioEmitter> em1 = g_audioSystem->getEmitter("thunder");
    em1->enableRelativeListener(false);
    em1->setPosition(5.0f, 5.0f, 5.0f);
    em1->setDirection(0.0f, 0.0f, 0.0f);
    em1->setMinMaxDistance(0.0f, 0.2f);
    em1->setGain(5.0f);
    em1->setLoop(true);
    em1->play();

    std::shared_ptr<audio::al::AudioEmitter> em2 = g_audioSystem->getEmitter("wind");
    em2->enableRelativeListener(true);
    em2->setPosition(5.0f, 5.0f, 5.0f);
    em2->setDirection(0.0f, 0.0f, 0.0f);
    em2->setMinMaxDistance(0.0f, 0.2f);
    em2->setGain(8.0f);
    em2->setLoop(true);
    em2->play();
}

void cleanupAudio()
{
    delete g_audioListener;
    delete g_audioSystem;
}

int main(void)
{
    GLSettings settings;
    settings.windowName = "Hello OpenGL";
    settings.windowHeight = 800;
    settings.windowWidth = 600;

    GLWindow window(settings);

    Shader shader;
    shader.loadShader("shader.vert", TypeShader::VERTEX_SHADER);
    shader.loadShader("shader.frag", TypeShader::FRAGMENT_SHADER);
    shader.createShaderProgram();

    GLint /*mvp_location,*/ vpos_location, vcol_location, tex_location;
    //mvp_location  = glGetUniformLocation(shader.getShaderProgram(), "MVP");
    vpos_location = glGetAttribLocation(shader.getShaderProgram(), "vPos");
    vcol_location = glGetAttribLocation(shader.getShaderProgram(), "vCol");
    tex_location  = glGetAttribLocation(shader.getShaderProgram(), "aTexCoord");

    unsigned int vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(vpos_location,
                          3,
                          GL_FLOAT, GL_FALSE,
                          5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(vpos_location);

    //glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //                      8 * sizeof(float), (void*)(3 * sizeof(float)));

    //glEnableVertexAttribArray(vcol_location);

    // texture coord attribute
    glVertexAttribPointer(tex_location,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          5 * sizeof(float),
                          (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(tex_location);

    unsigned int texture;
    glGenTextures(1, &texture);

    // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping parameters
    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load("box.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    shader.useShaderProgram();

    // Set texture in shader
    shader.setUniformInt("texture1", 0);

    std::vector<glm::vec3> randomPosition;
    randomPosition.push_back(glm::vec3(5.0f, 10.0f, 5.0f));
    //randomPosition.push_back(glm::vec3(0.0f, 0.0f, 5.0f));
    randomPosition.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
    /*for(int i = 0; i < 20; i++)
    {
        randomPosition.push_back(glm::vec3(static_cast <float> (rand() % 15 - 1) ,
                         static_cast <float> (rand() % 10 - 1) ,
                         static_cast <float> (rand() % 5) - 1));
    }*/

    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    // Load audio files
    loadAudio();

    // Play audio sources
    playAudio();


    Sphere sphere(10, 12);
    sphere.SetLocation(vpos_location, tex_location);

    //Cylinder cylinder;
    //cylinder.SetLocation(vpos_location, tex_location);


    /// Debug only rendering lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    g_audioListener->setPosition(g_camera.getCameraPosition());

    // Loop until the user closes the window
    while (!window.checkCloseWindow())
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.updateFpsCounter();
        window.updateframeBufferSize();
        window.updateCamera(deltaTime);

        // wipe the drawing surface clear
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.5f, 0.7f, 0.6f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        shader.useShaderProgram();

        //model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
        //float radius = 6.0f;
        //float camX = sin(glfwGetTime()) * radius;
        //float camZ = cos(glfwGetTime()) * radius;
        //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        projection = glm::perspective(glm::radians(g_camera.getFov()),
                                      static_cast<float>(window.getWidthWindow()) /
                                      static_cast<float>(window.getHeightWindow()),
                                      0.1f,
                                      100.0f);

        //glm::mat4 transform;
        //transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
        //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(transform));

        shader.setUniformMatrix4x4("projection", projection);

        view = g_camera.getLookAtCamera();
        shader.setUniformMatrix4x4("view", view);
        //shader.setUniformMatrix4x4("model", model);

        glBindVertexArray(vao);
        for(unsigned int i = 0; i < 2; i++)
        {
          glm::mat4 model;
          model = glm::translate(model, randomPosition[i]);
          //float angle = 20.0f * i;
          //model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
          //model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
          shader.setUniformMatrix4x4("model", model);

          glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        glm::mat4 model;
        model = glm::translate(model, glm::vec3(-5.f, -0.0f, 5.f));
        //float angle = 20.0f * i;
        //model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        //model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        shader.setUniformMatrix4x4("model", model);
        sphere.Draw();

        //cylinder.Draw();

        // Update audio listener is camera
        g_audioListener->updateListener(
                    g_camera.getCameraPosition(),
                    g_camera.getCameraFront());

        window.checkPoolEvents();
        window.checkSwapBuffer();
    }


    cleanupAudio();


    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);


    return 0;
}
