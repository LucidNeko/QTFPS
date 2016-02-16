#include "glview.h"
#include "mesh.h"
#include "meshloader.h"

#include <QOpenGLShaderProgram>
#include <QFile>

GLView::GLView(QWidget *parent)
{
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    setFormat(format);

    m_mesh = MeshLoader::load("C:\\Users\\Hamish\\Documents\\GitHub\\QTFPS\\models\\dragon.obj");
}

GLView::~GLView()
{
    cleanup();
}

QSize GLView::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLView::sizeHint() const
{
    return QSize(400, 400);
}

void GLView::cleanup()
{
    makeCurrent();
    //cleanup
    doneCurrent();
}

void GLView::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLView::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);

    QFile vertFile(":/shaders/basic.vert");
    QFile fragFile(":/shaders/basic.frag");
    vertFile.open(QIODevice::ReadOnly);
    fragFile.open(QIODevice::ReadOnly);
    QTextStream vertIn(&vertFile);
    QTextStream fragIn(&fragFile);
    QString vertexShaderSource = vertIn.readAll();
    QString fragmentShaderSource = fragIn.readAll();

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void GLView::paintGL()
{
    GLenum error = GL_NO_ERROR;
    do {
        error = glGetError();
        if (error != GL_NO_ERROR) {
            qDebug() << "errrrr";
        }
    } while (error != GL_NO_ERROR);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);

    m_world.setToIdentity();

    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    m_mesh->bind();
    glDrawArrays(m_mesh->mode(), 0, m_mesh->vertexCount());
    m_mesh->unbind();

    m_program->release();

    update();
}

void GLView::resizeGL(int width, int height)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(width) / height, 0.01f, 1000.0f);
}
