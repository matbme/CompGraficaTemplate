#include "Object.h"

#include "ModelImport.h"

using namespace ModelImporter;

Object::Object (std::string model_filename) {
        this->model_filename = model_filename;
        Obj::import(this);
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
