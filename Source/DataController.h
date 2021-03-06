#ifndef DATA_CONTROLLER_H
#define DATA_CONTROLLER_H

#include <QVideoFrame>
#include "GenericCamera.h"
#include "GenericCameraController.h"
#include "VideoWriter.h"
#include "VideoGLWidget.h"
#include <QList>
#include <QPainter>

enum TriggerType {
    NO_SELECTION,
    NO_CAMERA_TRIGGER,
    EXTERNAL_CAMERA_TRIGGER
};

Q_DECLARE_METATYPE(TriggerType)

enum SavingState {
    NOT_SAVING,
    READY_TO_WRITE,
    CURRENTLY_WRITING
};


class DataController : public QObject
{
    Q_OBJECT
public:
    explicit DataController(VideoWriter* writer, QObject *parent = 0);

signals:
    void updateSavingMenus(SavingState);
    void newFrame(QVideoFrame);

public slots:
    void stopVideo(void);
    void stopVideoWriting(void);
    void initializeVideoWriting(QString filename);
    void startVideoStreaming(bool writeToDisk);
    void startVideoRecording(void) { startVideoStreaming(true); }
    void startVideoViewing(void) { startVideoStreaming(false); }
    void useTriggering(TriggerType trigger) { triggerType = trigger; }
    void registerCamera(GenericCameraInterface *camera);
    void registerCameraController(GenericCameraController *controller);
    void registerVideoWidget(VideoGLWidget *videoWidget);
    void newLeftFrame(QVideoFrame);
    void newRightFrame(QVideoFrame);

private:
    QList<GenericCameraInterface *> cameraList;
    VideoWriter *videoWriter;
    GenericCameraController *cameraController;
    VideoGLWidget *videoWidget;
    int numCameras;
    TriggerType triggerType;
    bool videoIsStreaming;
    QVideoFrame *concatenatingFrame;
    QImage *concatenatingImage;
    bool concatenatingFrameInitialized;
    QPainter *concatenationPainter;
    enum FrameConcatenationState {
        NOT_STARTED,
        LEFT_READY,
        RIGHT_READY
    };
    FrameConcatenationState frameConcatenationState;

    enum WhichFrame {
        left, right
    };

    void concatenateFrames(WhichFrame which, QVideoFrame frame);
};

Q_DECLARE_METATYPE(DataController*)


#endif // DATA_CONTROLLER_H
