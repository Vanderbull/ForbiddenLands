#ifndef QUEST_H
#define QUEST_H
struct quest {
        int id;
        std::string name;
        int experience;
        int gold;
};

std::map<int, quest> quests;

// Should be able to generate quest items here
quest MakeQuest( int n, const char* s, int experience = 0, int gold = 0 )
{
    quest q = { n, s, experience, gold };
    return q;
};

void initQuests()
{
    quests[0] = MakeQuest( IN_PROGRESS, "Clear the slums immediately west of the Civilized Area.  Reward: 450 XP, 250 gold. 15 Random encounters clears this",450, 250);
    quests[1] = MakeQuest( PENDING, "Clear Sokal Keep of its spectral guardians. (Note: The Keep is considered cleared once Ferran Martinez has been told the truth. The shipping lanes will also be open to traffic. If you leave the Keep before telling the truth to Martinez, the Undead Patrols will be reset.) Reward: 1308 XP, 250 platinum.");
    quests[2] = MakeQuest( PENDING, "Return books, maps, and tomes with useful information.  This is resolved once you clear Mendor's Library (defeat the basilisk and spectre), not when you actually return all the books of interest.  Reward: 208 XP, 250 gold.");
    quests[3] = MakeQuest( PENDING, "Discover what item is to be auctioned in Podal Plaza.  This mission cannot be performed until it is offered.  If you get close enough for the auction to begin, that is enough; you do not need to actually discover what the item is.  Reward: 208 XP, 250 gold.");
    quests[4] = MakeQuest( PENDING, "Speak to Junior Councilman Porphyrys Cadorna, who has a mission; you must resolve commission #2 to be asked this.",833,200);
    quests[5] = MakeQuest( PENDING, "Speak to Bishop Braccio, who has a mission (only asked once).  Completing that mission will be recognized here, but your only reward is praise and getting to keep any items you found in the temple; it will also not negate any anger caused by fighting the city guard, unlike all the other missions here.");
    quests[6] = MakeQuest( PENDING, "Clear old Kovel Mansion of the thieves that operate there; you must resolve commission #2 to receive this.",191,800);
    quests[7] = MakeQuest( PENDING, "Prevent the nomads from joining forces with Phlan's enemies.",983,100);
    quests[8] = MakeQuest( IN_PROGRESS, "Prevent the kobolds from joining forces with Phlan's enemies.",1841,100);
    quests[9] = MakeQuest( PENDING, "Find the source of the Stojanow River's pollution and end it.",5708,2000);
    quests[10] = MakeQuest( PENDING, "Prevent the lizardmen from joining forces with Phlan's enemies.",2466,2300);
    quests[11] = MakeQuest( PENDING, "Rescue the heir to the house of Bivant; this mission cannot be performed until it is offered, and you cannot receive it if commission #2 has not been completed.  if you instead failed the mission, the clerk complains 'By the way, your bungling the Bivant rescue has cost us.'Reward: Two-Handed Sword +1, +3 Vs. Undead and 4 Clerical Scroll (Restoration, Restoration);",3208);
    quests[12] = MakeQuest( PENDING, "Go on a diplomatic mission to the Zhentil Keep Outpost to the west. This mission cannot be performed until it is offered, which requires commission #5 to be resolved.  You will either first be asked to speak to Senior Councilman Porphyrys Cadorna by going through the south door, or be given the mission directly if you have learned that Cadorna is a traitor by visiting Valjevo Castle 26. and if you have not already learned it, you are told that Porphyrys Cadorna is a traitor to New Phlan.  (You are also told he has a bounty upon his head, but none is actually paid.)",2125);
    quests[13] = MakeQuest( PENDING, "If you have resolved commission #13: Visit Head Councilman Urslingen, through the south door of Cadorna's old office, where he will ask you to capture Stojanow Gate.",3666);
    quests[14] = MakeQuest( IN_PROGRESS, "If you have resolved commission #14: Visit the council chambers, where you are asked to lead the assault on Valjevo Castle and defeat Tyranthraxus, which wins the game.",45000,300);
};

void renderQuestProgress()
{
    for (const auto& [key, value] : quests)
    {
        if( value.id == IN_PROGRESS )
        {
            if( randomEncounters >= 1 )
            {
                std::cout << "You finished the first of all quest" << std::endl;
                quests[key].id = DONE;
            }
            if( randomEncounters >= 1 )
            {
                std::cout << "You finished the fourth of all quest" << std::endl;
                quests[key].id = DONE;
            }
        }
    }
};

void renderQuests( bool hidden = true )
{
    if( hidden )
        return;

    int i = 0;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0,128);
    SDL_Rect questBackground = {current.w - 1020,380,1020,500};
    SDL_RenderFillRect(renderer, &questBackground);

    for (const auto& [key, value] : quests)
    {
        if( value.id == IN_PROGRESS )
        {
             RenderTextWrapped(value.name, White, current.w - 490, 500+i*120,24,660);
             RenderText("X", Red, current.w - 50, 500+i*120,24);
             i++;
        }
    }

    renderQuestProgress();
};


#endif
