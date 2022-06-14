#include "Object.h"

#include "ModelImport.h"

using namespace ModelImporter;

Object::Object (std::string model_filename) {
    this->model_filename = model_filename;
    Obj::import (this);
}

Object::Object (std::vector<std::pair<std::string, std::any>> params) {
    ObjectSetupArgs args;
    for (const auto &[name, value] : params) {
        switch (Utils::hash (name.c_str ())) {
            case Utils::hash ("load"): {
                auto value_str = std::any_cast<std::string> (value);
                this->model_filename = value_str.substr (1, value_str.size () - 2);
                Obj::import (this);
                break;
            }
            case Utils::hash ("shader"): {
                args.shader = std::any_cast<std::shared_ptr<Shader>> (value);
                break;
            }
            case Utils::hash ("position"): {
                /* return this->position; */
                break;
            }
            case Utils::hash ("rotation"): {
                /* return this->rotation; */
                break;
            }
            case Utils::hash ("scale"): {
                /* return this->scale; */
                break;
            }
            default: {
                throw std::invalid_argument ("Invalid argument `" + name + "` for Object setup.");
            }
        }
    }
    Object::setup(args);
}

void Object::add_model (std::unique_ptr<Model> model) {
    assert (this->model == nullptr);
    this->model.swap(model);
}

std::unique_ptr<Model>& Object::get_model () {
    if (this->model == nullptr)
        throw std::runtime_error ("Trying to access model from uninitialized object");

    return this->model;
}

void Object::setup (ObjectSetupArgs args) {
    if (this->model == nullptr)
        throw std::runtime_error ("Trying to access model from uninitialized object");

    this->model->set_shader_for_all (args.shader);
    if (args.position) this->model->translate (*args.position);
    if (args.rotation) this->model->rotate (args.rotation->first, args.rotation->second);
    if (args.scale) this->model->rescale (*args.scale);
}

void Object::apply (Object *instance, std::string action, std::vector<std::string>::iterator args) {
    this->get_model ().get ()->apply(action, args);
}
