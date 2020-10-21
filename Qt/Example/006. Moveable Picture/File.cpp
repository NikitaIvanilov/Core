#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QSize>
#include <QMap>
#include <QString>
#include <QVector>

class Texture : public QWidget{

  public:

    Texture(QString name, QSize size, QWidget *parent = 0) : QWidget(parent){

      label  = new QLabel (this);
      pixmap = new QPixmap(name);
      timer  = new QTimer (this);

      label->setPixmap((*pixmap).scaled(size));
      label->show();

      timer->setInterval(1000);
      timer->start();

      this->resize(parent->size());

      connect(timer, &QTimer::timeout, this, [=](){ timeEvent(parent); } );

    }

    void moveUp   (void){ y -= 2; label->move(x, y); }
    void moveDown (void){ y += 2; label->move(x, y); }
    void moveLeft (void){ x -= 2; label->move(x, y); }
    void moveRight(void){ x += 2; label->move(x, y); }

    int getX(void){ return x; }
    int getY(void){ return y; }

  private slots:

    void timeEvent(QWidget *parent){

      if(this->size() != parent->size())

        this->resize(parent->size());

    }

  private:

    QLabel  *label;
    QPixmap *pixmap;
    QTimer  *timer;

    int x = 0,
        y = 0;

};

class Player : public QWidget{

  public:

    Player(QString picture, int width ,int height, QWidget *parent = 0) : QWidget(parent){

      timer  = new QTimer (this);
      player = new Texture(picture, QSize(width, height), this);

      player->show();

      timer->setInterval(10);
      timer->start();

      connect(timer, &QTimer::timeout, this, &Player::timeEvent);

    }

    void moveUp   (void){ playerUp    = 10; }
    void moveDown (void){ playerDown  = 10; }
    void moveLeft (void){ playerLeft  = 10; }
    void moveRight(void){ playerRight = 10; }

    int getX(void){ return player->getX(); }
    int getY(void){ return player->getY(); }

  protected:

    void keyPressEvent(QKeyEvent *event){

      keyStream[event->key()] = true;
      QWidget::keyPressEvent(event);

    }

    void keyReleaseEvent(QKeyEvent *event){

      keyStream[event->key()] = false;
      QWidget::keyReleaseEvent(event);

    }

  private slots:

    void timeEvent(void){

      if(playerUp    > 0){ player->moveUp();    --playerUp;    };
      if(playerDown  > 0){ player->moveDown();  --playerDown;  };
      if(playerLeft  > 0){ player->moveLeft();  --playerLeft;  };
      if(playerRight > 0){ player->moveRight(); --playerRight; };

      if(keyStream[Qt::Key_W]){ moveUp();    }
      if(keyStream[Qt::Key_S]){ moveDown();  }
      if(keyStream[Qt::Key_A]){ moveLeft();  }
      if(keyStream[Qt::Key_D]){ moveRight(); }

    }

  private:

    QMap<int, bool> keyStream;

    QTimer  *timer;
    Texture *player;

    int playerUp    = 0,
        playerDown  = 0,
        playerLeft  = 0,
        playerRight = 0;

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  Player win("BlockOfGrass.png", 50, 50);

  win.setWindowTitle("Moveable Picture");
  win.resize(500, 500);
  win.show();

  return app.exec();

}