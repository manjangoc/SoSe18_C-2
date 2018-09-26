#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include "meinWidget.h"


//Definition Buttons
meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{

    QPushButton *start =new QPushButton(tr("Start"));
    start->setFont(QFont("Times", 18, QFont::Bold));
    connect(start, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *stopButton = new QPushButton(tr("Stopp"));
    stopButton->setFont(QFont("Times", 18, QFont::Bold));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    QPushButton *saver =new QPushButton(tr("Sichern"));
    saver->setFont(QFont("Times", 18, QFont::Bold));
    connect(saver, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *loader =new QPushButton(tr("Laden"));
    loader->setFont(QFont("Times", 18, QFont::Bold));
    connect(loader, SIGNAL(clicked()), this, SLOT(loadFile()));


    meinZeichenFeld->setFixedSize(500, 500);
    meinZeichenFeld->setFocusPolicy(Qt::StrongFocus);


    //Elemente Fenster hinzufügen
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(start, 0, 0);
    gridLayout->addWidget(stopButton, 1, 0);
    gridLayout->addWidget(loader,2, 0);
    gridLayout->addWidget(saver, 3, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 4, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);

}

// Verknüpfung Funktion mit Buttons
void meinWidget::start(void) //start
{
    meinZeichenFeld->start();
}

void meinWidget::stop(void) //stop
{
    meinZeichenFeld->stop();
}

void meinWidget::saveFile(void) // Funktion Speichern
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

void meinWidget::loadFile(void) //Funktion Laden
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geÃ¶ffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}
