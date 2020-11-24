#include <QApplication>
#include <QWidget>
#include <QIcon>

class MyClass : public QWidget{

  public:

    MyClass(QWidget *parent = 0) : QWidget(parent){

    }

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  MyClass window;

  window.resize(600, 400);
  window.setWindowTitle("Simple Window");
  window.setToolTip("ToolTip");
  window.setWindowIcon(QIcon("Icon.png"));
  window.show();

  return app.exec();

}