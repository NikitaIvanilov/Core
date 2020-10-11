#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QString>
#include <QKeyEvent>

#include <algorithm>

class Calculator{

  public:

    Calculator(QString line){

      line.push_back (")");
      line.push_front("(");

      checkBracketsOperator(&line);

      while(line[0] == '(') countBrackets(&line);

      if(minus_prepend == 1) line.prepend("-");

      result = line;

    }

    QString get_result(void){ return result; }
    QString result;

  private:

    // Options

    int minus_prepend = 0;

    // High Level: Brackets

    void countBrackets(QString *line){

      QString brackets_counted = catchBrackets(line),
              brackets_in_line = "(" + brackets_counted + ")";

        countExpressionAllPriority(&brackets_counted);
        line->replace(brackets_in_line, brackets_counted);

    }

    void checkBracketsOperator(QString *line){

      QString str = *line;

      for(int i = 0; i < (str.size() - 1); ++i)

        if(

          (str.at(i) == ")"    && str.at(i + 1).isDigit()) || // )1
          (str.at(i).isDigit() && str.at(i + 1) == "(") ||    // 1(
          (str.at(i) == ")"    && str.at(i + 1) == "(")       // )(

      ){ str.insert(i + 1, "*"); }

      *line = str;

    }

    QString catchBrackets(QString *line){

      int left  = indexOfOperatorLast(line, "("),
          right = catchBracketsRight(line, left);

      QString out = "";

      for(int i = left + 1; i < right; ++i)

        out += line->at(i);

      return out;

    }

    int catchBracketsRight(QString *line, int left){

      while(left < line->size())

        if(line->at(left) == ")") return left; else ++left;

      return -1;

    }

    // Middle Level: Expression

    void countExpressionAllPriority(QString *line){

      countExpressionHighPriority(line);
      countExpressionLowPriority (line);

    }

    void countExpressionLowPriority(QString *line){

      for(

        QString oper = nearOperatorLowPriority(line);
        isAddition(oper) || isSubtraction(oper);
        oper = nearOperatorLowPriority(line)

      ) countExpression(line, oper);

    }

    void countExpressionHighPriority(QString *line){

      for(

        QString oper = nearOperatorHighPriority(line);
        isDivision(oper) || isMultiplication(oper);
        oper = nearOperatorHighPriority(line)

      ) countExpression(line, oper);

    }

    void countExpression(QString *line, QString oper){

      int oper_index = indexOfOperator(line, oper);
      float out = 0;

      if(oper_index == -1) return;

      QString num_left  = numberLeft(line,  oper_index),
              num_right = numberRight(line, oper_index);

      if(isAddition      (oper)){ out = num_left.toFloat() + num_right.toFloat(); } else
      if(isSubtraction   (oper)){ out = num_left.toFloat() - num_right.toFloat(); } else
      if(isMultiplication(oper)){ out = num_left.toFloat() * num_right.toFloat(); } else
      if(isDivision      (oper)){ out = num_left.toFloat() / num_right.toFloat(); }

      line->replace((num_left + oper + num_right), QString::number(out));

      if(out < 0) invertOperatorFullLine(line);

    }

    // Low Level: Operator

    void invertOperatorFullLine(QString *line){

      QString str = *line;

      for(int i = 0; i < str.size(); ++i)

        if(str[i] == '+') str[i] = '-'; else
        if(str[i] == '-') str[i] = '+';

      *line = str;

      if(minus_prepend == 0) minus_prepend = 1; else minus_prepend = 0;

    }

    int isDivision      (QString oper){ if(oper == "/") return 1; else return 0; }
    int isMultiplication(QString oper){ if(oper == "*") return 1; else return 0; }
    int isSubtraction   (QString oper){ if(oper == "-") return 1; else return 0; }
    int isAddition      (QString oper){ if(oper == "+") return 1; else return 0; }

    int isOperator(QString oper){

      if(isAddition      (oper)) return 1; else
      if(isSubtraction   (oper)) return 1; else
      if(isMultiplication(oper)) return 1; else
      if(isDivision      (oper)) return 1; else

        return 0;

    }

    QString nearOperatorHighPriority(QString *line){ return nearOperator(line, "*/"); }
    QString nearOperatorLowPriority (QString *line){ return nearOperator(line, "+-"); }

    QString nearOperator(QString *line, QString oper_pair){

      int oper[2] = {

        indexOfOperator(line, oper_pair.at(0)),
        indexOfOperator(line, oper_pair.at(1))

      };

      std::sort(

        std::begin(oper),
        std::end(oper)

      );

      for(int i = 0; i < 2; ++i)

        if(oper[i] != -1) return line->at(oper[i]);

      return "";

    }

    QString numberLeft(QString *line, int index){

      QString out = "";

      for(int i = index - 1; i >= 0 && (line->at(i).isDigit() || line->at(i) == "."); --i)

        out.push_front(line->at(i));

      return out;

    }

    QString numberRight(QString *line, int index){

      QString out = "";

      for(int i = index + 1; i < line->size() && (line->at(i).isDigit() || line->at(i) == "."); ++i)

        out += line->at(i);

      return out;

    }

    int countOperator(QString *line, QString oper){

      int out = 0;

      for(int i = 0; i < line->size(); ++i)

        if(line->at(i) == oper)

          ++out;

      return out;

    }

    int indexOfOperatorLast(QString *line, QString oper){

      int out = -1;

      for(int i = 0; i < line->size(); ++i)

        if(line->at(i) == oper)

          out = i;

      return out;

    }

    int indexOfOperator(QString *line, QString oper){

      for(int i = 0; i < line->size(); ++i)

        if(line->at(i) == oper)

          return i;

      return -1;

    }

};

class UserInterface : public QWidget{

  public:

    UserInterface(QWidget *parent = 0) : QWidget(parent){

      // Set

      setOutputFrame();

      setButtonRun();
      setButtonBackspace();
      setButtonPoint();

      setButtonBracketLeft();
      setButtonBracketRight();

      setButtonOne();
      setButtonTwo();
      setButtonThree();
      setButtonFour();
      setButtonFive();
      setButtonSix();
      setButtonSeven();
      setButtonEight();
      setButtonNine();
      setButtonZero();

      setButtonAddition();
      setButtonSubtraction();
      setButtonMultiplication();
      setButtonDivision();

      // Connect

      connect(buttonRun,       &QPushButton::clicked, this, &UserInterface::buttonRunPush);
      connect(buttonBackspace, &QPushButton::clicked, this, &UserInterface::buttonBackspacePush);
      connect(buttonPoint,     &QPushButton::clicked, this, &UserInterface::buttonPointPush);

      connect(buttonBracketLeft,  &QPushButton::clicked, this, &UserInterface::buttonBracketLeftPush);
      connect(buttonBracketRight, &QPushButton::clicked, this, &UserInterface::buttonBracketRightPush);

      connect(buttonOne,   &QPushButton::clicked, this, &UserInterface::buttonOnePush);
      connect(buttonTwo,   &QPushButton::clicked, this, &UserInterface::buttonTwoPush);
      connect(buttonThree, &QPushButton::clicked, this, &UserInterface::buttonThreePush);
      connect(buttonFour,  &QPushButton::clicked, this, &UserInterface::buttonFourPush);
      connect(buttonFive,  &QPushButton::clicked, this, &UserInterface::buttonFivePush);
      connect(buttonSix,   &QPushButton::clicked, this, &UserInterface::buttonSixPush);
      connect(buttonSeven, &QPushButton::clicked, this, &UserInterface::buttonSevenPush);
      connect(buttonEight, &QPushButton::clicked, this, &UserInterface::buttonEightPush);
      connect(buttonNine,  &QPushButton::clicked, this, &UserInterface::buttonNinePush);
      connect(buttonZero,  &QPushButton::clicked, this, &UserInterface::buttonZeroPush);

      connect(buttonAddition,       &QPushButton::clicked, this, &UserInterface::buttonAdditionPush);
      connect(buttonSubtraction,    &QPushButton::clicked, this, &UserInterface::buttonSubtractionPush);
      connect(buttonMultiplication, &QPushButton::clicked, this, &UserInterface::buttonMultiplicationPush);
      connect(buttonDivision,       &QPushButton::clicked, this, &UserInterface::buttonDivisionPush);

    }

  protected:

    void keyPressEvent(QKeyEvent *event){

      switch(event->key()){

        case Qt::Key_Escape:    exit(0);               break;
        case Qt::Key_Backspace: buttonBackspacePush(); break;
        case Qt::Key_Equal:     buttonRunPush();       break;
        case Qt::Key_Period: buttonPointPush(); break;

        case Qt::Key_ParenLeft:  buttonBracketLeftPush();  break;
        case Qt::Key_ParenRight: buttonBracketRightPush(); break;

        case Qt::Key_1: buttonOnePush();   break;
        case Qt::Key_2: buttonTwoPush();   break;
        case Qt::Key_3: buttonThreePush(); break;
        case Qt::Key_4: buttonFourPush();  break;
        case Qt::Key_5: buttonFivePush();  break;
        case Qt::Key_6: buttonSixPush();   break;
        case Qt::Key_7: buttonSevenPush(); break;
        case Qt::Key_8: buttonEightPush(); break;
        case Qt::Key_9: buttonNinePush();  break;
        case Qt::Key_0: buttonZeroPush();  break;

        case Qt::Key_Plus:     buttonAdditionPush();       break;
        case Qt::Key_Minus:    buttonSubtractionPush();    break;
        case Qt::Key_Asterisk: buttonMultiplicationPush(); break;
        case Qt::Key_Slash:    buttonDivisionPush();       break;

      };

    }

  private slots:

    void buttonBackspacePush(void){

      QString str = output->text();

      if(str.size() > 0)

        str.resize(str.size() - 1);

      output->setText(str);

    }

    void buttonRunPush(void){

      calculator = new Calculator(output->text());
      output->setText(output->text() + "=" + calculator->get_result());

    }

    void buttonPointPush(void){ output->setText(output->text() + "."); }

    void buttonBracketLeftPush (void){ output->setText(output->text() + "("); }
    void buttonBracketRightPush(void){ output->setText(output->text() + ")"); }

    void buttonOnePush  (void){ output->setText(output->text() + "1"); }
    void buttonTwoPush  (void){ output->setText(output->text() + "2"); }
    void buttonThreePush(void){ output->setText(output->text() + "3"); }
    void buttonFourPush (void){ output->setText(output->text() + "4"); }
    void buttonFivePush (void){ output->setText(output->text() + "5"); }
    void buttonSixPush  (void){ output->setText(output->text() + "6"); }
    void buttonSevenPush(void){ output->setText(output->text() + "7"); }
    void buttonEightPush(void){ output->setText(output->text() + "8"); }
    void buttonNinePush (void){ output->setText(output->text() + "9"); }
    void buttonZeroPush (void){ output->setText(output->text() + "0"); }

    void buttonAdditionPush      (void){  output->setText(output->text() + "+"); }
    void buttonSubtractionPush   (void){  output->setText(output->text() + "-"); }
    void buttonMultiplicationPush(void){  output->setText(output->text() + "*"); }
    void buttonDivisionPush      (void){  output->setText(output->text() + "/"); }

  private:

    Calculator *calculator;

    QLabel *output;
    QPushButton *buttonRun, *buttonBackspace, *buttonPoint,

    *buttonBracketLeft, *buttonBracketRight,

    *buttonOne,   *buttonTwo,   *buttonThree,
    *buttonFour,  *buttonFive,  *buttonSix,
    *buttonSeven, *buttonEight, *buttonNine,
    *buttonZero,

    *buttonAddition,       *buttonSubtraction,
    *buttonMultiplication, *buttonDivision;

    // Operation Buttons

    void setButtonBracketLeft(void){

      buttonBracketLeft = new QPushButton("(", this);
      buttonBracketLeft->setGeometry(45, 190, 30, 30);

    }

    void setButtonBracketRight(void){

      buttonBracketRight = new QPushButton(")", this);
      buttonBracketRight->setGeometry(80, 190, 30, 30);

    }

    void setButtonAddition(void){

      buttonAddition = new QPushButton("+", this);
      buttonAddition->setGeometry(10, 50, 30, 65);

    }

    void setButtonSubtraction(void){

      buttonSubtraction = new QPushButton("-", this);
      buttonSubtraction->setGeometry(10, 120, 30, 65);

    }

    void setButtonMultiplication(void){

      buttonMultiplication = new QPushButton("*", this);
      buttonMultiplication->setGeometry(150, 50, 30, 65);

    }

    void setButtonDivision(void){

      buttonDivision = new QPushButton("/", this);
      buttonDivision->setGeometry(150, 120, 30, 65);

    }

    // Number Buttons

    void setButtonZero(void){

      buttonZero = new QPushButton("0", this);
      buttonZero->setGeometry(45, 155, 30, 30);

    }

    void setButtonNine(void){

      buttonNine = new QPushButton("9", this);
      buttonNine->setGeometry(115, 120, 30, 30);

    }

    void setButtonEight(void){

      buttonEight = new QPushButton("8", this);
      buttonEight->setGeometry(80, 120, 30, 30);

    }

    void setButtonSeven(void){

      buttonSeven = new QPushButton("7", this);
      buttonSeven->setGeometry(45, 120, 30, 30);

    }

    void setButtonSix(void){

      buttonSix = new QPushButton("6", this);
      buttonSix->setGeometry(115, 85, 30, 30);

    }

    void setButtonFive(void){

      buttonFive = new QPushButton("5", this);
      buttonFive->setGeometry(80, 85, 30, 30);

    }

    void setButtonFour(void){

      buttonFour = new QPushButton("4", this);
      buttonFour->setGeometry(45, 85, 30, 30);

    }

    void setButtonThree(void){

      buttonThree = new QPushButton("3", this);
      buttonThree->setGeometry(115, 50, 30, 30);

    }

    void setButtonTwo(void){

      buttonTwo = new QPushButton("2", this);
      buttonTwo->setGeometry(80, 50, 30, 30);

    }

    void setButtonOne(void){

      buttonOne = new QPushButton("1", this);
      buttonOne->setGeometry(45, 50, 30, 30);

    }

    void setButtonRun(void){

      buttonRun = new QPushButton("Run", this);
      buttonRun->setGeometry(80, 155, 65, 30);

    }

    void setButtonBackspace(void){

      buttonBackspace = new QPushButton("<-", this);
      buttonBackspace->setGeometry(115, 190, 65, 30);

    }

    void setButtonPoint(void){

      buttonPoint = new QPushButton(".", this);
      buttonPoint->setGeometry(10, 190, 30, 30);

    }

    // Output Frame

    void setOutputFrame(void){

      output = new QLabel("", this);

      output->setGeometry(10, 10, 300, 30);
      output->setFrameStyle(QFrame::Box);
      output->setLineWidth(2);

    }

};

int main(int argc, char *argv[]){

  QApplication app(argc, argv);

  UserInterface window;

  window.setWindowTitle("Qt Calculator v1.0");
  window.resize(350, 400);
  window.show();

  return app.exec();

}