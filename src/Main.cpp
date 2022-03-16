/* Template para desenvolvimento de atividades da disciplina
 * Computação Gráfica, ministrada pela prof. Rossana Baptista Queiroz.
 *
 * Developer: Mateus Melchiades <mateusbme@edu.unisinos.br>
 */

#include "KeyEvent.h"
#include "Scene.h"

int main () {
    Scene *main_scene = new Scene (1920, 1080);

    KeyEvent *main_scene_key_event = new KeyEvent ();
    main_scene->key_event = main_scene_key_event;
    main_scene->run ();
    main_scene->finish();

    return EXIT_SUCCESS;
}
