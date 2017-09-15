/*Copyright 2017 RGBender*/

 // Class: SkillManager.h

 // Purpose: This library have all methods needed to manage the skills of the player.

#ifndef __SKILLMANAGER__
#define __SKILLMANAGER__

#include <stdint.h>
#include <map>
#include <functional>

class Player;

// Defines a value for each color of the sprites of the skills
enum default_inks{
	BLANK = 0,
	RED = 1,
	GREEN = 2,
	BLUE = 3
};

// Handle the status of the skills of the player, such as cooldowns and skill pairs.
class SkillManager{

public:
	// Class creator method.
	SkillManager(Player *p_Player);

	// Sets the pair of the player skills and combine them.
	void setSkillPair(std::pair<default_inks, default_inks>* combinedSkills, default_inks, bool* isFirst);

	// Receives the information containing which skills is being used.
	std::function<uint8_t*()> getSkill(std::pair<default_inks, default_inks> combinedSkills);

	// Starts the cooldown timer of the skill.
	void setCoolDownTrigger(std::pair<default_inks, default_inks> combinedSkills);

	// Resets the cooldown timer of the skill.
	void resetCooldown(int);

	// Receives the cooldown map of the skill that is in use,
	std::map<std::pair<default_inks, default_inks>, bool>* getCoolDownMap(){
		return &m_coolDownMap;
	}
private:
	Player *m_player;

	// Defining the possible colours for the skills.
	uint8_t* purple();
	uint8_t* brown();
	uint8_t* cyan();
	uint8_t* redPlus();
	uint8_t* greenPlus();
	uint8_t* bluePlus();
	uint8_t* blank(int);

	std::map<std::pair<default_inks, default_inks>, std::function< uint8_t*()> > m_skills;
	std::map<std::pair<default_inks, default_inks>, bool> m_coolDownMap;

};

#endif
