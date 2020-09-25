#ifndef HCAMERA_H
#define HCAMERA_H

#include <QObject>
#include <QSharedPointer>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QList>
#include <QString>

class HCamera : public QObject
{
    Q_OBJECT
public:
    explicit HCamera(QObject *parent = nullptr);
    bool Open(int idx, QWidget *parent = nullptr);
    void Close();
    bool Start();
    void Stop();
    QWidget *ViewFinder() { return viewfinder.get(); }
    const QList<QCameraInfo> &Devices() { return list; };
protected:
    QSharedPointer<QCamera> cam;
    QSharedPointer<QCameraViewfinder> viewfinder;
    QSharedPointer<QCameraImageCapture> imagecapturer;
    QList<QCameraInfo> list;
protected slots:
    void OnCamStateChanged(QCamera::State state);
signals:

};

#endif // HCAMERA_H
