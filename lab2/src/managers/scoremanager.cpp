#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>

#include "include/managers/scoremanager.h"

ScoreManager::ScoreManager(const QString &filename, int max_lvl_) : filename(filename), max_lvl(max_lvl_), best_times(max_lvl_)
{
    read_status = false;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        std::fill(best_times.begin(), best_times.end(), 0);
        return;
    }

    QByteArray fileContent = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent);

    if (jsonDoc.isNull()) {
        std::fill(best_times.begin(), best_times.end(), 0);
        return;
    }

    QJsonObject save = jsonDoc.object();

    if (!save.contains("max_lvl") || !save["max_lvl"].isDouble()
        || !save.contains("best_times") || !save["best_times"].isArray()) {
        std::fill(best_times.begin(), best_times.end(), 0);
        return;
    }

    max_lvl = save["max_lvl"].toInt();

    if (max_lvl == 0 || max_lvl != max_lvl_) {
        max_lvl = max_lvl_;
        best_times.resize(max_lvl);
        std::fill(best_times.begin(), best_times.end(), 0);
        return;
    }

    QJsonArray best_scores_records = save["best_times"].toArray();
    best_times.resize(max_lvl);

    for (int i = 0; i < max_lvl; ++i) {
        best_times[i] = best_scores_records[i].toInt();
    }

    read_status = true;
}

ScoreManager::~ScoreManager() {}

void ScoreManager::saveBestScore(int lvl, int score)
{
    best_times[lvl - 1] = score;
    WriteBestScore();
}

int ScoreManager::getBestScore(int lvl) const
{
    return best_times[lvl - 1];
}

bool ScoreManager::getReadStatus()
{
    return read_status;
}

void ScoreManager::WriteBestScore()
{
    QJsonObject save;
    save["max_lvl"] = max_lvl;

    QJsonArray best_scores_records;
    for (int i = 0; i < max_lvl; i++) {
        best_scores_records.append(best_times[i]);
    }
    save["best_times"] = best_scores_records;

    QJsonDocument jsonDoc(save);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson(QJsonDocument::Compact));
        file.close();
    }
}
