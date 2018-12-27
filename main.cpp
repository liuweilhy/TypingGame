#include <QtWidgets>
#include "gameview.h"
#include "gamescene.h"
#include "charitem.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GameScene scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    GameView view(&scene);
    view.show();

    return app.exec();
}
