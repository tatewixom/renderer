#include "Model.h"
#include "Shader.h"

template<typename T>
const T* GetAttributeData(const tinygltf::Model& model, const tinygltf::Accessor& accessor) 
{
  const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
  const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

  const unsigned char* dataPtr = buffer.data.data() + bufferView.byteOffset + accessor.byteOffset;

  return reinterpret_cast<const T*>(dataPtr);
}

void Model_t::initialize(std::string_view gltf_file_path)
{
  //loading .gltf file
  tinygltf::Model model;
  tinygltf::TinyGLTF loader;
  std::string err, warn;

  bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, gltf_file_path.data());

  if (!warn.empty()) 
    std::cout << "Warn: " << warn << std::endl;
  if (!err.empty()) 
    std::cout << "Err: " << err << std::endl;
  if (!ret) 
    std::cout << "Failed to load model\n";

  //loading meshes from model file
  for (std::size_t i{ 0 }; i < model.meshes.size(); ++i)
  {
    const tinygltf::Mesh& mesh{ model.meshes[i] };

    //process the mesh
    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};
    std::vector<Texture> textures{};

    for (auto& primitive : mesh.primitives)
    {
      //position
      const tinygltf::Accessor& posAccessor{ model.accessors[primitive.attributes.at("POSITION")] };
      const glm::vec3* positions{ GetAttributeData<glm::vec3>(model, posAccessor) };

      size_t vertexCount{ posAccessor.count };

      //normal
      const glm::vec3* normals{ nullptr };

      if (primitive.attributes.count("NORMAL"))
      {
        const tinygltf::Accessor& normAccessor{ model.accessors[primitive.attributes.at("NORMAL")] };
        normals = GetAttributeData<glm::vec3>(model, normAccessor);
      }

      //texture coords
      const glm::vec2* texcoords{ nullptr };

      if (primitive.attributes.count("TEXCOORD_0"))
      {
        const tinygltf::Accessor& uvAccessor =
          model.accessors[primitive.attributes.at("TEXCOORD_0")];
        texcoords = GetAttributeData<glm::vec2>(model, uvAccessor);
      }

      vertices.resize(vertexCount);

      for (size_t i{ 0 }; i < vertexCount; ++i)
      {
        vertices[i].position = positions[i];

        if (normals)
          vertices[i].normal = normals[i];
        else
          vertices[i].normal = glm::vec3(0.0f);

        if (texcoords)
          vertices[i].texture = texcoords[i];
        else
          vertices[i].texture = glm::vec2(0.0f);
      }

      //extracting indices
      const tinygltf::Accessor& indexAccessor = model.accessors[primitive.indices];
      const auto* indexData = GetAttributeData<unsigned int>(model, indexAccessor);

      std::size_t indexCount = indexAccessor.count;
      indices.resize(indexCount);

      for (std::size_t i{ 0 }; i < indexCount; ++i)
        indices[i] = indexData[i];

      std::cout << "hello" << '\n';

      //extracting base color texture
      int materialIndex{ primitive.material };
      std::cout << materialIndex << '\n';
      const tinygltf::Image* image{};
      if (materialIndex > 0)
      {
        const tinygltf::Material& mat = model.materials[materialIndex];

        int baseColorTexIndex{ mat.pbrMetallicRoughness.baseColorTexture.index };
        if (baseColorTexIndex >= 0)
        {
          const tinygltf::Texture& tex{ model.textures[baseColorTexIndex] };
          int imageIndex{ tex.source };

          image = &model.images[imageIndex];
        }

        if (image)
        {
          Texture temptex{};
          temptex.initialize(image->image.data(), image->width, image->height);
          textures.push_back(temptex);
        }

        //extracting normal map
        image = nullptr;
        int normalTexIndex = mat.normalTexture.index;

        if (normalTexIndex >= 0)
        {
          const tinygltf::Texture& tex = model.textures[normalTexIndex];
          image = &model.images[tex.source];
        }

        if (image)
        {
          Texture temptex{};
          temptex.initialize(image->image.data(), image->width, image->height);
          textures.push_back(temptex);
        }
      }
    }

    Mesh_t temp{};
    temp.initialize(vertices, indices, std::array<Layout_t::Attribute, 3>
    {
      Layout_t::Attribute{ 0u, 3, sizeof(Vertex), 0 },
      Layout_t::Attribute{ 2u, 2, sizeof(Vertex), offsetof(Vertex, texture) },
      Layout_t::Attribute{ 3u, 3, sizeof(Vertex), offsetof(Vertex, normal) }
    },
    std::move(textures));

    meshes.emplace_back(temp);

    vertices.clear();
    indices.clear();
    textures.clear();
  }
}

void Model_t::draw(Shader& shader)
{
  for (auto& m : meshes)
    m.draw(shader);
}
