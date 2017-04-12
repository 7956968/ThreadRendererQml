#include <QtCore/QThread>

#include <QGuiApplication>

#include <QtGui/private/qguiapplication_p.h>
#include <QtGui/qpa/qplatformintegration.h>

#include <QtQuick/QQuickView>

#include "threadrenderer.h"
#include "logorenderer.h"

#include "fboinsgrenderer.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    if (!QGuiApplicationPrivate::platform_integration->hasCapability(QPlatformIntegration::ThreadedOpenGL)) {
        QQuickView view;
        view.setSource(QUrl("qrc:/error.qml"));
        view.show();
        return app.exec();
    }

    // Threaded renderer
    qmlRegisterType<ThreadRenderer>("SceneGraphRendering", 1, 0, "Renderer");

    // NO Threaded rendered
    qmlRegisterType<FboInSGRenderer>("SceneGraphRenderingNoThread", 1, 0, "RendererNoThread");

   // qmlRegisterType<LogoRenderer>("LogoRenderer", 1, 0, "Logo");

    int execReturn = 0;

    {
        QQuickView view;

       // LogoRenderer logo;

      //  logo.initialize();

        //logo.render();

        // Rendering in a thread introduces a slightly more complicated cleanup
        // so we ensure that no cleanup of graphics resources happen until the
        // application is shutting down.
        view.setPersistentOpenGLContext(true);
        view.setPersistentSceneGraph(true);

        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.setSource(QUrl("qrc:/main.qml"));
        view.show();

        execReturn = app.exec();
    }

    // As the render threads make use of our QGuiApplication object
    // to clean up gracefully, wait for them to finish before
    // QGuiApp is taken off the heap.
    foreach (QThread *t, ThreadRenderer::threads) {
        t->wait();
        delete t;
    }

    return execReturn;
}
