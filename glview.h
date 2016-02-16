#ifndef GLVIEW
#define GLVIEW

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

class QOpenGLShaderProgram;
class Mesh;

class GLView : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    explicit GLView(QWidget *parent = 0);
    ~GLView();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

private:
    void cleanup();
//    void render(GameObject *obj, QMatrix4x4 world);

protected:
    void initializeGL() override;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;

private:
    QOpenGLShaderProgram *m_program;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;

    Mesh *m_mesh;
};

#endif // GLVIEW

