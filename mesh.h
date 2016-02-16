#ifndef MESH
#define MESH

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class QOpenGLFunctions;

class MeshVertex {
public:
    QVector3D position;
    QVector3D normal;
    QVector2D texcoord;
    QVector4D color;
    char pad[16];
};

class Mesh {

public:
    Mesh(QVector<MeshVertex> data);
    ~Mesh();

    void bind();
    void unbind();

    int mode() const { return GL_TRIANGLES; }
    int vertexCount() const { return m_data.size(); }

private:
    void create();
    bool isCreated() const { return m_isCreated; }

    QVector<MeshVertex> m_data;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    bool m_isCreated = false;
};

#endif // MESH

