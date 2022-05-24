#ifndef RENDER_CHARACTER_CREATION_H
#define RENDER_CHARACTER_CREATION_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

void renderCharacterCreation()
{
    std::string raceDescriptions;

    int localCounter = 0;
    SDL_Rect TextFrame = {0, 0, 0, 0};
    SDL_Rect TextFrame2 = {0, 0, 0, 0};
    std::vector<std::string> textElements = { "STR ", "INT ", "WIS ", "DEX ", "CON ", "CHA "};
    std::vector<SDL_Rect> raceElements;
    std::vector<std::string> raceTextElements = { "DWARF", "ELF", "GNOME", "HALFELF", "HALFLING", "HALFORC", "HUMAN"};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    playerCharacter[currentCharacter].renderFace();

    RenderText(std::to_string(statPoints[currentCharacter]) + " Stat Points Left",White, 50,325, 24);
    counter = 0;

    for (std::string textElement : textElements)
    {
        RenderText(textElement.c_str()+std::to_string(playerCharacter[currentCharacter].current_stats[counter]),Green, 50,370+(counter*50), 24);

        TextFrame = FrameText("+",300, 370+(counter*50), 24);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &TextFrame);
        RenderText("+",White, 300,370+(counter*50), 24);

        TextFrame2 = FrameText("-",340, 370+(counter*50), 24);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &TextFrame2);
        RenderText("-",White, 340,370+(counter*50), 24);

        if( statPoints[currentCharacter] >= 0 )
        {
            if( SDL_PointInRect(&mousePosition, &TextFrame) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    if( statPoints[currentCharacter] > 0)
                    {
                        playerCharacter[currentCharacter].current_stats[counter]++;
                        statPoints[currentCharacter]--;
                        SDL_Delay(50);
                    }
                }
            }
            else
            if( SDL_PointInRect(&mousePosition, &TextFrame2) & SDL_BUTTON(SDL_BUTTON_LEFT) )
            {
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    if( playerCharacter[currentCharacter].current_stats[counter] > 3)
                    {
                        playerCharacter[currentCharacter].current_stats[counter]--;
                        statPoints[currentCharacter]++;
                        SDL_Delay(50);
                    }
                }
            }
        }
        counter++;
    }

    SDL_Rect rerollButton = {700, 600, 100, 50};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rerollButton);
    RenderText("Re roll",Black, 700,600, 24);

    if( SDL_PointInRect(&mousePosition, &rerollButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            playerCharacter[currentCharacter].current_stats[0] = GenerateNumber(3,18);
            playerCharacter[currentCharacter].current_stats[1] = GenerateNumber(3,18);
            playerCharacter[currentCharacter].current_stats[2] = GenerateNumber(3,18);
            playerCharacter[currentCharacter].current_stats[3] = GenerateNumber(3,18);
            playerCharacter[currentCharacter].current_stats[4] = GenerateNumber(3,18);
            playerCharacter[currentCharacter].current_stats[5] = GenerateNumber(3,18);

            statPoints[currentCharacter] = 5;
            SDL_Delay(50);
        }
    }

    if( currentCharacter > 5 )
        currentCharacter = 0;

    RenderText("Number: " + std::to_string(currentCharacter),White,current.w - 700,0,FontSize);
    int HorizontalPosition = current.w - 400;

    counter = 0;

    for (std::string textElement : raceTextElements)
    {
        SDL_Rect rect;
        rect.x = current.w - 1300;
        rect.y = 220+(counter*40);
        rect.w = 300;
        rect.h = 30;
        raceElements.push_back(rect);
        counter++;
    }

    SDL_Rect nextCharacter = {current.w - 500,0,600,30};
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &nextCharacter);
    RenderText("NEXT CHARACTER",Black,current.w - 500,0,FontSize);

    counter = 0;
    for (std::string textElement : raceTextElements)
    {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderFillRect(renderer, &raceElements[counter]);
        RenderText(textElement.c_str(),Black,raceElements[counter].x,raceElements[counter].y,FontSize);
        counter++;
    }

    if( SDL_PointInRect(&mousePosition, &nextCharacter) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            currentCharacter++;
            if( currentCharacter > 5)
            {
                LoadMenu = 0;
                SaveMenu = 0;
            }
            SDL_Delay(100);
        }
    }

    for( int i = 0; i < 7; i++ )
    {
        if( playerCharacter[currentCharacter].race == i )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &raceElements[i]);

            if( playerCharacter[currentCharacter].race == 0)
            {
            std::string raceDescriptions;
             raceDescriptions = "Dwarfs\n" \
             "Dwarfs are a short and burly race, living in mountain fastnesses"\
             "underground. They are loyal friends and fierce adversaries,"\
             "known for their steadfastness in all things."\
             "\n"\
             "The dwarfs are inherently resistant to many spells and spell-like"\
             "effects. Dwarfish characters gain bonuses against the use of"\
             "most magic, including all spells, wands, rods, and staves. The"\
             "amount of the bonus depends upon the dwarf’s constitution:"\
             "every 3.5 points of constitution (rounding down fractions)"\
             "grants a bonus of +1 against such magic. Moreover, the hardy"\
             "dwarfish nature imparts a similar bonus on any saving throws"\
             "against poison.Dwarfs are not a numerous folk, but they are adventurous,"\
             "loving the lustre of gold, the glitter of gems, and the quality"\
             "of well-wrought metals. Dwarfs can live to an age of 350 years"\
             "or more.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);

                 std::string stats = "Strength " + std::to_string(racialLimitations[0][0]) + "/" + std::to_string(racialLimitations[0][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[0][2]) + "/" + std::to_string(racialLimitations[0][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[0][4]) + "/" + std::to_string(racialLimitations[0][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[0][6]) + "/" + std::to_string(racialLimitations[0][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[0][8]) + "/" + std::to_string(racialLimitations[0][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[0][10]) + "/" + std::to_string(racialLimitations[0][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 1)
            {
            std::string raceDescriptions;
             raceDescriptions = "Elves\n"\
"Elves are thinner and generally smaller in stature than humans."\
"The elves have a powerful bond with nature and do not have"\
"souls; their thinking and motives are quite alien to those of"\
"humankind, and in any dealings with elves, it is perilous to"\
"forget this."\
"Some elven clans have built elaborate civilisations, remote and"\
"beautiful places of profound learning, master craftsmanship, and"\
"long history. Such elves tend to be chaotic good in alignment and"\
"friendly, if aloof, from humans. More numerous are the wilder"\
"friendly to other races, inclining even toward hostility."\
"Intruding into the territory of such elves is inadvisable, for their"\
"sense of humour with regard to humans is, at best, arbitrary"\
"and, at worst, cruel. Different as they are, these varied elven cul-"\
"tures all share the same racial abilities, unless the GM chooses"\
"otherwise. Elves can live to an age of 1,000 years or more.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);
                 std::string stats = "Strength " + std::to_string(racialLimitations[1][0]) + "/" + std::to_string(racialLimitations[1][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[1][2]) + "/" + std::to_string(racialLimitations[1][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[1][4]) + "/" + std::to_string(racialLimitations[1][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[1][6]) + "/" + std::to_string(racialLimitations[1][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[1][8]) + "/" + std::to_string(racialLimitations[1][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[1][10]) + "/" + std::to_string(racialLimitations[1][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 2)
            {
            std::string raceDescriptions;
             raceDescriptions = "Gnomes\n"\
"Gnomes are small folk imbued with the wilding power of il-"\
"lusion and misdirection. They are inveterate burrowers, often"\
"seeking hilly lands where gems and precious metals may be"\
"found. On average, they are shorter and slimmer of build than"\
"dwarfs, with larger noses and longer beards."\
"Like dwarfs, who are perhaps related to gnomes from some"\
"time in the distant and mythical past, gnomes are quite re-"\
"sistant to magic and sensitive to the nuances of construction."\
"Gnomes can live to an age of 650 years or more.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);
                 std::string stats = "Strength " + std::to_string(racialLimitations[2][0]) + "/" + std::to_string(racialLimitations[2][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[2][2]) + "/" + std::to_string(racialLimitations[2][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[2][4]) + "/" + std::to_string(racialLimitations[2][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[2][6]) + "/" + std::to_string(racialLimitations[2][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[2][8]) + "/" + std::to_string(racialLimitations[2][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[2][10]) + "/" + std::to_string(racialLimitations[2][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 3)
            {
            std::string raceDescriptions;
             raceDescriptions = "Halflings\n"\
"Halﬂings are a small and unprepossessing race, often living"\
"near human settlements at an agreeable remove from the bus-"\
"tle and hurriedness characteristic of humans. Halﬂ ing society"\
"is comfortable and staid, rooted in polite, placid, well-fed life."\
"Halﬂ ing adventurers are thought aberrant, even lunatic, but"\
"also dashing and heroic fi gures, a charming and amusing con-"\
"tradiction of logic."\
"Halﬂ ings value learning and craftsmanship, as long as nothing"\
"is taken to an embarrassing extreme. They are capable of mov-"\
"ing very quietly and are excellent marksmen; given the right"\
"personality, halﬂ ings can become excellent thieves. Halﬂ ings"\
"live to be 150 or more years old.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);
                 std::string stats = "Strength " + std::to_string(racialLimitations[3][0]) + "/" + std::to_string(racialLimitations[3][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[3][2]) + "/" + std::to_string(racialLimitations[3][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[3][4]) + "/" + std::to_string(racialLimitations[3][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[3][6]) + "/" + std::to_string(racialLimitations[3][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[3][8]) + "/" + std::to_string(racialLimitations[3][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[3][10]) + "/" + std::to_string(racialLimitations[3][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 4)
            {
            std::string raceDescriptions;
             raceDescriptions = "half-elves\n"\
"It is possible for elves and humans to interbreed, although el-"\
"ven fastidiousness makes this a fairly uncommon occurrence."\
"Half elves do not have a separate culture or civilisation of their"\
"own, usually assimilating into the elven or human society in"\
"which they were raised.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);
                 std::string stats = "Strength " + std::to_string(racialLimitations[4][0]) + "/" + std::to_string(racialLimitations[4][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[4][2]) + "/" + std::to_string(racialLimitations[4][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[4][4]) + "/" + std::to_string(racialLimitations[4][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[4][6]) + "/" + std::to_string(racialLimitations[4][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[4][8]) + "/" + std::to_string(racialLimitations[4][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[4][10]) + "/" + std::to_string(racialLimitations[4][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 5)
            {
            std::string raceDescriptions;
             raceDescriptions = "half-orcs\n"\
"The progeny of human/orc breeding are normally indistin-"\
"guishable from orcs. However, a few are suffi ciently human"\
"to gain levels in a character class, although they are severely"\
"limited in classes that do not focus upon violence and death."\
"Orcish blood runs strong in these half-breeds, and most of"\
"them are shifty, morally questionable, and unsophisticated."\
"They are typically ugly, carrying the mark of orcish ancestry,"\
"but the same ancestry makes them deadly adversaries when"\
"the chips are down and the swords are out. Half-orcs can live"\
"to be 70 years old or older.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);
                 std::string stats = "Strength " + std::to_string(racialLimitations[5][0]) + "/" + std::to_string(racialLimitations[5][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[5][2]) + "/" + std::to_string(racialLimitations[5][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[5][4]) + "/" + std::to_string(racialLimitations[5][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[5][6]) + "/" + std::to_string(racialLimitations[5][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[5][8]) + "/" + std::to_string(racialLimitations[5][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[5][10]) + "/" + std::to_string(racialLimitations[5][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
            else
            if( playerCharacter[currentCharacter].race == 6)
            {
            std::string raceDescriptions;
             raceDescriptions = "Humans\n"\
"Humans are the standard for the game, and as such, humans"\
"have no unusual abilities or limitations in game terms. Because"\
"of their potential for unlimited progression in all the character"\
"classes save assassin and druid, humans are a popular choice"\
"for most players. This is an intentional feature of the rules."\
"A common house rule in OSRIC-compatible games is the"\
"adjustment or removal of demi-human level limits. This will"\
"unbalance the game in favour of demi-humans unless humans"\
"are given some corresponding advantage. GMs considering"\
"such a house rule for their own OSRIC-compatible games are"\
"advised to ensure that in most campaigns, humans should still"\
"represent an attractive choice for their players.";
             RenderText3(raceDescriptions.c_str(),White, 550,900, 24);
                 std::string stats = "Strength " + std::to_string(racialLimitations[6][0]) + "/" + std::to_string(racialLimitations[6][1]) + "\n\n"\
                                    "Dexterity " + std::to_string(racialLimitations[6][2]) + "/" + std::to_string(racialLimitations[6][3]) + "\n\n"\
                                    "Constitution " + std::to_string(racialLimitations[6][4]) + "/" + std::to_string(racialLimitations[6][5]) + "\n\n"\
                                    "Intelligence " + std::to_string(racialLimitations[6][6]) + "/" + std::to_string(racialLimitations[6][7]) + "\n\n"\
                                    "Wisdom " + std::to_string(racialLimitations[6][8]) + "/" + std::to_string(racialLimitations[6][9]) + "\n\n"\
                                    "Charisma " + std::to_string(racialLimitations[6][10]) + "/" + std::to_string(racialLimitations[6][11]) + "\n\n";
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
                RenderText3(stats.c_str(),White, current.w - 1600,500, 24);
            }
        }
        if( SDL_PointInRect(&mousePosition, &raceElements[i]) & SDL_BUTTON(SDL_BUTTON_LEFT) )
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 128);
            SDL_RenderFillRect(renderer, &raceElements[i]);
            SDL_PumpEvents();
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                playerCharacter[currentCharacter].race = i;
            }
        }
    }

    SDL_Rect ExitButton = {current.w - 220,current.h - 50,200,30};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ExitButton);

    if( SDL_PointInRect(&mousePosition, &ExitButton) & SDL_BUTTON(SDL_BUTTON_LEFT) )
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &ExitButton);
        SDL_PumpEvents();
        if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            LoadMenu = 0;
            SaveMenu = 0;
            CreateCharacter = 0;
            SettingsMenu = 0;
        }
    }
    RenderText("EXIT",Black,ExitButton.x + 10,ExitButton.y + 5,FontSize);
};

#endif // RENDER_CHARACTER_CREATION_H
