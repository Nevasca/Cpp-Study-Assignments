#pragma once
#include <map>

#include "Enemy.h"
#include "EnemyReportEntry.h"
#include "Sizes.h"

class EnemiesReport
{
    std::map<Sizes, EnemyReportEntry> report;
public:
    void Add(Enemy& enemy);
    std::string ToString();
};
