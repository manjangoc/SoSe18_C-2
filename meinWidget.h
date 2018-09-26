#include <QWidget>
#include <QObject>
#include "zeichenFeld.h"


class meinWidget : public QWidget
{
Q_OBJECT

public:
    meinWidget(QWidget *parent = 0);

private:
    zeichenFeld *meinZeichenFeld = new zeichenFeld;

private slots:
    void start(void);
    void stop(void);
    void loadFile(void);
    void saveFile(void);
};
