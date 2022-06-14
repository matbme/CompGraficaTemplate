/* Template para desenvolvimento de atividades da disciplina
 * Computação Gráfica, ministrada pela prof. Rossana Baptista Queiroz.
 *
 * Developer: Mateus Melchiades <mateusbme@edu.unisinos.br>
 */

#include "KeyEvent.h"
/* #include "Scenes/MainScene.h" */

#include "Level.h"

static inline const bool key_is_pressed (int key) {
    return KeyEvent::keys[key] == KeyEvent::PRESSED;
}

int main () {
    auto level = Level::load_scene_from_level("levels/simple.lvl");

    level->update_func = [](std::shared_ptr<Camera>& cam, GLFWwindow *window, std::vector<std::unique_ptr<Object>>& objects) {
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
                obj->get_model ()->rotate (glm::radians (2.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
        }

        if (key_is_pressed (GLFW_KEY_Y)) {
            for (auto&& obj : objects)
                obj->get_model ()->rotate (glm::radians (2.0f), glm::vec3 (0.0f, 1.0f, 0.0f));
        }

        if (key_is_pressed (GLFW_KEY_Z)) {
            for (auto&& obj : objects)
                obj->get_model ()-> rotate (glm::radians (2.0f), glm::vec3 (0.0f, 0.0f, 1.0f));
        }

        if (key_is_pressed (GLFW_KEY_MINUS)) {
            for (auto&& obj : objects)
                obj->get_model ()->rescale (glm::vec3 (0.9f, 0.9f, 0.9f));
            KeyEvent::tempLockKey(GLFW_KEY_MINUS, 0.25);
        }

        if (key_is_pressed (GLFW_KEY_RIGHT_SHIFT) && key_is_pressed (GLFW_KEY_EQUAL)) {
            for (auto&& obj : objects)
                obj->get_model ()->rescale (glm::vec3 (1.1f, 1.1f, 1.1f));
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
    };

    level->run ();
    level->finish();

    /* MainScene *main_scene = new MainScene (1920, 1080, "template"); */

    /* main_scene->run (); */
    /* main_scene->run (); */
    /* main_scene->finish(); */
    /* main_scene->finish(); */

    return EXIT_SUCCESS;
}
