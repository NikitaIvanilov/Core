#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QString>

class Notepad : public QWidget{

  public:

    Notepad(QWidget *parent = 0) : QWidget(parent){

      title = new QLineEdit();
      text  = new QTextEdit();

      buttonSave = new QPushButton("Save");
      buttonLoad = new QPushButton("Load");

      HBox = new QHBoxLayout();
      VBox = new QVBoxLayout();

      HBox->addWidget(title);
      HBox->addWidget(buttonSave);
      HBox->addWidget(buttonLoad);

      VBox->addLayout(HBox);
      VBox->addWidget(text);

      this->setLayout(VBox);

      connect(buttonSave, &QPushButton::clicked, this, &Notepad::buttonSavePush);
      connect(buttonLoad, &QPushButton::clicked, this, &Notepad::buttonLoadPush);

    }

  private slots:

    void buttonSavePush(void){

      if(title->text() == "") return;

      QFile file(title->text());

      if(file.open(QIODevice::WriteOnly) == false) return;

      QTextStream(&file) << text->toPlainText();

      file.close();

    }

    void buttonLoadPush(void){

      if(title->text() == "") return;

      QFile file(title->text());

      if(file.open(QIODevice::ReadOnly) == false) return;

      QTextStream file_stream(&file);
      QString buffer = "";

      while(file_stream.atEnd() == false)

        buffer += file_stream.readLine() + '\n';

      text->setText(buffer);

      file.close();

    }

  private:

    QLineEdit   *title;
    QTextEdit   *text;

    QPushButton *buttonSave,
                *buttonLoad;

    QHBoxLayout *HBox;
    QVBoxLayout *VBox;

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  Notepad window;

  window.setWindowTitle("notepad-qt");
  window.resize(600, 800);
  window.show();

  return app.exec();

}