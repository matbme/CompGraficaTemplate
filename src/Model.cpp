#include "Model.h"
#include "Utils.h"

// Reference to https://learnopengl.com/Model-Loading/Model
Model::Model () {}

void Model::draw () {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].draw ();
    }
}

void Model::setup_meshes () {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].setup();
    }
}

void Model::set_shader_for_all (std::shared_ptr<Shader> shader) {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].setShader (shader);
    }
}

void Model::set_shader_for_textured (std::shared_ptr<Shader> shader) {
    for (int i = 0 ; i < meshes.size() ; i++) {
        if (!meshes[i].textures.empty())
            meshes[i].setShader (shader);
    }
}

void Model::set_shader_for_untextured (std::shared_ptr<Shader> shader) {
    for (int i = 0 ; i < meshes.size() ; i++) {
        if (meshes[i].textures.empty())
            meshes[i].setShader (shader);
    }
}

void Model::rotate (float angle, glm::vec3 axis, bool reset) {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].rotate (angle, axis, reset);
    }
}

void Model::translate (glm::vec3 displacements, bool reset) {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].translate (displacements, reset);
    }
}

void Model::rescale (glm::vec3 scaleFactors, bool reset) {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].rescale (scaleFactors, reset);
    }
}

void Model::update () {
    // Apply animation
    if (this->anim_curve != nullptr) {
        if (anim_frame > this->anim_curve->curve.size () - 1) anim_frame = 0;
        if (anim_frame > 0) {
            auto offset = this->anim_curve->curve[anim_frame] - this->anim_curve->curve[anim_frame - 1];
            this->translate (offset);
        }
        anim_frame++;
    }

    for (auto mesh : meshes) {
        mesh.update ();
    }
}

void Model::highlight () {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].set_highlight(true);
    }
}

void Model::remove_highlight () {
    for (int i = 0 ; i < meshes.size() ; i++) {
        meshes[i].set_highlight(false);
    }
}

void Model::apply (std::string action, std::vector<std::string>::iterator args) {
    switch (Utils::hash (action.c_str ())) {
        case Utils::hash ("position"): {
            this->translate (glm::vec3 (
                std::strtof((++args)->c_str (), NULL),
                std::strtof((++args)->c_str (), NULL),
                std::strtof((++args)->c_str (), NULL)
            ));
            break;
        }
        case Utils::hash ("rotation"): {
            auto angle = std::strtof((++args)->c_str (), NULL);
            this->rotate (
                glm::radians(angle),
                Model::axis_vector((++args)->c_str ()[0])
            );
            break;
        }
        case Utils::hash ("scale"): {
            this->rescale (glm::vec3 (
                std::strtof((++args)->c_str (), NULL),
                std::strtof((++args)->c_str (), NULL),
                std::strtof((++args)->c_str (), NULL)
            ));
            break;
        }
        case Utils::hash ("anim"): {
            auto name = (++args)->c_str ();
            this->anim_curve = Curves::BSpline::instanced[name];
            this->anim_curve->genCurve (100);
            break;
        }
        default: {
            throw std::invalid_argument ("Object has no action `" + action + "`.");
        }
    }
}
