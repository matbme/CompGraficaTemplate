#ifndef SCENE_H
#define SCENE_H

// Builtin
#include <iostream>
#include <string>
#include <vector>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// GLFW
// #include <GLFW/glfw3.h>

// Local
#include "Shader.h"
#include "Object.h"
#include "KeyEvent.h"

class Scene {
public:
    Scene (GLuint width, GLuint height, std::string window_name);
    ~Scene ();

    // Atualiza viewport e dimensoes
	static void resize (GLFWwindow* window, int width, int height);

    // Lifecycle da cena
	void run ();
	void finish ();

    // Gerenciamento do runtime
    virtual void update ();
    void render ();

    // Import de elementos na cena
	void addShaders (std::string vertex_path, std::string frag_path);
	virtual void setupScene ();
	void setupCamera ();
	unsigned int loadTexture (std::string filename); 

    // Input
    // static std::array <KeyEvent::KeyStatus, 1024>* keys;
	static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mode);

private:
    // Janela, presumindo uma unica janela
    GLFWwindow *window;
    static bool window_resized;

    // Dimensoes da janela
    static GLuint window_width;
    static GLuint window_height;

    // Programa de shader, presumindo um unico par de shaders
    Shader *shader;

    // Camera
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    GLint modelLoc;
    GLint viewLoc;
    GLint projLoc;

    // Objetos na cena
    std::vector <Object*> objects;
};

#endif
