#include "mesh.h"

#include <QOpenGLFunctions>

Mesh::Mesh(QVector<MeshVertex> data)
{
    m_data = data;
}

Mesh::~Mesh()
{

}

void Mesh::bind()
{
    if(!isCreated()) {
        create();
    }

    m_vao.bind();
}

void Mesh::unbind()
{
    if(!isCreated()) { return; }

    m_vao.release();
}

void Mesh::create()
{
    if(isCreated()) { return; }

    m_vao.create();
    m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(m_data.constData(), m_data.size() * sizeof(MeshVertex));

    m_vbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glEnableVertexAttribArray(2);
    f->glEnableVertexAttribArray(3);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    f->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), reinterpret_cast<void *>(6 * sizeof(GLfloat)));
    f->glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), reinterpret_cast<void *>(8 * sizeof(GLfloat)));
    m_vbo.release();

    m_vao.release();

    m_isCreated = true;
}
