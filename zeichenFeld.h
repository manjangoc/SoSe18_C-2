#include <QWidget>
#include <QFile>
#include <QTimer>
 
class zeichenFeld : public QWidget
{
    Q_OBJECT

    public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    void serialize(QFile &file);
    void deserialize(QFile &file);

    void start(void) { timer->start(1); increment=1; };
    void stop(void) { timer->stop(); increment=0; };

    QTimer *timer;

    private:
    int playerScore = 0;
    int playerDirection = 0;

    //QTimer *timer;

    int x=225, y=225;
    int lastX;
    int lastY;
  //  int lastCircleX;
    float lastCircleY;
  //  int lastRechtX;
    float lastRechtY;
    int lastFigurX = 250;
    int lastFigurY = 400;
    int lastLebenY;

    int increment;
    int phase;

    protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};


