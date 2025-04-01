#pragma once
#include "PlayerStats.h"

class StatsObserver
{
public:
	virtual ~StatsObserver() = default;
	virtual void onStatsUpdated(const PlayerStats& stats) = 0;
};

