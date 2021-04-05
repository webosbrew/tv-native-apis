#pragma once

#include <functional>
#include <string>

namespace ACB
{
    enum PlayerType : long
    {
        GROUP = 0L,
        VIDEO,
        VIDEO_UNMUTED_AFTER_PLAYING,
        AUDIO,
        HTML5_AUDIO,
        TV,
        EXT_INPUT,
        DVR,
        VCS,
        DIRECT_VIDEO,
        DIRECT_AUDIO,
        MSE,
        QT_DVR,
        PHOTO,
    };

    enum AppState : long
    {
        INITIALIZED = 0,
        FOREGROUND = 1,
        BACKGROUND = 2,
    };

    enum PlayState : long
    {
        UNLOADED = 0,
        LOADED = 1,
        SEAMLESS_LOADED = 2,
        PLAYING = 3,
        PAUSED = 4,
        AUDIO_ONLY_PLAYING = 5,
        FROZEN = 6,
    };

    enum StateSinkType : long
    {
        AUTO_ = 0,
        MAIN = 1,
        SUB = 2,
    };

    enum DassAction : long
    {
        AUTO = 0,
        MANUAL = 1,
    };

    enum VsmPurpose : long
    {
        NONE = 0,
        MULTI_VIEW = 1,
        LIVE_ZOOM = 2,
    };
}

class Acb
{
public:
    Acb();
    ~Acb();
    
    bool initialize(long playerType, std::string appId, std::function<void(long, long, long, long, const char *)> handler);
    long getAcbId();
    bool setMediaId(std::string mediaId);
    bool setState(long appState, long playState, long *taskId = nullptr);
    bool setDisplayWindow(long x, long y, long w, long h, bool fullScreen, long *taskId = nullptr);
    bool setCustomDisplayWindow(long in_x, long in_y, long in_w, long in_h, long out_x, long out_y, long out_w, long out_h, bool fullScreen, long *taskId = nullptr);
    void setMediaAudioData(std::string param, long *taskId = nullptr);
    void setMediaVideoData(std::string param, long *taskId = nullptr);
    long setSubWindowInfo(std::string param, long *taskId = nullptr);
    void changePlayerType(long playerType);
    void connectDass(long = 0, long *taskId = nullptr);
    void disconnectDass(long *taskId = nullptr);
    void setVsmInfo(long sinkType, long dassAction, long sinkPurpose);
    void startMute(bool audio, bool video, long *taskId = nullptr);
    void stopMute(bool audio, bool video, long *taskId = nullptr);
    void setSinkType(long sinkType);
    void finalize();

private:
    void setDualMode(long *taskId = nullptr);
    void setWindowZOrder(long, long, long *taskId = nullptr);
    void setNonstop();
    void resetWindowZOrder(long *taskId = nullptr);
    void clearMediaInfo();
    void resetDualMode(long *taskId = nullptr);
    void resetScreenSaverTimer();
    void cancelVsmStateSubscription();
    void setSeamlessSwitching(std::string, bool, long *taskId = nullptr);
    void setArcMenuControlMode(bool);
    void setScreenSaverAutoMode(bool);
    void resetDualModeEx(std::string, long *taskId = nullptr);
    void setVideoInfoEx(std::string, long *taskId = nullptr);
    void setStateEx(std::string, long *taskId = nullptr);
    void disconnectDassEx(std::string, long *taskId = nullptr);
    void getVsmStateEx(std::string, std::function<void(char const *, void *)>, void *, long *taskId = nullptr);
    void stopMuteEx(std::string, long *taskId = nullptr);
    void setWindowZOrderEx(std::string, long *taskId = nullptr);
    void setLowDelayModeEx(std::string, long *taskId = nullptr);
    void connectDassEx(std::string, long *taskId = nullptr);
    void rotateVideoEx(std::string, long *taskId = nullptr);
    void resetWindowZOrderEx(std::string, long *taskId = nullptr);
    void setDualModeEx(std::string, long *taskId = nullptr);
    void startMuteEx(std::string, long *taskId = nullptr);
    void setDisplayWindowEx(std::string, long *taskId = nullptr);
    void setAudioInfoEx(std::string, long *taskId = nullptr);
    void setSubWindowInfoEx(std::string, long *taskId = nullptr);
    
    // Must include big enough storage size. 4KB here should be fairly enough
    char padding[4096];
};