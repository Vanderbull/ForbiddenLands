#ifndef NPC_H
#define NPC_H

int npc_active = 0;
int npc_health[6] = {0,0,0,0,0,0};
int npc_initiative[6] = {0,0,0,0,0,0};
int npc_action[6] = {1,1,1,1,1,1};
int npc_max, npc_min;
int enemyImageID[6] = {0,0,0,0,0,0};
int npc_experience[6] = {0,0,0,0,0,0};
int npc_armour_class[6] = {0,0,0,0,0,0};
int npc_damage[6] = {0,0,0,0,0,0};
int npc_current_damage = 0;
int npc_targeted = 0;
int npcDefending = Generate(1,10);

SDL_Rect npcActionText[6];

std::vector<std::string> enemyImages;

SDL_Rect npc_fighting = {1000, 500,300,300};
//SDL_Rect npc[6];

std::string npc_name = "Unnameable";

void getEnemyImageID()
{
    for( int i = 0; i < 6; i++ )
    {
        enemyImageID[i] = Generate(0,29);
    }
};

struct npcEngine
{
    struct character
    {
        int _active;
        int _health;
        int _initiative;
        int _action;
        int _min, _max;
        int _imageId;
        int _experience;
        int _armourClass;
        int _damage;
        int _currentDamage;
        int _targeted;
        int _defending;
        SDL_Rect SDL_Rectangle;

        character()
        {
            _active = 0;
            _health = 0;
            _initiative = 0;
            _action = 1;
            _min, _max = 0;
            _imageId = 0;
            _experience = 0;
            _armourClass = 0;
            _damage = 0;
            _currentDamage = 0;
            _targeted = 0;
            _defending = Generate(1,10);
        }

        void generateInitiative()
        {
            _initiative = Generate(1,6);
        };
    };

    character NPC[6];

    npcEngine()
    {
        enemyImages.clear();
        enemyImages.push_back("./data/monsters/001_goblin_guard-0.png");
        enemyImages.push_back("./data/monsters/002_goblin_leader-0.png");
        enemyImages.push_back("./data/monsters/003_orc-0.png");
        enemyImages.push_back("./data/monsters/004_orc_leader-0.png");
        enemyImages.push_back("./data/monsters/005_hobgoblin-0.png");
        enemyImages.push_back("./data/monsters/006_hobgoblin_leader-0.png");
        enemyImages.push_back("./data/monsters/007_ogre-0.png");
        enemyImages.push_back("./data/monsters/008_ogre_leader-0.png");
        enemyImages.push_back("./data/monsters/009_4th_lvl_fighter-0.png");
        enemyImages.push_back("./data/monsters/010_kobold-0.png");
        enemyImages.push_back("./data/monsters/011_kobold_leader-0.png");
        enemyImages.push_back("./data/monsters/012_goblin_guard-0.png");
        enemyImages.push_back("./data/monsters/013_kobold_leader-0.png");
        enemyImages.push_back("./data/monsters/014_spectre-0.png");
        enemyImages.push_back("./data/monsters/031_level_6_mu-0.png");

        enemyImages.push_back("./data/monsters/032_mad_man-0.png");
        enemyImages.push_back("./data/monsters/033_basilisk-0.png");
        enemyImages.push_back("./data/monsters/034_troll-0.png");
        enemyImages.push_back("./data/monsters/035_aides-0.png");
        enemyImages.push_back("./data/monsters/036_hill_giant-0.png");

        enemyImages.push_back("./data/monsters/037_bugbear-0.png");
        enemyImages.push_back("./data/monsters/038_ettin-0.png");
        enemyImages.push_back("./data/monsters/039_gnoll-0.png");
        enemyImages.push_back("./data/monsters/040_6th_lvl_fighter-0.png");
        enemyImages.push_back("./data/monsters/042_5th_lvl_mu-0.png");

        enemyImages.push_back("./data/monsters/043_level_3_mu-0.png");
        enemyImages.push_back("./data/monsters/045_nomad-0.png");
        enemyImages.push_back("./data/monsters/046_4th_lvl_fighter-0.png");
        enemyImages.push_back("./data/monsters/047_1st_lvl_thief-0.png");
        enemyImages.push_back("./data/monsters/049_aides-0.png");
        init();
    };

    void init()
    {
        for(int i = 0; i < 6; i++)
        {
            npc_action[i] == 1;
        }

        for(int i = 0; i < 6; i++)
        {
            if( enemyImageID[i] == 0) // Goblin guard
            {
                npc_name = "goblin guard";
                npc_health[i] = 5;
                npc_initiative[i] = 6;
                npc_experience[i] = 11;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 1) // Goblin leader
            {
                npc_name = "goblin leader";
                npc_health[i] = 7;
                npc_initiative[i] = 4;
                npc_experience[i] = 20;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 2) // Orc
            {
                npc_name = "orc";
                npc_health[i] = 5;
                npc_initiative[i] = 6;
                npc_experience[i] = 20;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 3) // Orc leader
            {
                npc_name = "orc leader";
                npc_health[i] = 8;
                npc_initiative[i] = 5;
                npc_experience[i] = 20;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 4) // Hobgoblin
            {
                npc_name = "hobgoblin";
                npc_health[i] = 5;
                npc_initiative[i] = 6;
                npc_experience[i] = 22;
                npc_armour_class[i] = 5;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 5) // Hobgoblin leader
            {
                npc_name = "hobgoblin leader";
                npc_health[i] = 5;
                npc_initiative[i] = 6;
                npc_experience[i] = 22;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 6) // ogre
            {
                npc_name = "ogre";
                npc_health[i] = 5;
                npc_initiative[i] = 6;
                npc_experience[i] = 20;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 7) // ogre leader
            {
                npc_name = "ogre leader";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 8) // 4th level fighter
            {
                npc_name = "4th level fighter";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 9) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 10) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 11) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 12) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 13) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 14) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 15) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 16) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 17) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 18) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 19) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 20) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 21) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 22) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 23) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 24) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 25) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 26) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 27) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 28) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }
            if( enemyImageID[i] == 29) // kobold
            {
                npc_name = "kobold";
                npc_health[i] = 15;
                npc_initiative[i] = 6;
                npc_experience[i] = 40;
                npc_armour_class[i] = 6;
                                NPC[i]._damage = 6;
            }

            int imageSize = 100;
            NPC[0].SDL_Rectangle = {current.w - imageSize, 0,imageSize,144};
            NPC[1].SDL_Rectangle = {current.w - imageSize, 150,imageSize,144};
            NPC[2].SDL_Rectangle = {current.w - imageSize, 300,imageSize,144};
            NPC[3].SDL_Rectangle = {current.w - imageSize, 450,imageSize,144};
            NPC[4].SDL_Rectangle = {current.w - imageSize, 600,imageSize,144};
            NPC[5].SDL_Rectangle = {current.w - imageSize, 750,imageSize,144};
        }
    };
};


#endif
