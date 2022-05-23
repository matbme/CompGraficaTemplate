#ifndef LIGHT_H
#define LIGHT_H

#include "Shader.h"
#include <glm/glm.hpp>
#include <memory>

class Light {
public:
    Light (glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }
    ~Light () {};

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    virtual void add_to_shader (std::shared_ptr<Shader> shader, std::string name) { };
};

class DirectionalLight : public Light {
public:
    DirectionalLight (glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Light (ambient, diffuse, specular) {
        this->direction = direction;
    }

    glm::vec3 direction;

    void add_to_shader (std::shared_ptr<Shader> shader, std::string name) override {
        shader->setVec3 (name + ".direction", this->direction);
        shader->setVec3 (name + ".ambient", this->ambient);
        shader->setVec3 (name + ".diffuse", this->diffuse);
        shader->setVec3 (name + ".specular", this->specular);
    }
};

class PointLight : public Light {
public:
    PointLight (glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
    : Light (ambient, diffuse, specular) {
        this->position = position;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
    }

    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    void add_to_shader (std::shared_ptr<Shader> shader, std::string name) override {
        shader->setVec3  (name + ".position", this->position);
        shader->setVec3  (name + ".ambient", this->ambient);
        shader->setVec3  (name + ".diffuse", this->diffuse);
        shader->setVec3  (name + ".specular", this->specular);
        shader->setFloat (name + ".constant", this->constant);
        shader->setFloat (name + ".linear", this->linear);
        shader->setFloat (name + ".quadratic", this->quadratic);
    }
};

#endif
