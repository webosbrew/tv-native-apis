#include "Acb.h"

Acb::Acb() {}
Acb::~Acb() {}
bool Acb::initialize(long playerType, std::string appId, std::function<void(long, long, long, long, const char *)> handler) { return false; }
long Acb::getAcbId() { return -1; }
bool Acb::setMediaId(std::string mediaId) { return false; }
bool Acb::setState(long appState, long playState, long *taskId) { return false; }
bool Acb::setDisplayWindow(long x, long y, long w, long h, bool fullScreen, long *taskId) { return false; }
bool Acb::setCustomDisplayWindow(long in_x, long in_y, long in_w, long in_h, long out_x, long out_y, long out_w, long out_h, bool fullScreen, long *taskId) { return false; }
void Acb::setMediaAudioData(std::string param, long *taskId) {}
void Acb::setMediaVideoData(std::string param, long *taskId) {}
long Acb::setSubWindowInfo(std::string param, long *taskId) { return -1; }
void Acb::changePlayerType(long playerType) {}
void Acb::connectDass(long, long *taskId) {}
void Acb::disconnectDass(long *taskId) {}
void Acb::setVsmInfo(long sinkType, long dassAction, long sinkPurpose) {}
void Acb::startMute(bool audio, bool video, long *taskId) {}
void Acb::stopMute(bool audio, bool video, long *taskId) {}
bool Acb::setSinkType(long sinkType) { return false; }
void Acb::finalize() {}