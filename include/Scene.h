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
#include <GLFW/glfw3.h>

// Local
#include "Shader.h"
#include "Object.h"
#include "KeyEvent.h"

class Scene {
public:
    Scene (GLuint width, GLuint height);
    ~Scene ();

    // Atualiza viewport e dimensoes
	static void resize (GLFWwindow* window, int width, int height);

    // Lifecycle da cena
	void run ();
	void finish ();

    // Gerenciamento do runtime
    void update ();
    void render ();

    // Import de elementos na cena
	void addShaders (std::string vertex_path, std::string frag_path);
	void setupScene ();
	void setupCamera ();
	unsigned int loadTexture (std::string filename); 

    // Input
    static KeyEvent *key_event;
	static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mode);

private:
    // Janela, presumindo uma unica janela
    GLFWwindow *window;
    static bool window_resized;

    // Programa de shader, presumindo um unico par de shaders
    Shader *shader;

    // Camera
    glm::vec4 model;
    glm::vec4 view;
    glm::mat4 projection;

    // Objetos na cena
    std::vector <Object*> objects;
};

#endif
