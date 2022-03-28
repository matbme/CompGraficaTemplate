#include "Scenes/MainScene.h"

void MainScene::update () {
	if (key_is_pressed (GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);

    if (key_is_pressed (GLFW_KEY_W)) {
        cameraPos += cameraSpeed * cameraFront;
        cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_S)) {
        cameraPos -= cameraSpeed * cameraFront;
        cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_A)) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_D)) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_X)) {
        for (auto obj : objects)
            obj->setRotation(glm::radians (2.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
    }

    if (key_is_pressed (GLFW_KEY_Y)) {
        for (auto obj : objects)
            obj->setRotation(glm::radians (2.0f), glm::vec3 (0.0f, 1.0f, 0.0f));
    }

    if (key_is_pressed (GLFW_KEY_Z)) {
        for (auto obj : objects)
            obj->setRotation(glm::radians (2.0f), glm::vec3 (0.0f, 0.0f, 1.0f));
    }

    if (key_is_pressed (GLFW_KEY_MINUS)) {
        for (auto obj : objects)
            obj->setScale (glm::vec3 (0.9f, 0.9f, 0.9f));
        KeyEvent::tempLockKey(GLFW_KEY_MINUS, 0.25);
    }

    if (key_is_pressed (GLFW_KEY_RIGHT_SHIFT) && key_is_pressed (GLFW_KEY_EQUAL)) {
        for (auto obj : objects)
            obj->setScale (glm::vec3 (1.1f, 1.1f, 1.1f));
        KeyEvent::tempLockKey(GLFW_KEY_EQUAL, 0.25);
    }

    if (key_is_pressed (GLFW_KEY_LEFT_SHIFT)) {
        cameraPos += cameraSpeed * cameraUp;
        cameraUpdated = true;
    }

    if (key_is_pressed (GLFW_KEY_LEFT_CONTROL)) {
        cameraPos -= cameraSpeed * cameraUp;
        cameraUpdated = true;
    }

    if (cameraUpdated) {
        view = glm::lookAt (cameraPos, cameraPos+cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(fov), (GLfloat) Scene::window_width / (GLfloat) Scene::window_height, 0.1f, 100.0f);  

        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (projection));
    }
}

void MainScene::setupScene () {
    Object<BasicShapes::Cube>* cube = new Object<BasicShapes::Cube> ();
    cube->setShader(shader);
    cube->setTranslation(glm::vec3(1.0f, 0.0f, -0.3f));

    Object<BasicShapes::Floor>* floor = new Object<BasicShapes::Floor> ();
    floor->setShader(shader);
    floor->setTranslation(glm::vec3(-1.0f, 0.0f, 0.9f));

    view = glm::lookAt (cameraPos, cameraPos+cameraFront, cameraUp);

    push_object (cube);
    push_object (floor);
}
