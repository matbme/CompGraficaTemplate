#include "Scene.h"

bool Scene::window_resized = false;

Scene::Scene (GLuint width, GLuint height) {
    glfwInit ();

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->window_width = width;
    this->window_height = height;

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow (width, height, "CompGraficaTemplate", nullptr, nullptr);
	glfwMakeContextCurrent (window);

    // Set the required callback functions
    glfwSetKeyCallback (window, key_callback);

    // Setando a callback de redimensionamento da janela
    glfwSetWindowSizeCallback (window, resize);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader ((GLADloadproc) glfwGetProcAddress))
        std::cout << "Failed to initialize GLAD" << std::endl;

    // Build and compile our shader program
    addShaders ("shaders/template.vs", "shaders/template.fs");

    setupScene ();

    Scene::window_resized = true;
}

Scene::~Scene () { }

void Scene::addShaders (std::string vertex_path, std::string frag_path) {
    shader = new Shader (vertex_path.c_str(), frag_path.c_str());
}

void Scene::key_callback (GLFWwindow * window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, GL_TRUE);

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
            KeyEvent::keys[key] = KeyEvent::PRESSED;
        }
		else if (action == GLFW_RELEASE) {
            KeyEvent::keys[key] = KeyEvent::UNPRESSED;
        }
	}
}

void Scene::resize (GLFWwindow * window, int w, int h) {
    Scene::window_resized = true;

	// Define the viewport dimensions
	glViewport (0, 0, w, h);
}

void Scene::update () {
	if (KeyEvent::keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Scene::render () {
    glClearColor (0.5f, 0.5f, 0.5f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (Scene::window_resized) {
        setupCamera ();
        Scene::window_resized = false;
    }

    for (Object* obj : objects) {
        obj->update ();
        obj->draw ();
    }
}

void Scene::run () {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents ();
        update ();
        render ();
        glfwSwapBuffers (window);
    }
}

void Scene::finish () {
    glfwTerminate ();
}

void Scene::setupScene () {
    Object* cube = new Object ();
    cube->setPosition(glm::vec3 (0.0f, 0.0f, 0.0f));
    cube->setDimension(glm::vec3 (128.0f, 128.0f, 128.0f));
    cube->setShader(shader);

    objects.push_back(cube);
}

void Scene::setupCamera () {
    model = glm::mat4 (1);
    view = glm::lookAt (glm::vec3 (0.0f, 0.0f, 3.0f),
                        glm::vec3 (0.0f, 0.0f, 0.0f),
                        glm::vec3 (0.0f, 1.0f, 0.0f));

    projection = glm::perspective(45.0f, (GLfloat) window_width / (GLfloat) window_height, 0.1f, 100.0f);

    GLint modelLoc = glGetUniformLocation (shader->ID, "model");
    GLint viewLoc = glGetUniformLocation (shader->ID, "view");
    GLint projLoc = glGetUniformLocation (shader->ID, "projection");

    glUniformMatrix4fv (modelLoc, 1, GL_FALSE, glm::value_ptr (model));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (projection));
}

unsigned int Scene::loadTexture(std::string filename) {
    unsigned int texture;

    // load and create a texture 
    glGenTextures (1, &texture);
    glBindTexture (GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;

    unsigned char *data = stbi_load (filename.c_str (), &width, &height, &nrChannels, 0);

    if (data) {
        if (nrChannels == 3) //jpg, bmp
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else //png
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std::cout << "Failed to load texture" << std::endl;
    stbi_image_free (data);

    glBindTexture (GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

    glActiveTexture (GL_TEXTURE0);

    return texture;
}
