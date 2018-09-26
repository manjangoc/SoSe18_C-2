#include <QtGui>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include "zeichenFeld.h"

QPainter painter;

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    //Farbe wird gesetzt fuer Kasten
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    //Definition der Position der Objekte
    lastX=100;
    lastY=10;
    lastCircleY=10;
    lastRechtY=10;
    increment=10;
    phase=0;
}

zeichenFeld::~zeichenFeld()
{
}

//Objekte werden gezeichnet
void zeichenFeld::paintEvent(QPaintEvent *event)
{
    QPainter painter;
        int x,y,width,height;

        // Score
        painter.begin(this);
        painter.drawText(10, 20, "Score: " + QString::number(playerScore));
        playerScore++;

        //Rechteck von oben
        if (lastY<500){ // Objekt bewegt sich entlang der Y-Achse. Wenn Objekt kleiner als 500 ist, wird Objekt nicht mehr gezeichnet und somit entfernt.
        painter.begin(this); // Objekt wird gezeichnet
        x=lastX-0;  //Position Figur
        y=lastY-0;  //Position Figur
        painter.setPen(QPen(Qt::green, 2)); // Farbe Figur
        painter.drawRect(x, y, 50, 25); // Objekt Figur & Größre
        }

        //Kreis von oben
        if (lastCircleY<500){
        painter.begin(this);
        x=lastX+150;
        y=lastCircleY-0;
        painter.setPen(QPen(Qt::red, 2));
        painter.drawEllipse(x,y,50,50);
        }

        //Rechteck von oben
        if (lastRechtY<500){
        painter.begin(this);
        x=lastX+300;
        y=lastRechtY-0;
        painter.setPen(QPen(Qt::blue, 2));
        painter.drawRect(x, y, 25, 50);
        }

        //Spielfigur
        painter.begin(this);
        painter.setPen(QPen(Qt::black, 3));
        painter.setBrush(QBrush(Qt::BDiagPattern));
        painter.drawRect(lastFigurX, lastFigurY, 50, 50);

        //Leben 1
        painter.begin(this);
        x=lastX+345;
        y=lastLebenY+10;
        painter.setPen(QPen(Qt::red, 12));
        painter.drawPoint(x, y); //Ausgefülltes Objekt
        //Leben 2
        painter.begin(this);
        x=lastX+365;
        y=lastLebenY+10;
        painter.setPen(QPen(Qt::red, 12));
        painter.drawPoint(x, y);
        // Leben 3
        painter.begin(this);
        x=lastX+385;
        y=lastLebenY+10;
        painter.setPen(QPen(Qt::red, 12));
        painter.drawPoint(x, y);


        //Objekte fallen von oben nach unten. Funktion lässt Objekt immer wieder von oben Fallen.
             if (increment)
             switch(phase)
             {
             case 0:
                 if (lastY<500) lastY++;
                 else {
                        phase=0;
                        lastY=-50;
                 }

                 if (lastCircleY<500) lastCircleY = lastCircleY + 0.8;
                 else {
                        lastCircleY=-50;
                 }
                 if (lastRechtY<500) lastRechtY = lastRechtY + 1.1;
                 else {
                        lastRechtY=-50;
                 }
                 break;
              }

       painter.end();
}

//Bewegung der Spielfigur durch Pfeiltaste
void zeichenFeld::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Left)
    {
        if(lastFigurX>=25)
          lastFigurX = lastFigurX - 25;
        update();
    }

    if (event->key() == Qt::Key_Right)
    {
        if(lastFigurX<450)
          lastFigurX = lastFigurX + 25;
        update();
    }
}

//Speichern in Savegame
void zeichenFeld::serialize(QFile &file)
{
    QTextStream out(&file);

        out << "p "<< playerScore;
        out << " " << playerDirection;
        out << " " << y;
        out << " " << lastCircleY;
        out << " " << lastFigurX;
        out << " " << lastRechtY;
}

//Laden des Savegames
void zeichenFeld::deserialize(QFile &file)
{
    char c;

    QTextStream in(&file);

    while (in.status() == QTextStream::Ok)
    {
        in >> c;
        if (in.status() == QTextStream::ReadPastEnd) break;

        if (c!='p')
        {
            QMessageBox::warning(this, tr("Objektfehler"),
                                 tr("Folgender Objekttyp ist unbekannt: ") + c,QMessageBox::Ok);
            return;
        }

        in >> playerScore >> playerDirection >> y >> lastCircleY  >> lastFigurX >> lastRechtY;
    }

    update();
}
