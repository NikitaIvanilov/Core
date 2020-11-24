#include <QApplication>
#include <QWidget>
#include <QPushButton>

class Button : public QWidget{

  public:

    Button(QWidget *parent = 0) : QWidget(parent){

      QPushButton *buttonQuit = new QPushButton("Quit", this);
      buttonQuit->setGeometry(10, 10, 75, 30);

      connect(buttonQuit, &QPushButton::clicked, qApp, &QApplication::quit);

    }

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  Button window;

  window.resize(600, 400);
  window.setWindowTitle("Button Quit");
  window.show();

  return app.exec();

}