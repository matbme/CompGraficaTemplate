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

    // if (key_is_pressed (GLFW_KEY_X)) {
    //     for (auto obj : objects)
    //         obj->setRotation(glm::radians (2.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
    // }
    //
    // if (key_is_pressed (GLFW_KEY_Y)) {
    //     for (auto obj : objects)
    //         obj->setRotation(glm::radians (2.0f), glm::vec3 (0.0f, 1.0f, 0.0f));
    // }
    //
    // if (key_is_pressed (GLFW_KEY_Z)) {
    //     for (auto obj : objects)
    //         obj->setRotation(glm::radians (2.0f), glm::vec3 (0.0f, 0.0f, 1.0f));
    // }
    //
    // if (key_is_pressed (GLFW_KEY_MINUS)) {
    //     for (auto obj : objects)
    //         obj->setScale (glm::vec3 (0.9f, 0.9f, 0.9f));
    //     KeyEvent::tempLockKey(GLFW_KEY_MINUS, 0.25);
    // }
    //
    // if (key_is_pressed (GLFW_KEY_RIGHT_SHIFT) && key_is_pressed (GLFW_KEY_EQUAL)) {
    //     for (auto obj : objects)
    //         obj->setScale (glm::vec3 (1.1f, 1.1f, 1.1f));
    //     KeyEvent::tempLockKey(GLFW_KEY_EQUAL, 0.25);
    // }

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
    std::string path ("/home/matbme/Downloads/3D_Models/Classic-NoTexture/apple.obj");
    auto model = ModelImporter::Obj::import (path);
    // Object<BasicShapes::Cube>* cube = new Object<BasicShapes::Cube> ();
    // cube->setShader(shader);
    // cube->setTranslation(glm::vec3(1.0f, 0.0f, -0.3f));
    //
    // Object<BasicShapes::Floor>* floor = new Object<BasicShapes::Floor> ();
    // floor->setShader(shader);
    // floor->setTranslation(glm::vec3(-1.0f, 0.0f, 0.9f));

    view = glm::lookAt (cam->cameraPos, cam->cameraPos+cam->cameraFront, cam->cameraUp);

    // push_object (cube);
    // push_object (floor);
    objects.push_back(std::move (model));
    objects[0]->meshes.back().setShader(shader);
    objects[0]->meshes.back().setup();
}
