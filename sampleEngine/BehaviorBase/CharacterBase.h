#pragma once

#include<vector>

class CharacterBase
{
private:
	template <class T> using vector = std::vector<T>;

public:
	CharacterBase(float max_hp, float max_mp, float attack, float deffence) :
		hp_(max_hp),
		maxHp_(max_hp),
		mp_(max_mp),
		maxMp_(max_mp),
		attack_(attack),
		deffence_(deffence)
	{
	}

	float GetHp()
	{
		return hp_;
	}
	float GetMp()
	{
		return mp_;
	}
	float GetAttack()
	{
		return attack_;
	}
	float GetDeffence()
	{
		return deffence_;
	}
	// スキルを所持しているか
	bool HasSkill()
	{
		if (skillList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// 魔法を所持しているか
	bool HasMagic()
	{
		if (magicList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// HPオーバー判定
	bool IsHpPercentOver(float check_percent);

	// MPオーバー判定
	bool IsMpPercentOver(float check_percent);

	// 死亡判定
	bool IsDie();
protected:
	vector<int> skillList;	// スキルリスト
	vector<int> magicList;	// 魔法リスト

	float hp_;			// HP
	float maxHp_;		// 最大HP
	float mp_;			// MP
	float maxMp_;		// 最大MP
	float attack_;		// 攻撃力
	float deffence_;	// 防御力
};

