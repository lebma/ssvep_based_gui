#include "ssvepwindow.h"
#include <QDebug>
#include <QString>

SSVEPWindow::~SSVEPWindow()
{
  makeCurrent();
  teardownGL();
}

/*******************************************************************************
 * OpenGL Events
 ******************************************************************************/

void SSVEPWindow::initializeGL()
{
    this->setMinimumWidth(800);
    this->setMinimumHeight(900);

    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    printContextInformation();

    // Set global information
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    font = new QFont("Times", 40, QFont::Bold);
    QFontMetrics fm(*font);

    color1 = new QColor(255, 255, 255);
    color2 = new QColor(0, 0, 0);

    letterWidth = fm.horizontalAdvance(SYMBOLS[0]);
    letterHeight = fm.height();

    horizontalGap = (this->width()-6*letterWidth)/7;
    verticalGap = this->height()/5 - letterHeight;

    for(int i = 0; i < SYMBOL_COUNT + 3; ++i)
    {
        count[i] = 0;
        visible[i] = true;
    }

    calculatePositions();

    predictions.clear();

    connect(this, &SSVEPWindow::frameSwapped, this, &SSVEPWindow::paintGL);
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
}

void SSVEPWindow::resizeGL(int width, int height)
{
    // Currently we are not handling width/height changes
        (void)width;
        (void)height;

        horizontalGap = (this->width()-6*letterWidth)/6.5;
        verticalGap = this->height()/6 - letterHeight;

        calculatePositions();
}

void SSVEPWindow::paintGL()
{
    delete painter;
    painter = new QPainter(this);
    painter->setFont(*font);

    glClearColor(0.35, 0.35, 0.35, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    draw();
    //connect(this, &Window::frameSwapped, this, &Window::draw);
}

void SSVEPWindow::teardownGL()
{
    // Currently we have no data to teardown
    delete painter;
    delete font;
}

/*******************************************************************************
 * Private Helpers
 ******************************************************************************/

void SSVEPWindow::printContextInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

void SSVEPWindow::draw()
{
    for(int i = 0; i < SYMBOL_COUNT; ++i)
    {
        if(visible[i])
        {
            painter->setPen(*color1);
            painter->drawText(posX[i], posY[i], SYMBOLS[i]);
        }
        else
        {
            painter->setPen(*color2);
            painter->drawText(posX[i], posY[i], SYMBOLS[i]);
        }

        if(count[i] > i)
        {
            count[i] = 0;
            visible[i] = !visible[i];
        }
        else {
            ++count[i];
        }
    }

    int posx = horizontalGap;
    int posy = verticalGap + (rowCount+1)*(verticalGap+letterHeight);;

    for(size_t i = 0; i < predictions.size(); ++i)
    {
        if(visible[SYMBOL_COUNT + i])
        {
            painter->setPen(*color1);
            painter->drawText(posx, posy, predictions[i]);
        }
        else
        {
            painter->setPen(*color2);
            painter->drawText(posx, posy, predictions[i]);
        }

        if(count[SYMBOL_COUNT + i] > SYMBOL_COUNT + (int)i)
        {
            count[SYMBOL_COUNT + i] = 0;
            visible[SYMBOL_COUNT + i] = !visible[SYMBOL_COUNT + i];
        }
        else {
            ++count[SYMBOL_COUNT + i];
        }

        posx += (this->width()-horizontalGap)/3;
    }

}

void SSVEPWindow::calculatePositions()
{
    rowLength = horizontalGap;
    rowCount = 0;

    for(int i = 0; i < SYMBOL_COUNT; ++i)
    {
        posX[i] = rowLength;
        posY[i] = verticalGap + rowCount*(verticalGap+letterHeight);
        if(rowLength > this->width())
        {
            rowLength = horizontalGap;
            ++rowCount;
            posX[i] = rowLength;
            posY[i] = verticalGap + rowCount*(verticalGap+letterHeight);
        }
        rowLength += (letterWidth+horizontalGap);
    }
}

void SSVEPWindow::setPredictons(std::vector<QString> predictions)
{
    this->predictions = predictions;
}
