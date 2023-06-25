#include "EnemiesReport.h"

#include <sstream>

void EnemiesReport::Add(Enemy& enemy)
{
    if(report.count(enemy.Size) == 0)
    {
        report[enemy.Size] = EnemyReportEntry{0, 0};
    }
    
    EnemyReportEntry& entry = report[enemy.Size];
    entry.Total++;

    if(enemy.IsDead())
    {
        entry.TotalDefeated++;
    }
}

std::string EnemiesReport::ToString()
{
    std::stringstream reportResult;
    
    for (const std::pair<const Sizes, EnemyReportEntry>& entry : report)
    {
        reportResult << ConvertSizeToString(entry.first) << ": " << entry.second.TotalDefeated << "/" <<entry.second.Total << std::endl;
    }

    return reportResult.str();
}
