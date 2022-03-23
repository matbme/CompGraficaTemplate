#include "Scenes/MainScene.h"

void MainScene::update () {
	if (keypress (GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);

    if (keypress (GLFW_KEY_X)) {
        for (auto obj : objects)
            obj->setRotation(glm::radians (2.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
    }

    if (keypress (GLFW_KEY_Y)) {
        for (auto obj : objects)
            obj->setRotation(glm::radians (2.0f), glm::vec3 (0.0f, 1.0f, 0.0f));
    }

    if (keypress (GLFW_KEY_Z)) {
        for (auto obj : objects)
            obj->setRotation(glm::radians (2.0f), glm::vec3 (0.0f, 0.0f, 1.0f));
    }

    if (keypress (GLFW_KEY_MINUS)) {
        for (auto obj : objects)
            obj->setScale (glm::vec3 (0.9f, 0.9f, 0.9f));
        KeyEvent::tempLockKey(GLFW_KEY_MINUS, 0.25);
    }

    if ((keypress (GLFW_KEY_LEFT_SHIFT) || keypress (GLFW_KEY_RIGHT_SHIFT)) && keypress (GLFW_KEY_EQUAL)) {
        for (auto obj : objects)
            obj->setScale (glm::vec3 (1.1f, 1.1f, 1.1f));
        KeyEvent::tempLockKey(GLFW_KEY_EQUAL, 0.25);
    }
}

void MainScene::setupScene () {
    Object<BasicShapes::Cube>* cube = new Object<BasicShapes::Cube> ();
    cube->setShader(shader);
    cube->setTranslation(glm::vec3(1.0f, 0.0f, -0.3f));

    Object<BasicShapes::Floor>* floor = new Object<BasicShapes::Floor> ();
    floor->setShader(shader);
    floor->setTranslation(glm::vec3(-1.0f, 0.0f, 0.9f));

    push_object (cube);
    push_object (floor);
}
