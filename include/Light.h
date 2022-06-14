#ifndef LIGHT_H
#define LIGHT_H

#include "Shader.h"
#include "Utils.h"

#include <glm/glm.hpp>

#include <any>
#include <memory>
#include <vector>

class Light {
public:
    Light (glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
    }
    ~Light () {};

    Light (std::vector<std::pair<std::string, std::any>> params) {
        for (const auto & [name, value] : params) {
            try {
                Light::apply(this, name, std::any_cast<std::vector<std::string>> (value).begin ());
            } catch (const std::bad_any_cast& e) {
                auto value_str = std::any_cast<std::string> (value);
                Light::apply(this, name, std::vector<std::string> ({value_str}).begin ());
            }
        }
    }

    static void apply (Light *instance, std::string action, std::vector<std::string>::iterator args) {
        switch (Utils::hash (action.c_str ())) {
            case Utils::hash("ambient"): {
                instance->ambient = glm::vec3 (
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL)
                );
                break;
            }
            case Utils::hash("diffuse"): {
                instance->diffuse = glm::vec3 (
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL)
                );
                break;
            }
            case Utils::hash("specular"): {
                instance->specular = glm::vec3 (
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL)
                );
                break;
            }
        }
    }

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

    DirectionalLight (std::vector<std::pair<std::string, std::any>> params) : Light (params) {
        for (const auto & [name, value] : params) {
            DirectionalLight::apply(this, name, std::any_cast<std::vector<std::string>> (value).begin ());
        }
    }

    static void apply (DirectionalLight *instance, std::string action, std::vector<std::string>::iterator args) {
        switch (Utils::hash (action.c_str ())) {
            case Utils::hash("direction"): {
                instance->direction = glm::vec3 (
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL)
                );
                break;
            }
            /* default: { */
            /*     Light::apply(instance, action, args); */
            /* } */
        }
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

    PointLight (std::vector<std::pair<std::string, std::any>> params) : Light (params) {
        for (const auto & [name, value] : params) {
            try {
                PointLight::apply(this, name, std::any_cast<std::vector<std::string>> (value).begin ());
            } catch (const std::bad_any_cast& e) {
                auto value_str = std::any_cast<std::string> (value);
                PointLight::apply(this, name, std::vector<std::string> ({value_str}).begin ());
            }
        }
    }

    static void apply (PointLight *instance, std::string action, std::vector<std::string>::iterator args) {
        switch (Utils::hash (action.c_str ())) {
            case Utils::hash("position"): {
                instance->position = glm::vec3 (
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL),
                    std::strtof((++args)->c_str (), NULL)
                );
                break;
            }
            case Utils::hash("constant"): {
                instance->constant = std::strtof((args)->c_str (), NULL);
                break;
            }
            case Utils::hash("linear"): {
                instance->linear = std::strtof((args)->c_str (), NULL);
                break;
            }
            case Utils::hash("quadratic"): {
                instance->quadratic = std::strtof((args)->c_str (), NULL);
                break;
            }
            /* default: { */
            /*     Light::apply(instance, action, args); */
            /* } */
        }
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
