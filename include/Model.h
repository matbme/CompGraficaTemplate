#ifndef MODEL_H
#define MODEL_H

#include <any>
#include <map>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Material.h"

class Model {
public:
    Model ();
    void draw ();
    void setup_meshes ();
    void set_shader_for_all (std::shared_ptr<Shader> shader);
    void set_shader_for_textured (std::shared_ptr<Shader> shader);
    void set_shader_for_untextured (std::shared_ptr<Shader> shader);

    void rotate (float angle, glm::vec3 axis, bool reset = false);
    void translate (glm::vec3 displacements, bool reset = false);
    void rescale (glm::vec3 scaleFactors, bool reset = false);
    void highlight ();
    void remove_highlight ();

    void apply (std::string action, std::vector<std::string>::iterator args);

    void update ();

    std::vector<Mesh> meshes;
    std::map<std::string, Material> materials;

    constexpr static glm::vec3 axis_vector (const char ax) {
        switch (ax) {
            case 'x': return glm::vec3 (1.0f, 0.0f, 0.0f);
            case 'y': return glm::vec3 (0.0f, 1.0f, 0.0f);
            case 'z': return glm::vec3 (0.0f, 0.0f, 1.0f);
            default: throw std::invalid_argument (std::string("Inalid axis. Not one of (x, y, z): ") + ax);
        }
    }
};

#endif
