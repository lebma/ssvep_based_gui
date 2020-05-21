#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include "ssvepwindow.h"
#include "dictionary.h"
#include <QPushButton>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateText(/*QString symbol*/);
    void deleteText();
    void predict();
    void acceptFirst();
    void acceptSecond();
    void acceptThird();

private:
    void createMenu();
    void createActions();
    bool correctWord(QString word);
    void closeEvent(QCloseEvent *event);

    SSVEPWindow *ssvepwindow;
    Dictionary *dictionary;

    QString *text;
    QLabel *label;

    QMenu *filemenu;
    QAction *runAct;
    QAction *stopAct;
    QAction *exitAct;

    //variables for modelling the hole system
    QLineEdit *lineEdit;
    QPushButton *writeButton;
    QPushButton *deleteButton;
    QPushButton *acceptFirstButton;
    QPushButton *acceptSecondButton;
    QPushButton *acceptThirdButton;

signals:

};

#endif // MAINWINDOW_H
