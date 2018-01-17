#include "shader_manager.h"
#include <iostream>

using namespace std;

void ShaderManager::add(string name, string vertex_filename,
                        string fragment_filename) {
    auto shader = make_shared<sf::Shader>();

    if (!shader->loadFromFile(vertex_filename, fragment_filename)) {
        cerr << "Cannot load shaders: " << vertex_filename << " and "
             << fragment_filename << endl;
        exit(EXIT_FAILURE);
    }
    shaders[name] = shader;
}

shared_ptr<sf::Shader> ShaderManager::get(string name) { return shaders[name]; }
