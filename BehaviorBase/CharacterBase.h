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
	// �X�L�����������Ă��邩
	bool HasSkill()
	{
		if (skillList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// ���@���������Ă��邩
	bool HasMagic()
	{
		if (magicList.size() > 0)
		{
			return true;
		}
		return false;
	}

	// HP�I�[�o�[����
	bool IsHpPercentOver(float check_percent);

	// MP�I�[�o�[����
	bool IsMpPercentOver(float check_percent);

	// ���S����
	bool IsDie();
protected:
	vector<int> skillList;	// �X�L�����X�g
	vector<int> magicList;	// ���@���X�g

	float hp_;			// HP
	float maxHp_;		// �ő�HP
	float mp_;			// MP
	float maxMp_;		// �ő�MP
	float attack_;		// �U����
	float deffence_;	// �h���
};

