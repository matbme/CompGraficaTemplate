#include "Model.h"

// Reference to https://learnopengl.com/Model-Loading/Model
Model::Model () {}

void Model::draw () {
    for (auto mesh : meshes) {
        mesh.draw ();
    }
}

void Model::setup_meshes () {
    // For some reason, using foreach doesn't work here
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].setup();
    }
}

void Model::set_shader(Shader *shader) {
    for (auto mesh : meshes) {
        mesh.setShader (shader);
    }
}
