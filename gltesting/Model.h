#pragma once

#include "Mesh.h"

#include <tinygltf/tiny_gltf.h>
#include <stb/stb_image.h>

class Model_t
{
public:
  void initialize(std::string_view gltf_file_path);

  void draw(Shader& shader);

private:
  std::vector<Mesh_t> meshes{};
  std::vector<Texture> textures{};
};

