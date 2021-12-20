#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <bits/stdc++.h>

/*
struct saveGameData
{
    std::vector<int> readyCharacterInventoryAC;
    std::vector<int> readyCharacterInventoryTHACO;
    std::vector<int> readyCharacterInventoryDamage;
    std::vector<int> readyCharacterInventoryCost;

    std::string name = "default";

    int str_current = 0;
    int int_current = 0;
    int wis_current = 0;
    int dex_current = 0;
    int con_current = 0;
    int cha_current = 0;

    int coins_copper = 0;
    int coins_silver = 0;
    int coins_electrum = 0;
    int coins_gold = 0;
    int coins_platinum = 0;

    int gems = 0;
    int jewellery = 0;
    int gender = 0;
    int ac_base = 0;
    int thaco_base = 0;
    int experience = 0;
    int hit_points_rolled = 0;
    int xp_award = 0;
    int xp_bonus_per_hp = 0;
    int encumbrance = 0;
    int thaco_current = 0;
    int ac_current = 0;
    int hitpoints_current = 10;
    int level_cleric = 0;
    int level_fighter = 0;
    int level_magic_user = 0;
    int level_thief = 0;
    int uuid = 0;

    saveGameData()
    {
        update();
        name = setName();
        gender = rand()%2;
        str_current = rand()%18;
        int_current = rand()%18;
        wis_current = rand()%18;
        dex_current = rand()%18;
        con_current = rand()%18;
        cha_current = rand()%18;

        coins_copper = rand()%100;
        coins_silver = rand()%100;
        coins_electrum = rand()%100;
        coins_gold = rand()%100;
        coins_platinum = rand()%100;

        level_cleric = 1;
        level_fighter = 1;
        level_magic_user = 1;
        level_thief = 1;
        uuid++;
    };

    std::string setName()
    {
        char Player1Name[21];
        NameGen(Player1Name);
        name = Player1Name;
        return name;
    };

    std::string getName()
    {
        return name;
    };

    int getGems()
    {
        return gems;
    };

    int getJewellery()
    {
        return jewellery;
    };

    int getClericLevel()
    {
        return level_cleric;
    };

    int getFighterLevel()
    {
        return level_fighter;
    };

    int getMagicUserLevel()
    {
        return level_magic_user;
    };

    int getThiefLevel()
    {
        return level_thief;
    };

    int getExperience()
    {
        return experience;
    }

    int getHitpoints()
    {
        return hitpoints_current;
    }

    int getEncumbrance()
    {
        int encumbranceTotal = 0;
        encumbranceTotal += coins_copper;
        encumbranceTotal += coins_silver;
        encumbranceTotal += coins_electrum;
        encumbranceTotal += coins_gold;
        encumbranceTotal += coins_platinum;
        return encumbranceTotal;
    }

    int getArmourClass()
    {
        ac_current = ac_base;
        for(const auto& value: readyCharacterInventoryAC)
        {
            if( value == 1)
                ac_current++;
        }
        return ac_current;
    }

    int getToHitArmourClass()
    {
        thaco_current = thaco_base;
        for(const auto& value: readyCharacterInventoryTHACO)
        {
            if( value == 1)
                thaco_current++;
        }
        return thaco_current;
    }

    std::string getGender()
    {
        if( gender == 0)
            return "MALE";
        else
            return "FEMALE";
    }

    std::string getRace()
    {
        return "DWARF";
    }

    void update()
    {
        getEncumbrance();
        //ac_current = rand()%10;
    }

};

saveGameData saveGames[6];

struct CoordinatePair
{
    int x;
    int y;
    int z;
};

// Starting point from original game @ pier
CoordinatePair saveCoordinate = {0,4,0};
/*
void savingGameData( std::string saveFile )
{
    std::ofstream SaveGame;
    SaveGame.open(saveFile.c_str());

    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame << saveGames[i].getName() << std::endl;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame << saveGames[i].getArmourClass() << std::endl;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame << saveGames[i].getClericLevel() << std::endl;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame << saveGames[i].getEncumbrance() << std::endl;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame << saveGames[i].getExperience() << std::endl;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame << saveGames[i].getFighterLevel() << std::endl;
    }
    SaveGame << saveCoordinate.x << std::endl;
    SaveGame << saveCoordinate.y << std::endl;
    SaveGame.close();
}

void loadingGameData( std::string saveFile )
{
    std::ifstream SaveGame;
    SaveGame.open(saveFile.c_str());
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame >> saveGames[i].name;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame >> saveGames[i].ac_current;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame >> saveGames[i].level_cleric;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame >> saveGames[i].encumbrance;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame >> saveGames[i].experience;
    }
    for( int i = 0; i < sizeof(saveGames)/sizeof(saveGames[0]); i++ )
    {
        SaveGame >> saveGames[i].level_fighter;
    }
    SaveGame >> saveCoordinate.x;
    SaveGame >> saveCoordinate.y;
    SaveGame.close();
}
*/
#endif
