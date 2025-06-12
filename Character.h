#pragma once
class Character
{
public:
	Character(int level, int health, int strength, int dexterity, int intelligence, int wisdom, int charisma)
		: level(level),
		  health(health),
		  strength(strength),
		  dexterity(dexterity),
		  intelligence(intelligence),
		  wisdom(wisdom),
		  charisma(charisma)
	{
	}

private:
	int level;
	int health;
	int strength;
	int dexterity;
	int intelligence;
	int wisdom;
	int charisma;
};

