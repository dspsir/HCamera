#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QCameraInfo> list = cam.Devices();
    int n = list.size();
    for(int i = 0; i < n; i ++)
    {
        QCameraInfo &info = list[i];
        ui->cbCams->addItem(info.deviceName());
    }

    connect(ui->cbCams, SIGNAL(currentIndexChanged(int)), this, SLOT(OnCamListChanged(int)));
    connect(ui->pbSwitch, SIGNAL(clicked()), this, SLOT(OnSwitchClicked()));

    if(ui->cbCams->count())
    {
        ui->cbCams->setCurrentIndex(0);
        emit ui->cbCams->currentIndexChanged(ui->cbCams->currentIndex());
    }
}

MainWindow::~MainWindow()
{
    cam.Close();

    delete ui;
}

void MainWindow::OnSwitchClicked()
{
    if(ui->pbSwitch->text() == tr("开始"))
    {
        ui->pbSwitch->setText(tr("停止"));
        cam.Start();
    }
    else
    {
        ui->pbSwitch->setText(tr("开始"));
        cam.Stop();
    }
}

void MainWindow::OnCamListChanged(int index)
{
    cam.Close();
    cam.Open(index, this);
    QWidget *vf = cam.ViewFinder();
    ui->vl->addWidget(vf);
}
