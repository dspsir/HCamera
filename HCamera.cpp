#include "HCamera.h"

HCamera::HCamera(QObject *parent) : QObject(parent)
{  
    list = QCameraInfo::availableCameras();
    for (int i = 0; i < list.size(); i++)
    {
        qDebug() << list.at(i).deviceName(); //获取设备名称
        qDebug() << list.at(i).description();
        qDebug() << list.at(i).position();
        qDebug() << "###############";
    }


}

bool HCamera::Open(int idx, QWidget *parent)
{
    Close();

    if(list.size() <= idx) return false;

    cam = QSharedPointer<QCamera>(new QCamera(list[idx], parent));
    viewfinder = QSharedPointer<QCameraViewfinder>(new QCameraViewfinder(parent));
    imagecapturer = QSharedPointer<QCameraImageCapture>(new QCameraImageCapture(cam.get()));
    cam->setViewfinder(this->viewfinder.get());

    connect(cam.get(), SIGNAL(stateChanged(QCamera::State)), this, SLOT(OnCamStateChanged(QCamera::State)));

    return true;
}

void HCamera::Close()
{
    Stop();

    if(cam == nullptr) return;

    disconnect(cam.get(), SIGNAL(stateChanged(QCamera::State)), this, SLOT(OnCamStateChanged(QCamera::State)));
    imagecapturer.clear();
    cam.clear();
    viewfinder.clear();
}

bool HCamera::Start()
{
    if(cam == nullptr) return false;
    cam->start();

    return true;
}

void HCamera::Stop()
{
    if(cam == nullptr) return;
    cam->stop();
}

void HCamera::OnCamStateChanged(QCamera::State state)
{
    if(state == QCamera::State::ActiveState)
    {
        QList<QCameraViewfinderSettings> list = cam->supportedViewfinderSettings();

        if(list.size())
        {
            cam->setViewfinderSettings(list[0]);
        }
        else
        {
//            QCameraViewfinderSettings set;
//            set.setResolution(760, 438);
//            set.setPixelAspectRatio(770, 438);
//            set.setPixelFormat(QVideoFrame::PixelFormat::Format_YUV420P);
//            cam->setViewfinderSettings(set);
        }

    }
}
