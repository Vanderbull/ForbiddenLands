#ifndef ITEM_H
#define ITEM_H

// Move this structure to its own file when possible
struct items
{
    std::string icon = "./icons/uiAtlas/ui_game_symbol_other.png";
    std::string name_1 = "";
    std::string name_2 = "";
    std::string name_3 = "";
    int unidentified = 0;
    int type = 0;
    int bonus = 0;
    int save = 0; // armour class
    int cursed = 0;
    int amount = 0;
    int weight = 0;
    int value = 0;
    int properties_1 = 0;
    int properties_2 = 0;
    int properties_3 = 0;
    int equipped = 0;
    int damage_vs_small = 0;
    int damage_vs_large = 0;

    items()
    {
        bool ArmourAndShield = false;
        bool MiscellaneousMagic = false;
        bool MiscellaneousWeapons = false;
        bool Potions = false;
        bool Rings = false;
        bool RodsStavesAndWands = false;
        bool Scrolls = false;
        bool Swords = false;

        value = Generate(0,256);
        amount = Generate(0,256);
        // MASTER MAGIC ITEM TABLES
        switch( Generate(0,7) )
        {
        case 0:
            {
                ArmourAndShield = true;
                // FORM
                switch( Generate(0,8) )
                {
                    case 0:
                    {
                        name_1 = "Banded";
                    } break;
                    case 1:
                    {
                        name_1 = "Chain Mail";
                    } break;
                    case 2:
                    {
                        name_1 = "Leather";
                    } break;
                    case 3:
                    {
                        name_1 = "Plate Mail";
                    } break;
                    case 4:
                    {
                        name_1 = "Ring Mail";
                    } break;
                    case 5:
                    {
                        name_1 = "Splinted";
                    } break;
                    case 6:
                    {
                        name_1 = "Scale Mail";
                    } break;
                    case 7:
                    {
                        name_1 = "Studded Leather";
                    } break;
                    case 8:
                    {
                        name_1 = "Shield";
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        case 1:
            {
                MiscellaneousMagic = true;
               switch( Generate(0,4) )
                {
                    case 0:
                    {
                        name_1 = "Common";
                    } break;
                    case 1:
                    {
                        name_1 = "Less Common";
                    } break;
                    case 2:
                    {
                        name_1 = "Uncommon";
                    } break;
                    case 3:
                    {
                        name_1 = "Rare";
                    } break;
                };
               switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "Incense of Meditation";
                    } break;
                    case 1:
                    {
                        name_2 = "Javelin of the Raptor";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 2:
                    {
                        name_2 = "Thunder Spear";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 3:
                    {
                        name_2 = "Boots of Elvenkind";
                    } break;
                    case 4:
                    {
                        name_2 = "Candle of Invocation";
                    } break;
                    case 5:
                    {
                        name_2 = "Dust of Appearance";
                    } break;
                };
            }break;
        case 2:
            {
            MiscellaneousWeapons = true;
               switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_1 = "Arrow";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 1:
                    {
                        name_1 = "Axe";
                        damage_vs_small = 6;
                        damage_vs_large = 4;
                    } break;
                    case 2:
                    {
                        name_1 = "Bolt";
                        damage_vs_small = 4;
                        damage_vs_large = 4;
                    } break;
                    case 3:
                    {
                        name_1 = "Bow";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        case 3:
            {
            Potions = true;
               switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_1 = "Potion";
                    } break;
                    case 1:
                    {
                        name_1 = "Potion";
                    } break;
                    case 2:
                    {
                        name_1 = "Potion";
                    } break;
                    case 3:
                    {
                        name_1 = "Potion";
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        case 4:
            {
            Rings = true;
            //FORM
            name_1 = "Ring";

                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "Charisma";
                    } break;
                    case 1:
                    {
                        name_2 = "Feather Falling";
                    } break;
                    case 2:
                    {
                        name_2 = "Fire Resistance";
                    } break;
                    case 3:
                    {
                        name_2 = "Free Action";
                    } break;
                    case 4:
                    {
                        name_2 = "Genie Summoning";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Invisibility";
                    } break;
                };
            }break;
        case 5:
            {
            RodsStavesAndWands = true;
            name_1 = "";

                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "Rod of Absorption";
                    } break;
                    case 1:
                    {
                        name_2 = "Rod of Cancellation";
                    } break;
                    case 2:
                    {
                        name_2 = "Rod of Captivation";
                    } break;
                    case 3:
                    {
                        name_2 = "Rod of Lordly Might";
                    } break;
                    case 4:
                    {
                        name_2 = "Rod of Resurrection";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Rod of Rulership";
                    } break;
                };
            }break;
        case 6:
            {
            Scrolls = true;
            // TYPE
               switch( Generate(0,2) )
                {
                    case 0:
                    {
                        name_1 = "Spell";
                    } break;
                    case 1:
                    {
                        name_1 = "Protection";
                    } break;
                    case 2:
                    {
                        name_1 = "Cursed";
                    } break;
                };
                //SPELLS
                switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_2 = "Cleric";
                    } break;
                    case 1:
                    {
                        name_2 = "Druid";
                    } break;
                    case 2:
                    {
                        name_2 = "Illusionist";
                    } break;
                    case 3:
                    {
                        name_2 = "Magic User";
                    } break;
                };
            }break;
        case 7:
            {
                Swords = true;
                // FORM
               switch( Generate(0,3) )
                {
                    case 0:
                    {
                        name_1 = "Bastard Sword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 1:
                    {
                        name_1 = "Broadsword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 2:
                    {
                        name_1 = "Longsword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                    case 3:
                    {
                        name_1 = "Shortsword";
                        damage_vs_small = 6;
                        damage_vs_large = 6;
                    } break;
                };
                //PROPERTIES
                switch( Generate(0,5) )
                {
                    case 0:
                    {
                        name_2 = "+1";
                        bonus = 1;
                    } break;
                    case 1:
                    {
                        name_2 = "+2";
                        bonus = 2;
                    } break;
                    case 2:
                    {
                        name_2 = "+3";
                        bonus = 3;
                    } break;
                    case 3:
                    {
                        name_2 = "+4/+5";
                        bonus = 4;
                    } break;
                    case 4:
                    {
                        name_2 = "Cursed";
                        cursed = 1;
                    } break;
                    case 5:
                    {
                        name_2 = "Special";
                    } break;
                };
            }break;
        }
    };

    items( int aValue )
    {
        name_1 = "WATER GOT DAMN IT";
    };

    std::string getName()
    {
        return name_1 + " " + name_2 + " " + name_3;
    };

    friend std::ostream& operator <<(std::ostream& os, items const& a)
    {
        return os << a.name_1 << " " << a.name_2 << " " << a.name_3 << ' '
                  << a.unidentified << ' '
                  << a.type << ' '
                  << a.bonus << ' '
                  << a.save << ' '
                  << a.cursed << ' '
                  << a.amount << ' '
                  << a.weight << ' '
                  << a.value << ' '
                  << a.properties_1 << ' '
                  << a.properties_2 << ' '
                  << a.properties_3 << ' '
                  << a.equipped << ' ';
    }
};

items gameItems[100];

#endif
