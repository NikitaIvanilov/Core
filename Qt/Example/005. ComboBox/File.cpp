#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>

class ComboBox : public QWidget{

  private:

    QLabel      *label;
    QComboBox   *cbox;
    QHBoxLayout *hbox;

  public:

    ComboBox(QWidget *parent = 0) : QWidget(parent){

      hbox  = new QHBoxLayout(this);
      cbox  = new QComboBox();
      label = new QLabel("Point 1");

      cbox->addItem("Point 1");
      cbox->addItem("Point 2");
      cbox->addItem("Point 3");

      hbox->addWidget(cbox);
      hbox->addWidget(label);

      this->setLayout(hbox);

      connect(cbox, SIGNAL(activated(const QString &)),
              label, SLOT(setText(const QString &)));

    }

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  ComboBox window;

  window.resize(200, 200);
  window.show();

  return app.exec();

}