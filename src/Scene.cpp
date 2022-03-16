#include "Scene.h"

Scene::Scene (GLuint width, GLuint height) {
    glfwInit ();

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
    addShaders ("shaders/transformations.vs", "shaders/transformations.frag");

    setupScene ();

    window_resized = true;
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
	window_resized = true;

	// Define the viewport dimensions
	glViewport (0, 0, w, h);
}

void Scene::update () {
	if (KeyEvent::keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);
}
