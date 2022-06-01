#ifndef OBJECT_H
#define OBJECT_H

#include "Model.h"

#include <memory>
#include <optional>
#include <string>

struct ObjectSetupArgs {
    std::shared_ptr<Shader> shader;
    std::optional<glm::vec3> position = std::nullopt;
    std::optional<std::pair<float, glm::vec3>> rotation = std::nullopt;
    std::optional<glm::vec3> scale = std::nullopt;
};

class Object {
public:
    Object (std::string model_filename);

    std::string get_model_filename () { return this->model_filename; }
    std::string get_name () { return this->name; }
    std::unique_ptr<Model>& get_model ();

    void set_name (std::string name) { this->name = name; }

    void add_model (std::unique_ptr<Model> model);
    void setup (ObjectSetupArgs args);
private:
    std::string model_filename;
    std::unique_ptr<Model> model;
    std::string name = "";
};

#endif
