#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "include/managers/scoremanager.h"

ScoreManager::ScoreManager(const QString &filename, int max_lvl_) : filename(filename)
{
    read_status = false;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        this->max_lvl = max_lvl_;
        this->best_times = new int[max_lvl_]();
        return;
    }

    QByteArray fileContent = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileContent);

    if (jsonDoc.isNull()) {
        this->max_lvl = max_lvl_;
        this->best_times = new int[max_lvl_]();
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (!jsonObj.contains("max_lvl") || !jsonObj["max_lvl"].isDouble()
        || !jsonObj.contains("best_times") || !jsonObj["best_times"].isArray()) {
        this->max_lvl = max_lvl_;
        this->best_times = new int[max_lvl_]();
        return;
    }

    max_lvl = jsonObj["max_lvl"].toInt();

    if (max_lvl == 0 || max_lvl != max_lvl_) {
        this->max_lvl = max_lvl_;
        this->best_times = new int[max_lvl_]();
        return;
    }

    QJsonArray jsonArray = jsonObj["best_times"].toArray();

    if (jsonArray.size() != max_lvl) {
        this->max_lvl = max_lvl_;
        this->best_times = new int[max_lvl_]();
        return;
    }

    best_times = new int[max_lvl];

    for (int i = 0; i < max_lvl; ++i) {
        best_times[i] = jsonArray[i].toInt();
    }

    read_status = true;
}

ScoreManager::~ScoreManager()
{
    delete best_times;
}

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
    QJsonObject jsonObj;
    jsonObj["max_lvl"] = max_lvl;

    QJsonArray jsonArray;
    for (int i = 0; i < max_lvl; i++) {
        jsonArray.append(best_times[i]);
    }
    jsonObj["best_times"] = jsonArray;

    QJsonDocument jsonDoc(jsonObj);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson(QJsonDocument::Compact));
        file.close();
    }
}
