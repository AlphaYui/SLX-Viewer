#include <QApplication>

#include <QFile>
#include <QXmlStreamReader>
#include <QtDebug>
#include "system.h"

#include <QElapsedTimer>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    /*MainWindow w;
    w.show();*/

    // Get file to be read
    const QString path = "C:\\Users\\Arthur\\Desktop\\SL_viewer\\TestModel\\simulink\\blockdiagram.xml";
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

    map.save("C:\\Users\\Arthur\\Desktop\\SL_viewer\\TestModel\\simulink\\rendered.png");

    if( in->hasError() )
    {
        // Error handling

        qDebug() << "An error has occured...";
    }

    f->close();

    return app.exec();
}
