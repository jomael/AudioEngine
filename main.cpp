#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cstddef>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "al2/AudioSystem.hpp"
#include "al2/ALListener.hpp"

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

struct VertexFormat
{
public:

    glm::vec3 m_position;
    glm::vec4 m_color;
    glm::vec2 m_texture;

    VertexFormat(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texel)
    {
        m_position = position;
        m_color = color;
        m_texture = texel;
    }
};

struct VertexPosTex
{
public:

    glm::vec3 m_position;
    glm::vec2 m_texture;

    VertexPosTex(const glm::vec3 &position, const glm::vec2 &texel)
    {
        m_position = position;
        m_texture = texel;
    }
};


class Cylinder
{
public:

    Cylinder()
    {

        /*float x, y, theta;
        int subs_z = 0, subs_xy = 10;
        int cylinder_height = 10;
        int cylinder_radius = 10;

        for (int j = 0; j <= subs_z + 1; ++j)
        {
            float z = j * (cylinder_height / (float)(subs_z+1));
            for (int i = 0; i < subs_xy; ++i)
            {
                theta = 2.0 * M_PI * i /( float)subs_xy;
                x = sin(theta) * cylinder_radius;
                y = cos(theta) * cylinder_radius;

                //vert.push_back(VertexPosTex(glm::vec3(x, y, z)));
                verts.push_back(glm::vec3(x, y, z));
            }
        }*/

    }

    void SetLocation(GLuint vpos_location, GLuint tex_location)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * verts.size(), &verts[0], GL_STATIC_DRAW);

        //glGenBuffers(1, &ibo);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        glEnableVertexAttribArray(1);
        /*glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE,
                              sizeof(glm::vec3),
                              (void*)(offsetof(glm::vec3, VertexPosTex::m_texture)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(tex_location, 2, GL_FLOAT, GL_TRUE,
                              sizeof(glm::vec3),
                              (void*)(offsetof(glm::vec3, VertexPosTex::m_texture)));*/

        glBindVertexArray(0);
    }

    void Draw()
    {
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, verts.size());
    }

private:

    GLuint m_vao, m_vbo, ibo;

private:

    std::vector<VertexPosTex> vert;
    std::vector<glm::vec3> verts;
    std::vector< GLuint > faces;
};

class Sphere
{
public:

    Sphere(unsigned int rings, unsigned int sectors)
    {
        float const R = 1.0f / (rings - 1);
        float const S = 1.0f / (sectors - 1);

        for(unsigned int r = 0; r < rings; r++)
        {
            for(unsigned int s = 0; s < sectors; s++)
            {

                float const y = sinf(-glm::pi<float>() / 2.0f + glm::pi<float>() * r * R);
                float const x = cosf(2 * glm::pi<float>() * s * S) * sinf(glm::pi<float>() * r * R);
                float const z = sinf(2 * glm::pi<float>() * s * S) * sinf(glm::pi<float>() * r * R);

                glm::vec2 texCoord = glm::vec2(s*S, r*R);
                glm::vec3 vertexPos = glm::vec3(x, y, z);

                vertices.push_back(VertexPosTex(vertexPos, texCoord));
            }
        }

        indices.resize(rings * sectors * 6);
        std::vector<GLushort>::iterator i = indices.begin();
        for(unsigned int r = 0; r < rings - 1; r++)
        {
            for(unsigned int s = 0; s < sectors - 1; s++)
            {
                *i++ = r * sectors + s;
                *i++ = r * sectors + (s + 1);
                *i++ = (r + 1) * sectors + (s + 1);

                *i++ = (r + 1) * sectors + (s + 1);
                *i++ = (r + 1) * sectors + s;
                *i++ = r * sectors + s;
            }
        }
    }

    void SetLocation(GLint vpos_location, GLint tex_location)
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPosTex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPosTex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE,
                              sizeof(VertexPosTex),
                              (void*)(offsetof(VertexPosTex, VertexPosTex::m_texture)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(tex_location, 2, GL_FLOAT, GL_TRUE,
                              sizeof(VertexPosTex),
                              (void*)(offsetof(VertexPosTex, VertexPosTex::m_texture)));

        glBindVertexArray(0);
    }

    void Draw()
    {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
    }

private:

    GLuint m_vao, m_vbo, ibo;
    std::vector<GLushort> indices;
    std::vector<VertexPosTex> vertices;
};


static const char* shaderVertex =
"#version 330 core\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"attribute vec3 vCol;\n"
"attribute vec3 vPos;\n"
"attribute vec2 aTexCoord;\n"
"out vec3 color;\n"
"out vec2 TexCoord;"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(vPos, 1.0);\n"
"    TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"    color = vCol;\n"
"}\n";

static const char* shaderFragment =
"#version 330 core\n"
"varying vec3 color;\n"
"varying vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"void main()\n"
"{\n"
"    //gl_FragColor = vec4(color, 1.0);\n"
"    gl_FragColor = texture(texture1, TexCoord);\n"
"}\n";


enum CameraDirection {
    FORWARD_DIRECTIOM = 0,
    BACKWARD_DIRECTION = 1,
    LEFT_DIRECTION = 2,
    RIGHT_DIRECTION = 3
};

class CameraSettings
{
public:

    CameraSettings() : position(0.0f, 0.0f, 10.0f), up(0.0f, 5.0f, 0.0f),
        front(0.0f, 0.0f, -1.0f), cameraSpeed(5.0), fov(45.0), yaw(-90.0),
        pitch(0.0)
    {
    }

    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;

    float cameraSpeed;
    float fov;
    float yaw;
    float pitch;
};

class FpsCamera
{
public:

    FpsCamera() : m_position(0.0f, 0.0f, 10.0f), m_up(0.0f, 5.0f,  0.0f),
        m_front(0.0f, 0.0f, -1.0f), m_cameraSpeed(5.0f)
    {
    }

    FpsCamera(CameraSettings &settings) : m_settings(settings)
    {
        m_position = settings.position;
        m_up = settings.up;
        m_front = settings.front;
        m_cameraSpeed = settings.cameraSpeed;
        m_fov = settings.fov;
        m_yaw = settings.yaw;
        m_pitch = settings.pitch;
    }

    ~FpsCamera() { }

    glm::vec3 getCameraPosition()
    {
        return m_position;
    }

    glm::vec3 getCameraFront()
    {
        return m_front;
    }

    glm::vec3 getCameraUp()
    {
        return m_up;
    }

    glm::vec3 getCameraRight()
    {
        return m_right;
    }

    float getSpeed()
    {
        return m_cameraSpeed;
    }

    float getFov()
    {
        return m_fov;
    }

    void setFov(float fov)
    {
        m_fov = fov;
    }

    void setFront(glm::vec3 front)
    {
        m_front = front;
    }

    void setRight(glm::vec3 right)
    {
        m_right = right;
    }

    void setUp(glm::vec3 up)
    {
        m_up = up;
    }

    void updateCameraDirection(CameraDirection direction, float deltaTime)
    {
        float cameraSpeed = m_cameraSpeed * deltaTime;
        if(direction == CameraDirection::FORWARD_DIRECTIOM)
        {
            m_position += cameraSpeed * m_front;
        }

        if(direction == CameraDirection::BACKWARD_DIRECTION)
        {
            m_position -= cameraSpeed * m_front;
        }

        if(direction == CameraDirection::LEFT_DIRECTION)
        {
            /*m_position -= glm::normalize(
                          glm::cross(m_front,
                          m_up)) * cameraSpeed;*/
            m_position -= cameraSpeed * m_right;
        }

        if(direction == CameraDirection::RIGHT_DIRECTION)
        {
            /*m_position += glm::normalize(
                          glm::cross(m_front,
                          m_up)) * cameraSpeed;*/

            m_position += cameraSpeed * m_right;
        }
    }

    void updateMouseCameraDirection(float xoffset, float yoffset/*, GLboolean constrainPitch = true*/)
    {
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        m_yaw += xoffset;
        m_pitch += yoffset;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        computeCamera();
    }

    void updateCameraZoom(double xoffset, double yoffset)
    {
        if (m_fov >= 1.0f && m_fov <= 45.0f)
            m_fov -= yoffset;
        if (m_fov <= 1.0f)
            m_fov = 1.0f;
        if (m_fov >= 45.0f)
            m_fov = 45.0f;
    }

    glm::mat4 getLookAtCamera()
    {
       return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void computeCamera()
    {
        glm::vec3 front;
        front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
        front.y = sinf(glm::radians(m_pitch));
        front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
        m_front = glm::normalize(front);

        /*std::cerr << "front x : " << front.x
                  << " front y : " << front.y
                  << " front z : " << front.z << std::endl;*/

        //m_right = glm::normalize(glm::cross(m_front, m_up));
        //m_up    = glm::normalize(glm::cross(m_right, m_front));
    }

public:

    CameraSettings m_settings;

private:

    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_front;
    glm::vec3 m_right;

    float m_cameraSpeed;
    float m_fov;
    float m_yaw;
    float m_pitch;
};

CameraSettings settings;
FpsCamera g_camera(settings);

bool firstMouse = true;
double lastX =  800.0 / 2.0;
double lastY =  600.0 / 2.0;

class GLSettings
{
public:

    GLSettings() : majorVersion(3), minorVersion(3),
        windowHeight(640), windowWidth(480), windowName("Hello") { }

    // Major version OpenGL, Minor version OpenGL
    int majorVersion, minorVersion;

    // Window width, height,
    int windowHeight, windowWidth;

    // Main window name
    std::string windowName;
};

class GLWindow
{
public:

    GLWindow(GLSettings &settings) : m_settings(settings)
    {

        if(!glfwInit())
        {
            std::cout << "Failed initilize GLFW library!" << std::endl;
            glfwTerminate();
        }

        glfwSetErrorCallback(errorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_settings.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_settings.minorVersion);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        createWindow(m_settings.windowHeight,
                     m_settings.windowWidth,
                     m_settings.windowName);
    }

    ~GLWindow()
    {
        glfwTerminate();
    }

    int getWidthWindow()
    {
        return m_settings.windowWidth;
    }

    int getHeightWindow()
    {
        return m_settings.windowHeight;
    }

    int checkCloseWindow()
    {
        return glfwWindowShouldClose(m_window);
    }

    void checkPoolEvents()
    {
        glfwPollEvents();
    }

    void checkSwapBuffer()
    {
        glfwSwapBuffers(m_window);
    }

    void updateFpsCounter()
    {
        static double prevSecond = glfwGetTime();
        static int frameCounter = 0;

        double currentSecond = glfwGetTime();
        double elapsedSecond = currentSecond - prevSecond;

        if(elapsedSecond > 0.25)
        {
            prevSecond = currentSecond;
            double fps = static_cast<double>(frameCounter) / elapsedSecond;

            char buffer[256];
            sprintf(buffer, "fps: %.2f", fps);
            glfwSetWindowTitle(m_window, buffer);
            frameCounter = 0;
        }

        frameCounter++;
    }

    static void errorCallback(int error, const char* description)
    {
        fprintf(stderr, "Error callback: %s\n", description);
    }

    /*static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {

    }*/

    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        g_camera.updateCameraZoom(xoffset, yoffset);
    }

    static void mouseCursorPositionCallback(GLFWwindow* window, double x, double y)
    {
        if (firstMouse)
        {
            lastX = x;
            lastY = y;
            firstMouse = false;
        }

        float xoffset = x - lastX;
        float yoffset = lastY - y;

        lastX = x;
        lastY = y;

        g_camera.updateMouseCameraDirection(xoffset, yoffset);
    }

    static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
               glfwSetWindowShouldClose(window, true);
        }
    }

    void getFramebufferSize(int *width, int *height)
    {
        glfwGetFramebufferSize(m_window, width, height);
    }

    void updateframeBufferSize()
    {
        int width, height;
        glfwGetFramebufferSize(m_window, &width, &height);
        glViewport(0, 0, width, height);
    }

    void updateCamera(float deltaTime)
    {
        if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            g_camera.updateCameraDirection(CameraDirection::FORWARD_DIRECTIOM,
                                     deltaTime);
        }

        if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        {
            g_camera.updateCameraDirection(CameraDirection::BACKWARD_DIRECTION,
                                     deltaTime);
        }

        if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        {
            g_camera.updateCameraDirection(CameraDirection::LEFT_DIRECTION,
                                     deltaTime);
        }

        if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        {
            g_camera.updateCameraDirection(CameraDirection::RIGHT_DIRECTION,
                                     deltaTime);
        }
    }

protected:

    void createWindow(int width, int height, std::string name)
    {
        m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if(!m_window)
        {
            std::cout << "Failed create GLFW window!" << std::endl;
            glfwTerminate();
        }

       glfwMakeContextCurrent(m_window);
       glfwSetKeyCallback(m_window, keyboardCallback);
       glfwSetCursorPosCallback(m_window, mouseCursorPositionCallback);
       glfwSetScrollCallback(m_window, scrollCallback);
       glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
       glewExperimental = GL_TRUE;
       glewInit();
    }

private:

    GLSettings m_settings;
    GLFWwindow *m_window;
};

enum TypeShader
{
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    GEOMETRY_SHADER = GL_GEOMETRY_SHADER
};

class Shader
{
public:

    Shader() : m_vertexShader(0), m_fragmentShader(0),
        m_isVertexShader(false), m_isFragmentShader(false)
    { }

    ~Shader() {}

    void loadShader(const std::string &shader, TypeShader type)
    {
        if(type == TypeShader::VERTEX_SHADER)
        {
            //const char * vertex_shader = getShaderReader(shader);
            m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(m_vertexShader, 1, &shaderVertex, NULL);
            glCompileShader(m_vertexShader);
            shaderCompileStatus(m_vertexShader, __FILE__ , __LINE__);
            m_isVertexShader = true;
        }

        if(type == TypeShader::FRAGMENT_SHADER)
        {
            //const char *fragment_shader = getShaderReader(shader);
            m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(m_fragmentShader, 1, &shaderFragment, NULL);
            glCompileShader(m_fragmentShader);
            shaderCompileStatus(m_fragmentShader, __FILE__ , __LINE__);
            m_isFragmentShader = true;
        }
    }

    void useShaderProgram()
    {
        glUseProgram(m_id);
    }

    GLuint getShaderProgram()
    {
        return m_id;
    }

    void createShaderProgram()
    {
        m_id = glCreateProgram();

        if(m_isVertexShader)
        {
            glAttachShader(m_id, m_vertexShader);
        }
        if(m_isFragmentShader)
        {
            glAttachShader(m_id, m_fragmentShader);
        }

        glLinkProgram(m_id);
        programCompileStatus(m_id, __FILE__ , __LINE__);
    }


    void setUniformMatrix4x4(const std::string &type, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, type.c_str()), 1, GL_FALSE, &matrix[0][0]);
    }

    void setUniformInt(const std::string &type, const GLint value)
    {
        glUniform1i(glGetUniformLocation(m_id, type.c_str()), value);
    }

protected:

    void shaderCompileStatus(GLuint shader, std::string file, int line)
    {
        GLint isCompiled;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if(!isCompiled)
        {
            int logLenght;
            GLchar log[1024];
            glGetShaderInfoLog(shader, 1024, &logLenght, log);
            std::cerr << "[WARN] Shader compilation error : "  << log <<
                         " - Log lenght: " << logLenght <<
                         " - File: " << file <<
                         " - Line: " << line <<
                         "\n";
        }
        else
        {
            int logLenght;
            GLchar log[1024];
            glGetShaderInfoLog(shader, 1024, &logLenght, log);
            std::cerr << "[INFO] Shader compilation success ! " << log <<
                         " - Log lenght: " << logLenght <<
                         " - File: " << file <<
                         " - Line: " << line <<
                         "\n";
        }
    }

    void programCompileStatus(GLuint program, std::string file, int line)
    {
        GLint isCompiled;

        glGetProgramiv(program, GL_LINK_STATUS, &isCompiled);
        if(!isCompiled)
        {
            int logLenght;
            GLchar log[1024];
            glGetProgramInfoLog(program, 1024, &logLenght, log);
            std::cerr << "[WARN] Program linker error : "  << log <<
                         " - Log lenght: " << logLenght <<
                         " - File: " << file <<
                         " - Line: " << line <<
                         "\n";
        }
        else
        {
            int logLenght;
            GLchar log[1024];
            glGetProgramInfoLog(program, 1024, &logLenght, log);
            std::cerr << "[INFO] Pogram linker success ! " << log <<
                         " - Log lenght: " << logLenght <<
                         " - File: " << file <<
                         " - Line: " << line <<
                         "\n";
        }
    }

private:

    // Shader program id
    GLuint m_id;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;

    bool m_isVertexShader;
    bool m_isFragmentShader;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// Audio example
/////////////////////////////////////////////////////////////////////////////////////////////
//audio::al::AudioSystem *g_audioSystem;
//audio::al::Listener *g_listener;

audio::newapi::AudioSystem *g_audioSystem = nullptr;
audio::newapi::AudioListener *g_audioListener = nullptr;

void loadAudio()
{
    g_audioSystem = new audio::newapi::AudioSystem();
    g_audioListener = new audio::newapi::AudioListener();
    g_audioSystem->loadFromFile("wind", "resources/wind.ogg");
    g_audioSystem->loadFromFile("thunder","resources/thunder2_mono.wav");
}

void playAudio()
{
    std::shared_ptr<audio::newapi::AudioEmitter> emitter1 = g_audioSystem->getEmitter("thunder");
    emitter1->enableRelativeListener(true);
    emitter1->setPosition(5.0f, 5.0f, 5.0f);
    emitter1->setDirection(0.0f, 0.0f, 0.0f);
    emitter1->setMinMaxDistance(0.0f, 0.2f);
    emitter1->setGain(8.0f);
    emitter1->setLoop(true);
    emitter1->play();
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
    //randomPosition.push_back(glm::vec3(5.0f, 10.0f, 5.0f));
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
