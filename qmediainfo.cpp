#include "qmediainfo.h"

QMediaInfo::QMediaInfo()
{
    _lib = new QLibrary("MediaInfo.dll");
    _lib->load();
    MEDIAINFO_New v = (MEDIAINFO_New)_lib->resolve("MediaInfo_New");
    _pMedia = v();
}

bool QMediaInfo::Open(const QString &filename) {
    if (!IsLoaded()) return false;
    MEDIAINFO_Open mopen = (MEDIAINFO_Open)_lib->resolve("MediaInfo_Open");
    if ((mopen(_pMedia, filename.toStdWString().c_str())) == 0) return false;
    return true;
}

QString QMediaInfo::Inform() const {
    MEDIAINFO_Inform inf = (MEDIAINFO_Inform)_lib->resolve("MediaInfo_Inform");
    if (!inf) return NULL;
    return QString::fromStdWString(inf(_pMedia,0));
}

wchar_t *QMediaInfo::Get(int streamKind, int streamNumber, wchar_t* parameter,
                         int infoKind, int searchKind) const{
    MEDIAINFO_Get get = (MEDIAINFO_Get)_lib->resolve("MediaInfo_Get");
    if (!get) return NULL;
    return get(_pMedia, streamKind, streamNumber, parameter, infoKind, searchKind);
}

QString QMediaInfo::Duration() const {
    wchar_t *prop=L"Duration/String3";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::VideoBitRate() const {
    wchar_t *prop=L"BitRate/String";
    return QString::fromStdWString(Get(1, 0, prop, 1, 0));
}

QString QMediaInfo::AudioBitRate() const {
    wchar_t *prop=L"BitRate/String";
    return QString::fromStdWString(Get(2, 0, prop, 1, 0));
}

QString QMediaInfo::VideoResolution() const {
    wchar_t *propH=L"Height";
    wchar_t *propW=L"Width";
    QString sW = QString::fromStdWString(Get(1, 0, propW, 1, 0));
    QString sH = QString::fromStdWString(Get(1, 0, propH, 1, 0));
    if (sW.isEmpty() || sH.isEmpty())
        return "";
    return sW + "x" + sH;
}

QString QMediaInfo::VideoFrameRate() const {
    wchar_t *prop=L"FrameRate/String";
    return QString::fromStdWString(Get(1, 0, prop, 1, 0));
}

QString QMediaInfo::VideoCodec() const {
    wchar_t *prop=L"InternetMediaType";
    wchar_t *propF=L"Format";
    QString codec;
    codec = QString::fromStdWString(Get(1, 0, prop, 1, 0));
    if (codec.isEmpty())
        return QString::fromStdWString(Get(1, 0, propF, 1, 0));
    return codec;
}

QString QMediaInfo::AudioCodec() const {
    wchar_t *prop=L"InternetMediaType";
    wchar_t *propF=L"Format";
    QString codec;
    codec = QString::fromStdWString(Get(2, 0, prop, 1, 0));
    if (codec.isEmpty())
        return QString::fromStdWString(Get(2, 0, propF, 1, 0));
    return codec;
}

int QMediaInfo::StreamCount(int stream) const {
    wchar_t *prop=L"StreamCount";
    return QString::fromStdWString(Get(stream, 0, prop, 1, 0)).toInt();
}

QString QMediaInfo::AudioLanguages() const {
    wchar_t *prop=L"Language";
    QString lang;

    int cs = StreamCount(2);
    for (int i=0;i<cs;i++) {
        if (i!=0) lang += "/";
        lang += QString::fromStdWString(Get(2, i, prop, 1, 0));
    }
    if (lang.isEmpty()) return QString::number(cs);
    return lang;
}

QString QMediaInfo::SubtitleLanguages() const {
    wchar_t *prop=L"Language";
    QString lang;

    int cs = StreamCount(3);
    for (int i=0;i<cs;i++) {
        if (i!=0) lang += "/";
        lang += QString::fromStdWString(Get(3, i, prop, 1, 0));
    }
    if (lang.isEmpty()) return QString::number(cs);
    return lang;
}

QString QMediaInfo::Title() const {
    wchar_t *prop=L"Title";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::TitleMore() const {
    wchar_t *prop=L"Title/More";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::Domain() const {
    wchar_t *prop=L"Domain";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::Collection() const {
    wchar_t *prop=L"Collection";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::Season() const {
    wchar_t *prop=L"Season";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::Movie() const {
    wchar_t *prop=L"Movie";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::Description() const {
    wchar_t *prop=L"Movie";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::FileSize() const {
    wchar_t *prop=L"FileSize/String";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::FormatExt() const {
    wchar_t *prop=L"Format/Extensions";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::CompleteName() const {
    wchar_t *prop=L"CompleteName";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::Filename() const {
    wchar_t *prop=L"FileName";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

QString QMediaInfo::FileExtension() const {
    wchar_t *prop=L"FileExtension";
    return QString::fromStdWString(Get(0, 0, prop, 1, 0));
}

bool QMediaInfo::IsLoaded() {
    return (_lib->isLoaded());
}

QMediaInfo::~QMediaInfo() {
    MEDIAINFO_Delete d = (MEDIAINFO_Delete)_lib->resolve("MediaInfo_Delete");
    d(_pMedia);
    _lib->unload();
}
