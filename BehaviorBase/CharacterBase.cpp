#include "CharacterBase.h"

bool CharacterBase::IsHpPercentOver(float check_percent)
{
	float percent = hp_ / maxHp_;

	if (percent * 100.0f >= check_percent)
	{
		return true;
	}

	return false;
}

bool CharacterBase::IsMpPercentOver(float check_percent)
{
	float percent = mp_ / maxMp_;

	if (percent * 100.0f >= check_percent)
	{
		return true;
	}

	return false;
}

bool CharacterBase::IsDie()
{
	return hp_ <= 0.0f ? true : false;
}

