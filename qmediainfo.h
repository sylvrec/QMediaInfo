#ifndef QMEDIAINFO_H
#define QMEDIAINFO_H

#include <iostream>
#include <string>
#include <QLibrary>

typedef void* (*MEDIAINFO_New)();
typedef void (*MEDIAINFO_Delete)(void*);
typedef size_t (*MEDIAINFO_Open)(void*, const wchar_t *);
typedef wchar_t* (*MEDIAINFO_Inform)(void*, long);
typedef wchar_t* (*MEDIAINFO_Get)(void*, int, int, wchar_t *, int, int);

#define STREAM_GENERAL = 0
#define STREAM_VIDEO = 1
#define STREAM_AUDIO = 2
#define STREAM_SUBTITLE = 3

class QMediaInfo
{
public:
    QMediaInfo();
    bool IsLoaded();
    QString CompleteName() const;
    QString Filename() const;
    QString FileExtension() const;
    QString Title() const;
    QString TitleMore() const;
    QString Domain() const;
    QString Collection() const;
    QString Season() const;
    QString Movie() const;
    QString Description() const;
    QString Inform() const;
    QString Duration() const;
    QString FileSize() const;
    QString FormatExt() const;
    QString VideoBitRate() const;
    QString AudioBitRate() const;
    QString VideoResolution() const;
    QString VideoFrameRate() const;
    QString VideoCodec() const;
    QString AudioCodec() const;
    QString AudioLanguages() const;
    QString SubtitleLanguages() const;

    bool Open(const QString &filename);
    ~QMediaInfo();
private:
    wchar_t *Get(int streamKind, int streamNumber, wchar_t* parameter, int infoKind, int searchKind) const;
    int StreamCount(int stream) const;

    QLibrary *_lib;
    void *_pMedia;
};

#endif // QMEDIAINFO_H
