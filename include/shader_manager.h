#ifndef SHADER_MANAGER_H_
#define SHADER_MANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

struct ShaderManager {
    std::map<std::string, std::shared_ptr<sf::Shader>> shaders;

    void add(std::string name, std::string vertex_filename,
             std::string fragment_filename);
    std::shared_ptr<sf::Shader> get(std::string name);
};

#endif  // SHADER_MANAGER_H_
