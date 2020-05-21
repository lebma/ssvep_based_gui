#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QPainter>

static const QString SYMBOLS[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "_", "<", "del"};
static const int SYMBOL_COUNT = 29;

class SSVEPWindow : public QOpenGLWindow,
               protected QOpenGLFunctions
{
  Q_OBJECT

// OpenGL Events
public:
  ~SSVEPWindow();

  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
  void teardownGL();
  void setPredictons(std::vector<QString> predictions);

public slots:
  void draw();


private:
  // Private Helpers
  void printContextInformation();
  void calculatePositions();

  QPainter *painter;
  int count[SYMBOL_COUNT + 3];
  bool visible[SYMBOL_COUNT + 3];
  int posX[SYMBOL_COUNT];
  int posY[SYMBOL_COUNT];

  int horizontalGap;
  int verticalGap;
  int letterWidth;
  int letterHeight;

  int rowLength;
  int rowCount;

  QFont *font;
  QColor *color1;
  QColor *color2;

  std::vector<QString> predictions;
};

#endif // WINDOW_H
