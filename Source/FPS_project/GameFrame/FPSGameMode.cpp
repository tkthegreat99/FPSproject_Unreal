// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"

void AFPSGameMode::UpdateRankingCPP()
{
	int32 RankingIndex = 0;
	for (int32 Index = 0; Index < RankingScoresCPP.Num(); ++Index)
	{
		float Element = RankingScoresCPP[Index];
		if (Element >= ScoreCPP)
		{
			RankingIndex++;
		}
		else
		{
			break;
		}
	}
	RankingCPP = RankingIndex + 1;
	RankingScoresCPP.Insert(ScoreCPP, RankingIndex);
	RankingTimesCPP.Insert(EndTimeCPP.ToString(), RankingIndex);
	if (RankingScoresCPP.Num() > 10)
	{
		RankingScoresCPP.RemoveAt(RankingScoresCPP.Num() - 1);
		RankingTimesCPP.RemoveAt(RankingTimesCPP.Num() - 1);
	}

}