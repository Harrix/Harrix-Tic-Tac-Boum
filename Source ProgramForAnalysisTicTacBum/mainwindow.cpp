#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>

#include "HarrixMathLibrary.h"
#include "HarrixQtLibrary.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch () % 1000000);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();

    QString ListFromFile = HQt_ReadFile("word_rus.txt");
    QStringList List = HQt_QStringToQStringList(ListFromFile);

    QString Syllable = ui->lineEdit->text();

    int n = List.count();

    ui->textEdit->insertPlainText("Количество слов в базе = "+QString::number(n)+"\n");

    int s = 0;
    QString Temp;
    for (int i=0;i<n;i++)
    {
        Temp = List.at(i);
        if (Temp.indexOf(Syllable)>=0)
        {
            s++;
            ui->textEdit_2->insertPlainText(Temp+"\n");
        }
    }

    ui->textEdit->insertPlainText("Найдено слов = "+QString::number(s)+"\n");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();

    QString ListFromFile = HQt_ReadFile("word_rus.txt");
    QStringList List = HQt_QStringToQStringList(ListFromFile);

    QString ListFromFileTicTacBoom = HQt_ReadFile("tictacboom.txt");
    QStringList ListTicTacBoom = HQt_QStringToQStringList(ListFromFileTicTacBoom);

    int n = List.count();
    ui->textEdit->insertPlainText("Количество слов в базе = "+QString::number(n)+"\n");
    ui->textEdit_2->insertPlainText("Слог\tСколько найдено слов\n");
    ui->label_2->setText("Найдено слогов: 0");

    int findWords = 0;

    int check=0;

    for (int j=0;j<ListTicTacBoom.count();j++)
    {
        check++;
        QString Syllable;

        Syllable = ListTicTacBoom.at(j);

        int s = 0;
        QString Temp;
        for (int i=0;i<n;i++)
        {
            Temp = List.at(i);
            if (Temp.indexOf(Syllable)>=0)
                s++;
        }

        ui->textEdit->insertPlainText(Syllable+"\n");
        ui->textEdit_2->insertPlainText(Syllable + "\t"+QString::number(s)+"\n");
        findWords++;
        ui->label_2->setText("Найдено слогов: "+QString::number(findWords)+". Проверено всего: "+QString::number(check));

        QTextCursor c =  ui->textEdit->textCursor();
        c.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(c);

        QTextCursor c2 =  ui->textEdit_2->textCursor();
        c2.movePosition(QTextCursor::End);
        ui->textEdit_2->setTextCursor(c2);

        QGuiApplication::processEvents();
    }

    ui->label_2->setText("Найдено слогов: "+QString::number(findWords)+". Проверено всего: "+QString::number(check));

    ui->textEdit->insertPlainText("Найдено слогов = "+QString::number(findWords)+"\n");
    ui->textEdit->insertPlainText("Конец поиска\n");

    QTextCursor c =  ui->textEdit->textCursor();
    c.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(c);

    QTextCursor c2 =  ui->textEdit_2->textCursor();
    c2.movePosition(QTextCursor::End);
    ui->textEdit_2->setTextCursor(c2);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();

    QString ListFromFile = HQt_ReadFile("word_rus.txt");
    QStringList List = HQt_QStringToQStringList(ListFromFile);

    QString ListFromFileTicTacBoom = HQt_ReadFile("tictacboom.txt");
    QStringList ListTicTacBoom = HQt_QStringToQStringList(ListFromFileTicTacBoom);

    int n = List.count();
    ui->textEdit->insertPlainText("Количество слов в базе = "+QString::number(n)+"\n");
    ui->textEdit_2->insertPlainText("Слог\tСколько найдено слов\n");
    ui->label_2->setText("Найдено слогов: 0");

    int level = ui->spinBox_3->value();

    int findWords = 0;

    int check=0;

    int a = ui->spinBox->value();

    //Найдем в базе все куски указанной длинны.
    QStringList ListFromBase;
    for (int I=0;I<n;I++)
    {
        QString Temp = List.at(I);
        QString Part;
        int l = Temp.length();
        if (l>=a)
        {
            for (int i=0;i<l-a+1;i++)
            {
                Part = Temp.mid(i,a);
                int was=HQt_SearchQStringInQStringList (ListFromBase, Part);
                if (was<0) ListFromBase << Part;
            }
        }
        QGuiApplication::processEvents();
    }

    ui->textEdit->insertPlainText("В базе слов найдено уникальныз слогов длинны "+QString::number(a)+" = "+QString::number(ListFromBase.length())+"\n");

    for (int j=0;j<ListFromBase.count();j++)
    {
        check++;
        QString Syllable;

        Syllable = ListFromBase.at(j);

        //Если уже в игре слог был, то завершаем.
        int was=HQt_SearchQStringInQStringList (ListTicTacBoom, Syllable);
        if (was>=0) continue;

        int s = 0;
        QString Temp;
        for (int i=0;i<n;i++)
        {
            Temp = List.at(i);
            if (Temp.indexOf(Syllable)>=0)
                s++;
        }

        if (s > level)
        {

            ui->textEdit->insertPlainText(Syllable+"\n");
            ui->textEdit_2->insertPlainText(Syllable + "\t"+QString::number(s)+"\n");
            findWords++;
            ui->label_2->setText("Найдено слогов: "+QString::number(findWords)+". Проверено всего: "+QString::number(check));

            QTextCursor c =  ui->textEdit->textCursor();
            c.movePosition(QTextCursor::End);
            ui->textEdit->setTextCursor(c);

            QTextCursor c2 =  ui->textEdit_2->textCursor();
            c2.movePosition(QTextCursor::End);
            ui->textEdit_2->setTextCursor(c2);
        }

        QGuiApplication::processEvents();
    }

    ui->label_2->setText("Найдено слогов: "+QString::number(findWords)+". Проверено всего: "+QString::number(check));

    ui->textEdit->insertPlainText("Найдено слогов = "+QString::number(findWords)+"\n");
    ui->textEdit->insertPlainText("Конец поиска\n");

    QTextCursor c =  ui->textEdit->textCursor();
    c.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(c);

    QTextCursor c2 =  ui->textEdit_2->textCursor();
    c2.movePosition(QTextCursor::End);
    ui->textEdit_2->setTextCursor(c2);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();

    QString ListFromFile = HQt_ReadFile("efremova.txt");
    QStringList List = HQt_QStringToQStringList(ListFromFile);
    QStringList ListTrim;
    int n=List.count();
    ui->textEdit->insertPlainText("n = "+QString::number(n)+"\n");
    for (int i=0;i<n;i++)
    {
        QString Temp = List.at(i);
        Temp = Temp.trimmed();
        ListTrim << Temp;
        QGuiApplication::processEvents();
    }
    ui->textEdit->insertPlainText("Первая стадия прошла\n");
    n=ListTrim.count();
    ui->textEdit->insertPlainText("n = "+QString::number(n)+"\n");
    for (int i=0;i<n-1;i++)
    {
        QString Temp = ListTrim.at(i);
        QString Temp2 = ListTrim.at(i+1);
        if ((Temp2=="ср.")||(Temp2=="м.")||(Temp2=="ж."))
            ui->textEdit_2->insertPlainText(Temp+"\n");
        QGuiApplication::processEvents();
    }
    ui->textEdit->insertPlainText("Вторая стадия прошла\n");

    QString file=ui->textEdit_2->toPlainText();;
    HQt_SaveFile(file, "text.txt");
}
