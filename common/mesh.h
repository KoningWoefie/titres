#ifndef MESH_H
#define MESH_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot);
    Mesh(int width, int height, float uvWidth, float uvHeight, glm::vec2 pivot, glm::vec2 uvOffset, bool corner, int type = 0);
    ~Mesh();

    int changeUV(float uvWidth, float uvHeight);

    glm::vec2 meshPos;

    glm::vec2 GetUV() { return glm::vec2(_uvWidth, _uvHeight);  };
    bool IsNineSlice() {    return nineSlice;   };
    bool Corner() { return _corner; };
    int Type() { return _type; };

    GLuint vertexbuffer() { return _vertexbuffer; };
    GLuint uvbuffer() { return _uvbuffer; };
private:
    GLuint _vertexbuffer;
    GLuint _uvbuffer;

    std::vector<glm::vec2> _uvs;

    int generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv);

    //if nine slices
    bool nineSlice;
    int _width;
    int _height;
    float _uvWidth;
    float _uvHeight;
    glm::vec2 _pivot;
    bool _corner;
    int _type;

    glm::vec2 _uvOffset;
};

#endif // MESH_H
