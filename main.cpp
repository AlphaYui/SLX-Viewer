#include <QApplication>

#include <QFile>
#include <QXmlStreamReader>
#include <QtDebug>
#include "Main/system.h"

#include <QElapsedTimer>

#include "UI/mainwindow.h"

void debugParser()
{
    QString appPath = QCoreApplication::applicationDirPath();

    QElapsedTimer t;
    t.start();

    // Select&open model file - currently still static
    const QString path = appPath + "/../SLX-Viewer/Tests/blockdiagram.xml";
    QFile *f = new QFile(path);
    f->open(QIODevice::ReadOnly);

    // Create input stream
    QXmlStreamReader *in = new QXmlStreamReader;
    in->setDevice( f );

    // Create and read system
    System s(in);

    qDebug() << "Loading time: " << t.elapsed() << " ms for " << in->lineNumber() << " lines";
    f->close();
}

void debugRenderer()
{
    QString appPath = QCoreApplication::applicationDirPath();

    // Select&open model file - currently still static
    const QString path = appPath + "/../SLX-Viewer/Tests/blockdiagram.xml";
    QFile *f = new QFile(path);
    f->open(QIODevice::ReadOnly);

    QElapsedTimer t;
    t.start();

    // Create input stream
    QXmlStreamReader *in = new QXmlStreamReader;
    in->setDevice( f );

    // Create and read system
    System s(in);

    qDebug() << "Model loading time: " << t.elapsed() << " ms";

    t.restart();

    // Render system
    QPixmap map = s.render();

    qDebug() << "Rendering time: " << t.elapsed() << " ms";

    map.save(appPath + "/../SLX-Viewer/Tests/model.png");

    if( in->hasError() )
    {
        // Error handling

        qDebug() << "An error has occured...";
    }

    f->close();
}

void debugUI()
{
    MainWindow w;
    w.show();
}

int main(int argc, char *argv[])
{
    const int DEBUG_PARSER = 1;
    const int DEBUG_RENDERER = 2;
    const int DEBUG_UI = 3;

    QApplication app(argc,argv);

    int action = DEBUG_RENDERER;

    if( action == DEBUG_PARSER )
        debugParser();
    else if( action == DEBUG_RENDERER )
        debugRenderer();
    else if( action == DEBUG_UI )
        debugUI();

    return 0;
}
