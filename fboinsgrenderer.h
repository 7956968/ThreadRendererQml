#ifndef FBOINSGRENDERER_H
#define FBOINSGRENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include <QLoggingCategory>
#include <QThread>
#include <QOpenGLContext>

class LogoRenderer;

class FboInSGRenderer : public QQuickFramebufferObject
{
    Q_OBJECT


public:
    FboInSGRenderer();
    Renderer *createRenderer() const;
};

#endif // FBOINSGRENDERER_H
