#include "Scene.h"

bool Scene::window_resized = false;
GLuint Scene::window_width = 0;
GLuint Scene::window_height = 0;

Scene::Scene (GLuint width,
              GLuint height,
              std::string window_name,
              std::string vertex_shader,
              std::string fragment_shader)
{
    glfwInit ();

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load (true);

    Scene::window_width = width;
    Scene::window_height = height;

    // Creates a new camera which will be our eye and binds it to mouse and scroll callbacks
    this->cam = std::make_shared<Camera>();
    Camera::bind_instance (cam);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow (width, height, window_name.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent (window);

    // Disable mouse cursor
    glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the required callback functions
    glfwSetKeyCallback (window, key_callback);
    glfwSetCursorPosCallback (window, Camera::mouse_callback);
    glfwSetScrollCallback (window, Camera::scroll_callback);
    glfwSetMouseButtonCallback (window, Camera::mouse_button_callback);

    // Setando a callback de redimensionamento da janela
    glfwSetWindowSizeCallback (window, resize);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader ((GLADloadproc) glfwGetProcAddress))
        std::cout << "Failed to initialize GLAD" << std::endl;

    Scene::window_resized = true;

    if (vertex_shader != "" && fragment_shader != "")
        this->shader = std::make_shared<Shader> (
            vertex_shader.c_str(),
            fragment_shader.c_str()
        );
}

Scene::~Scene () { }

void Scene::addShaders (std::string vertex_path, std::string frag_path) {
    shader = std::make_shared<Shader> (vertex_path.c_str(), frag_path.c_str());
}

void Scene::key_callback (GLFWwindow * window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, GL_TRUE);

	if (key >= 0 && key < 1024) {
        KeyEvent::updateKeyStatus (key, action);
	}
}

void Scene::resize (GLFWwindow * window, int w, int h) {
    Scene::window_width = w;
    Scene::window_height = h;
    Scene::window_resized = true;

	// Define the viewport dimensions
	glViewport (0, 0, w, h);
}

void Scene::render () {
    glClearColor (0.5f, 0.5f, 0.5f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (Scene::window_resized) {
        setupCamera ();
        Scene::window_resized = false;
    }

    for (auto&& obj : objects) {
        obj->get_model ()->update ();
        obj->get_model ()->draw ();
    }

	GLint viewPosLoc = glGetUniformLocation(shader->ID, "viewPos");
	glUniform3f(viewPosLoc, cam->cameraPos.x, cam->cameraPos.y, cam->cameraPos.z);
}

void Scene::run () {
    view = glm::lookAt (cam->cameraPos, cam->cameraPos+cam->cameraFront, cam->cameraUp);
    // Setup lights
    this->dirLight->add_to_shader (this->shader, "dirLight");
    for (int i = 0 ; i < this->pointLights.size () ; i++)
        this->pointLights[i]->add_to_shader (this->shader, "pointLights[" + std::to_string(i) + "]");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents ();
        update_func (this->cam, this->window, this->objects);

        if (cam->changed ()) {
            view = glm::lookAt (cam->cameraPos, cam->cameraPos+cam->cameraFront, cam->cameraUp);
            projection = glm::perspective(
                glm::radians(cam->fov),
                (GLfloat) Scene::window_width / (GLfloat) Scene::window_height,
                0.1f,
                100.0f
            );
            glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));
            glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (projection));
        }

        render ();
        glfwSwapBuffers (window);
    }
}

void Scene::finish () {
    glfwTerminate ();
}

void Scene::setupCamera () {
    model = glm::mat4 (1); // Matriz identidade
    modelLoc = glGetUniformLocation (shader->ID, "model");

    view = glm::mat4 (1); // Matriz identidade
    viewLoc = glGetUniformLocation (shader->ID, "view");

    projection = glm::mat4 (1); // Matriz identidade
    projLoc = glGetUniformLocation (shader->ID, "projection");

    model = glm::rotate (model, glm::radians (90.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv (modelLoc, 1, GL_FALSE, glm::value_ptr (model));

    view = glm::lookAt (glm::vec3 (0.0f, 0.0f, 3.0f),
                        glm::vec3 (0.0f, 0.0f, 0.0f),
                        glm::vec3 (0.01, 1.0f, 0.0f));
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));

    projection = glm::perspective (45.0f, (GLfloat) Scene::window_width / (GLfloat) Scene::window_height, 0.1f, 100.0f);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (projection));

	glEnable (GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_FRAMEBUFFER_SRGB);

    Camera::scene_width = &Scene::window_width;
    Camera::scene_height = &Scene::window_height;
    Camera::proj_mat = &this->projection;
    Camera::view_mat = &this->view;
    Camera::objects = &this->objects;

    Camera::initialized = true;
}

unsigned int Scene::add_object (std::unique_ptr<Object>& object) {
    this->objects.push_back (std::move (object));
    return this->objects.size ();
}

void Scene::add_dirLight (std::unique_ptr<DirectionalLight>& light) {
    assert (this->dirLight == nullptr);
    this->dirLight.swap(light);
}

void Scene::add_pointLight (std::unique_ptr<PointLight>& light) {
    this->pointLights.push_back (std::move(light));
}
