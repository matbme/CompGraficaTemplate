#include "Scenes/MainScene.h"
#include "ModelImport.h"

void MainScene::update () {
	if (key_is_pressed (GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);

    if (key_is_pressed (GLFW_KEY_W)) {
        cam->cameraPos += cam->cameraSpeed * cam->cameraFront;
        cam->cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_S)) {
        cam->cameraPos -= cam->cameraSpeed * cam->cameraFront;
        cam->cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_A)) {
        cam->cameraPos -= glm::normalize(glm::cross(cam->cameraFront, cam->cameraUp)) * cam->cameraSpeed;
        cam->cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_D)) {
        cam->cameraPos += glm::normalize(glm::cross(cam->cameraFront, cam->cameraUp)) * cam->cameraSpeed;
        cam->cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_X)) {
        for (auto&& obj : objects)
            obj->rotate (glm::radians (2.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
    }

    if (key_is_pressed (GLFW_KEY_Y)) {
        for (auto&& obj : objects)
            obj->rotate (glm::radians (2.0f), glm::vec3 (0.0f, 1.0f, 0.0f));
    }

    if (key_is_pressed (GLFW_KEY_Z)) {
        for (auto&& obj : objects)
            obj->rotate (glm::radians (2.0f), glm::vec3 (0.0f, 0.0f, 1.0f));
    }

    if (key_is_pressed (GLFW_KEY_MINUS)) {
        for (auto&& obj : objects)
            obj->rescale (glm::vec3 (0.9f, 0.9f, 0.9f));
        KeyEvent::tempLockKey(GLFW_KEY_MINUS, 0.25);
    }

    if (key_is_pressed (GLFW_KEY_RIGHT_SHIFT) && key_is_pressed (GLFW_KEY_EQUAL)) {
        for (auto&& obj : objects)
            obj->rescale (glm::vec3 (1.1f, 1.1f, 1.1f));
        KeyEvent::tempLockKey(GLFW_KEY_EQUAL, 0.25);
    }

    if (key_is_pressed (GLFW_KEY_LEFT_SHIFT)) {
        cam->cameraPos += cam->cameraSpeed * cam->cameraUp;
        cam->cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_LEFT_CONTROL)) {
        cam->cameraPos -= cam->cameraSpeed * cam->cameraUp;
        cam->cameraUpdated = true;
    }

    if (cam->changed ()) {
        view = glm::lookAt (cam->cameraPos, cam->cameraPos+cam->cameraFront, cam->cameraUp);
        projection = glm::perspective(glm::radians(cam->fov), (GLfloat) Scene::window_width / (GLfloat) Scene::window_height, 0.1f, 100.0f);

        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (projection));
    }
}

void MainScene::setupScene () {
    this->addShaders ("shaders/template_vs.glsl", "shaders/template_fs.glsl");

    // Point lights are cubes
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    // Load models
    // Male Pikachu
    std::string path ("/home/matbme/Downloads/3D_Models/Pokemon/Pikachu.obj");
    auto pikachu = ModelImporter::Obj::import (path);
    pikachu->set_shader_for_all (shader);
    this->add_object (pikachu);

    // Female Pikachu
    path = "/home/matbme/Downloads/3D_Models/Pokemon/PikachuF.obj";
    auto pikachuF = ModelImporter::Obj::import (path);
    pikachuF->set_shader_for_all (shader);
    pikachuF->translate (glm::vec3 (8.0f, 0.0f, 0.0f));
    pikachuF->rescale (glm::vec3 (0.1f, 0.1f, 0.1f));
    this->add_object (pikachuF);

    // Light cubes
    path = "/home/matbme/Downloads/3D_Models/Cube/cube.obj";
    for (auto pos : pointLightPositions) {
        auto light_cube = ModelImporter::Obj::import (path);
        light_cube->set_shader_for_all (shader);
        light_cube->translate (pos);
        this->add_object(light_cube);
    }

    // Load lights
    auto ambient_light  = glm::vec3 (0.2f, 0.2f, 0.2f);
    auto diffuse_light  = glm::vec3 (0.5f, 0.5f, 0.5f);
    auto specular_light = glm::vec3 (1.0f, 1.0f, 1.0f);

    this->dirLight = std::make_unique<DirectionalLight> (
        glm::vec3 (-0.2f, -1.0f, -0.3f),
        ambient_light,
        diffuse_light,
        specular_light
    );
    this->dirLight->add_to_shader (this->shader, "dirLight");

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    for (auto pos : pointLightPositions) {
        auto pl = std::make_unique<PointLight> (
            pos,
            ambient_light, diffuse_light, specular_light,
            constant, linear, quadratic
        );

        this->pointLights.push_back (std::move (pl));
    }

    for (int i = 0 ; i < 4 ; i++)
        this->pointLights[i]->add_to_shader (this->shader, "pointLights[" + std::to_string(i) + "]");

    view = glm::lookAt (cam->cameraPos, cam->cameraPos+cam->cameraFront, cam->cameraUp);
}
