#include <QApplication>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

class Pixmap : public QWidget{

  private:

      QVBoxLayout *vbox;
      QLabel      *label;
      QPixmap     *pixmap;

  public:

    Pixmap(QWidget *parent = 0) : QWidget(parent){

      vbox   = new QVBoxLayout(this);
      label  = new QLabel(this);
      pixmap = new QPixmap("Picture.png");

      label->setPixmap(*pixmap);

      vbox->addWidget(label, 0, Qt::AlignCenter);

    }

    ~Pixmap(){

      delete vbox;
      delete label;
      delete pixmap;

    }

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  Pixmap window;

  window.resize(600, 600);
  window.show();

  return app.exec();

}