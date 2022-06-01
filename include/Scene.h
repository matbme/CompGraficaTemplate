#ifndef SCENE_H
#define SCENE_H

// Builtin
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Local
#include "Light.h"
#include "Model.h"
#include "Object.h"
#include "Shader.h"
#include "KeyEvent.h"
#include "Camera.h"

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
    virtual void update () {}
    void render ();

    // Import de elementos na cena
	void addShaders (std::string vertex_path, std::string frag_path);
	virtual void setupScene () {}
	void setupCamera ();
	unsigned int loadTexture (std::string filename);
    unsigned int add_object (std::unique_ptr<Object>& object);

    // Callbacks de input
	static void key_callback (GLFWwindow* window, int key, int scancode, int action, int mode);

protected:
    // Janela, presumindo uma unica janela
    GLFWwindow *window;
    static bool window_resized;

    // Dimensoes da janela
    static GLuint window_width;
    static GLuint window_height;

    // Programa de shader, presumindo um unico par de shaders
    std::shared_ptr<Shader> shader;

    // Parameteros do shader
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    GLint modelLoc;
    GLint viewLoc;
    GLint projLoc;

    // Camera
    std::shared_ptr<Camera> cam;

    // Objetos na cena
    std::vector<std::unique_ptr<Object>> objects;

    // Lights
    std::unique_ptr<DirectionalLight> dirLight;
    std::vector<std::unique_ptr<PointLight>> pointLights;

    // Tecla
    static inline const bool key_is_pressed (int key) {
        return KeyEvent::keys[key] == KeyEvent::PRESSED;
    }
};

#endif
