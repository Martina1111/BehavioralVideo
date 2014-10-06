#ifndef VIDEOWRITER_H
#define VIDEOWRITER_H

#include <QObject>
#include <QImage>
#include <QFile>
#include <QTabWidget>
#include <QComboBox>
#include "FFMPEG.h"

class VideoWriter : public QObject
{
    Q_OBJECT
public:
    explicit VideoWriter(QObject *parent = 0);
    void addPreferencesPanel(QTabWidget *preferencesTabs);

signals:
    void videoInitialized(void);
    void writingStarted(void);
    void writingEnded(void);

public slots:
    void initialize(QString);
    void newFrame(QImage image);
    void beginWriting(void);
    void endWriting(void);

private:
    int width, height;
    int frameRateNumerator, frameRateDenominator;
    QImage *currentFrame;

    QFile *vFile;
    QString *vFilename;

    bool currentlyWriting;
    bool waitingToInitialize;

    //FFMPEG
    AVOutputFormat *fmt;
    AVFormatContext *oc;
    AVCodec *codec;
    AVStream *video_st;
    AVFrame *picture;
    uint8_t *picture_buf;
    AVFrame *tmp_picture;
    SwsContext *sws_ctx;

    uint8_t *video_outbuf;
    int video_outbuf_size;

    QString videoExt = ".mp4";
    QWidget *prefWidget;
    QComboBox *videoEncoder;
};

Q_DECLARE_METATYPE(VideoWriter*)


#endif // VIDEOWRITER_H
