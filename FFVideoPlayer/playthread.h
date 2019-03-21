#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H
#include <QThread>

class PlayThread : public QThread
{
    Q_OBJECT

public:
    static PlayThread* GetObj()
    {
        static PlayThread pt;
        return &pt;
    }

    ~PlayThread();

    void run();

protected:
    PlayThread();
};
#endif // PLAYTHREAD_H
