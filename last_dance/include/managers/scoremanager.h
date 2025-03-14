#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QFile>

class ScoreManager
{
public:
    ScoreManager(const QString& filename, int max_lvl = 0);
    ~ScoreManager();
    void saveBestScore(int lvl, int score);
    int getBestScore(int lvl) const;
    bool getReadStatus();

private:
    void WriteBestScore();

    QString filename;
    int max_lvl;
    int* best_times;
    bool read_status;
};

#endif // SCOREMANAGER_H
