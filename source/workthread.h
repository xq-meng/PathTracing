#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include "pathtracing.h"

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread(PathTracing *path_tracing, QObject *parent = nullptr);
    ~WorkThread()   override;
    PathTracing *pt;
    bool        renderover = false;
signals:
    void resultReady(double value);
protected:
    virtual void run() override;
};

#endif // WORKTHREAD_H
