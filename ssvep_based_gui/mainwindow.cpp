#include <QMenuBar>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);

    ssvepwindow = new SSVEPWindow();
    ssvepwindow->setFormat(format);

    dictionary = new Dictionary();

    createActions();
    createMenu();

    text = new QString();

    label = new QLabel(this);
    label->setGeometry(10,50,280,30);
    label->setText("Here you will see the test text");

    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Write here the words");
    lineEdit->setGeometry(10,100,280,30);
    lineEdit->setFocus();

    writeButton = new QPushButton("write", this);
    writeButton->move(300, 100);
    writeButton->show();

    deleteButton = new QPushButton("delete", this);
    deleteButton->move(300, 50);
    deleteButton->show();

    acceptFirstButton = new QPushButton("accept 1st", this);
    acceptFirstButton->move(10, 150);
    acceptFirstButton->show();

    acceptSecondButton = new QPushButton("accept 2nd", this);
    acceptSecondButton->move(110, 150);
    acceptSecondButton->show();

    acceptThirdButton = new QPushButton("accept 3rd", this);
    acceptThirdButton->move(210, 150);
    acceptThirdButton->show();

    connect(writeButton, SIGNAL(clicked()), this, SLOT(updateText()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteText()));
    connect(lineEdit, &QLineEdit::textChanged, this, &MainWindow::predict);

    connect(acceptFirstButton, SIGNAL(clicked()), this, SLOT(acceptFirst()));
    connect(acceptSecondButton, SIGNAL(clicked()), this, SLOT(acceptSecond()));
    connect(acceptThirdButton, SIGNAL(clicked()), this, SLOT(acceptThird()));

}

MainWindow::~MainWindow()
{
    ssvepwindow->close();
    delete ssvepwindow;
    delete dictionary;

    //delete attributes
    delete label;
    delete text;
    delete lineEdit;

    delete writeButton;
    delete deleteButton;

    delete acceptFirstButton;
    delete acceptSecondButton;
    delete acceptThirdButton;

    //delete menus
    delete runAct;
    delete stopAct;
    delete exitAct;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ssvepwindow->close();
    event->accept();
}

void MainWindow::createMenu()
{
    filemenu = menuBar()->addMenu("&File");
    filemenu->addAction(runAct);
    filemenu->addAction(stopAct);
    filemenu->addSeparator();
    filemenu->addAction(exitAct);
}

void MainWindow::createActions()
{
    runAct = new QAction("&Run");
    connect(runAct, &QAction::triggered, ssvepwindow, &SSVEPWindow::show);

    stopAct = new QAction("&Stop");
    connect(stopAct, &QAction::triggered, ssvepwindow, &SSVEPWindow::hide);

    exitAct = new QAction("&Exit");
    connect(exitAct, &QAction::triggered, ssvepwindow, &SSVEPWindow::close);
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::updateText()
{
    QString word = lineEdit->text();

    if(!correctWord(word))
        return;

    text->append(word + " ");

    label->setText(*text);
    lineEdit->setText("");
}

void MainWindow::deleteText()
{
    text->clear();
    label->setText(*text);
}

void MainWindow::predict()
{
    QString word = lineEdit->text();
    if(word.at(word.size()-1) == '<')
        word.chop(1);

    dictionary->predict(word);
    ssvepwindow->setPredictons(dictionary->getPredictedWords());
}

void MainWindow::acceptFirst()
{
    if(dictionary->getPredictedWords().size() > 0)
        lineEdit->setText(dictionary->getPredictedWords()[0]);
}

void MainWindow::acceptSecond()
{
    if(dictionary->getPredictedWords().size() > 1)
        lineEdit->setText(dictionary->getPredictedWords()[1]);
}

void MainWindow::acceptThird()
{
    if(dictionary->getPredictedWords().size() > 2)
        lineEdit->setText(dictionary->getPredictedWords()[2]);
}

bool MainWindow::correctWord(QString word)
{
    for(int i = 0; i < word.size(); ++i)
    {
        bool symbolFound = false;

        for(int j = 0; j < SYMBOL_COUNT; ++j)
            if(word.mid(i, 1) == SYMBOLS[j])
                symbolFound = true;

        if(!symbolFound)
            return false;
    }

    return true;
}
