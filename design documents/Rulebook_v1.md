OPEN RULEBOOK SYSTEM
for Computer Roleplaying Games (CRPGs)
by Rickard Skeppström

# 1. Planeverse

Our own world is just one plane of existence. There are many other planes,
woven together into what called a “Planeverse”. A plane is just another reality in the
same space that we call “Universe”. Therefore, the planes can overlap themselves
in space. Most of these planes are materialistic, formed in one way or another by
the prime elements of nature such as fire, earth etc.
Planes are vast, cosmic creations that require astonishing amounts of energy
to create and even more to maintain, therefore only gods can form them. Most gods
have created their own planes of existence.
## 1.1. Planes of existence

NameDescription
Natural PlaneThe primary plane. Birth & death by nature is the base law on this plane.
VortexA foggy and lifeless plane that exists between the planes and it's used
primarily to connect the planes together.
Fiery PlaneThe Fiery plane is a vast sea of flames and smoke, interrupted only by gigantic
burnt rocks and coal. Only parties with extreme resistance to fire can withstand
this hell of a place.
Water PlaneThe Water plane is just a vast sea of unmeasurable depth. There are silent
regions with no waves and regions full of whirlpools and titanic waves. Not a
place for walking parties.
Terra PlaneThe Terra plane is a solid plane made completely out of stone, mud, soil and
about any mineral in existence. Even the fact that you can walk through it is
because it has been dug down by the plane’s inhabitants.
Aerial PlaneThe Aerial plane is a vast, groundless and cloudy place. There's no gravity
here and no sense of depth at all.
2. World
The Planeverse is a vast place, although not without rules, at least in the
Natural Plane. The party can move, can get hungry, buy stuff, need to rest & there’s
a day-night cycle like in real life. All this may sound too obvious & perhaps a time of
waste to even consider, but in a CRPG, a set of rules will be required to restrict
things in favor of common sense & balance.
2.1. Time
The time can be broken down into minutes, hour, day, month & year. There
are no different rules than the ones already used in our reality, so 60 minutes
makes up an hour, 24 hours makes up a day, 30 days (strict) make up a month &12 months make up a year. Time can be increased through the following ways:
•Time is increased by one (1) minute when the party moves
•Time is increased by one (1) minute when a player makes a combat action
•Time is increased by eight (8) hours when the party performs a long rest
•Time is increased by a period when party makes a rest until fully healed
•Time is increased by a period when party travels to another map
2.2. Lighting
There are various states of lighting in the world environments. Those
environments can be either interior (interior) or exterior (etc. forest). Lighting can be
modified either by environment (i.e. daylight) or equipment/magic (i.e. torch, spells).
Interior areas can provide the following lighting states:
•None – Usually encountered in interior areas, such as dungeons. Visibility is
really low, allowing up to one (1) visible square before everything gets pitch
black.
•Normal – Stronger lighting that none. An interior area can be lit for up two (2)
visible squares & perhaps more but the rest remains pitch black.
Exterior areas can provide the following lighting states:
•Day – Very strong lighting.
•Night – Strong lighting.
2.3. Movement
Moving in the world is very context-related i.e. on dungeon crawlers the
movement could be done by grid, one at a time, while on open 3D games there's
typically free movement. However, there are some simple rules:
•For every movement the party makes, there is also a movement for all
monsters, NPCs etc. A creature might prefer to not move on its turn but it
always takes a chance to do that. A non-move is also considered a move.
•Monsters, NPCs have an initial position i.e. their starting position. They can
move randomly or chasing you down i.e. monsters, but they can't movefurther from their initial position after some distance. This keeps monsters,
NPCs population in certain places. See below for more information.
•Movement is not allowed through objects considered as obstacles. These
objects includes trees, monsters, walls etc. General rule is, the party can't
move through obstacles, under normal situations.
•Movement is not allowed when the party is engaged in a fight i.e. there are
monsters in neighbor squares.
•Movement to another area is done by traveling (see Traveling). Traveling
requires some time (see Time) & food to be completed, which is distance-
based. For example, the party may travel to another neighbor area in one (1)
day & consume one (1) food ration. If the party has no food left, the traveling
can not be done.
•Monsters that are far but still in range (visible or not), they're not seeing you
yet and will make random, patrolling moves around their initial position. In
code that could mean an 80% of your draw distance.
•Monsters that are far from their initial position, they stop following you and
instead making moves that keeps them in range with their initial position.
•Monsters can take one (1) up to four (4) squares in each direction of the
party; therefore, up to 16 monsters can surround the party.
2.4. Traveling
The world is divided into smaller areas. Each area is, usually, interconnected
to a number of other areas. Traveling to an area takes time & consumes food
rations, which are context-based. Those areas can be traveled by the party in a
number of ways:
•The party can travel to a neighbor area on their own, using the roads. The
time spent is one (1) day & food consumed is one (1) ration.
•The party can travel to non-neighbor area through a traveling service. In this
case, the time spent & food consumed is context-based. One way to
estimate the time spent is to count the areas the party is traveling through.
2.5. Food
A character needs to eat before getting a rest (see Resting), otherwise he
won't be able to rest at all; therefore a well prepared party should be the first priority.
Food rations can be obtained in several ways but they can usually be found incivilized places such as taverns or traveling merchants. Food can be consumed, by
user action or automatically, in the following ways:
•Food can be consumed by resting
•Food can be consumed by traveling to another map
2.6. Resting
Characters spends their entire day fighting though monsters and difficult
challenges. Most of the times they end up wounded and tired. An easy (but
expensive) way to restore hit points is to use magic or potions. The other way is
through resting. A party has 2 options here:
•A Long Rest: The party rests for eight (8) hours or less if the party is healed,
which may or may not heal the party to full extent. The party consumes one
(1) food ration after the healing. Useful when the party needs some fast
healing, consuming the least possible food rations.
•Rest Until Fully Healed: Here the party rests until all members have full hit
points, as well as spell points (for caster professions). This might take more
time, especially the more wounded the party is. The party consumes one (1)
food ration for every 8 hours the party is rested, round up. Useful when the
party is severely wounded, but keep an eye on available food rations.
The procedure heals the hit points & restores the spell slots (for caster
professions) in a single turn. This is context-based, since this is a timed procedure.
A turn may last 5 minutes, as an example or similar timed periods. The spell slots
restored on single turn, are added to a single expertise slot at a time, starting from
the lowest expertise (that is, initiate) and advance to next expertise when the current
expertise spell slots are full! The exact hit points healed & restored spell slots for
each character, in each turn, are the following:
int amount_hp = random(1, (ToughnessMod / 2));
int amount_sp = random(1, (IntelligenceMod / 2));
2.7. Currency
The monetary system in Planeverse is as simple and straightforward as
could be; everything is traded through gold coins. The suffix for an amount of gold
coins is simply a g, for example 350g is a valid amount. However, this can lead to
some problems if the amount is big enough for expensive objects i.e. selling a
house could cost millions of gold. In this case there are two (2) possible solutions:
•
Format the gold amount with commas i.e. 3420500g becomes 3,420,500g•
Use additional suffixes based on amount i.e. 150200g becomes 150.2Kg
Specifically:
SuffixNameIn gold coinsDescription
1Kg1 Kilogold1,000g1 thousand gold coins
1Mg1 Megagold1,000,000g1 million gold coins
1Tg1 Teragold1,000,000,000g1 billion gold coins

3.1. Relation to D&D attributes
D&D provides a number of attributes like Strength, Intelligence etc. A close
interpretation of D&D attributes and ORS abilities is shown on the following table:
ORS
ability
D&D
attributePower
The amount of force that muscles can exert
against a targetStrength
Measuring physical power and carrying capacity
Intelligence
The ability to logically think & acquiring
knowledgeIntelligence
Measuring deductive reasoning, knowledge,
memory, logic and rationality
Personality
Charisma
The ability to verbally impose, persuade & cope Measuring force of personality, persuasiveness,
with conversations
leadership and successful planning
Toughness
The ability to exercise and develop the
muscular systemConstitution
Measuring endurance, stamina and good health
Technique
The ability of handling difficult or highly
sensitive tasks, by handDexterity
Measuring agility, balance, coordination and
reflexes
Quickness
The ability of moving fast & accurately for a
short timeDexterity
Measuring agility, balance, coordination and
reflexes
Perception
The ability of sensing & coherently interpreting
the environmentWisdom
Measuring self-awareness, common sense,
restraint, perception and insight
An easy way to convert D&D attribute values to ORS ability values is to simply
multiply each D&D attribute value with 1.5, round up. This is only based to the fact
that ORS allows larger ability values. For example:
D&D goblin attributes: STR (8), DEX (14), CON (10), INT (10), WIS (8), CHA (8)
ORS goblin abilities: POW (12), INT (15), PERS (12), TOU (15), TECH (21), QUI (21), PERC (12)
3.2. Ability modifiers
Static ability values by themselves are only used as a starting reference but
they've to be converted before they be used in game mechanics, providing
bonuses & penalties to a particular ability. A static ability score of 5 is not very useful
to game mechanics, however it can be easily understood by humans as it
represents steady improvement. Wherever an ability is referenced by its normal
name i.e. Intelligence, it indicates its static ability score or the ability in general.
When the special word Mod is applied as suffix i.e. IntelligenceMod, it indicates the
ability modifier of that particular ability.
To compute the ability modifier from a static ability value, one subtracts 20
points from the static ability value, then divide by 2, then round down the number to
get the ability modifier value. If instead one prefers a limited table for the first 40
static ability values, the chapter Initial computed values can be used for quick
reference. However, in a developed CRPG, the developer has to implement a
computation mechanism.3.3. Initial computed values
Static ability
for 0...23Ability modifierStatic ability
for 24...41Ability modifier
5-6-724-25+2
7-8-626-27+3
9-10-528-29+4
11-12-430-31+5
13-14-332-33+6
15-16-234-35+7
17-18-136-37+8
19-21+038-39+9
22-23+140-41+10
* static ability values can't go below 5 (see Character creation)
3.4. Generate static ability values
A character has to generate seven (7) values to be used as the starting
(static) ability values. All (static) ability values are starting at 15 points. You are given
20 ability points at the start to distribute them freely to all abilities. Remember that
you can't reduce a static ability value below 5.
4. Races
Characters are sorted into races, which greatly shapes their appearance,
code of law, spoken languages, lifespan and other. Those races are:
NameLifespanAdulthoodLanguagesAbility Bonus
Human~100 years18 yearsEnglish*Intelligence +4
Dwarf~400 years60 yearsEnglish*, DwarvishToughness +4
* English is a language that every race can speak; its not considered a skill
4.1. Alignment
Characters have a personality that drives their actions, every decision &
motive. Usually, it is directly connected to real player’s alignment i.e. the one playingthe character. Alignment can be used to greatly change the outcome of a
discussion, the course of a quest, the entire party goals and so on. In addition,
alignment is not only a party’s feature; it also applies to monsters, farmers & kings
out there which can & will have further consequences on everything the party does.
Those alignments are:
NameDescription
GoodGood characters protect the innocent, respect life and value dignity. They keep their
word and have strong respect for the law and truth.
NeutralNeutral characters are driven by their own causes and they're not get attached to
other characters. They can be either Good or Evil on occasion if that helps their
cause.
EvilEvil characters hurt and oppressing others and have no respect or compassion for
others. They strongly disrespect law and prefer lies and trickery, if that helps their
causes.
4.2. Languages
Characters speaks their own languages based primarily on their race and
secondly by choice for a reason i.e. trading, exploring or living in another place.
The languages are:
NameSpoken byDescription
English*Human, DwarfThe most common and oldest language of Natural Plane
DwarvishDwarfThe native language of the Dwarves
* English is a language that every race can speak; its not considered a skill
4.3. Naming
Most races have vastly different culture and ancestry, so it's only logical they
have their own naming conventions. One is free however to choose whatever name
he thinks about. The following table present a recommended name list:
RaceNamesHumanMaleAlphonsus, Arminel, Arthurus, Athelard, Azorius, Beroldus, Bertrand,
Christofur, Emericus, Forthwind, Jacques, Jarin, Jeronim, Jesper, Galeran,
Gerontius, Geffrey, Giffard, Gualterius, Hancock, Huggett, Humphrey,
Maynard, Pawelinus, Percevale, Rainald, Reginald, Ricaud, Robertus,
Rolph, Salemon, Sansonnet, Tamas, Searl, Warrenus, Wiscar
FemaleAdeliza, Aelesia, Alicia, Alyson, Anne, Arabella, Ariana, Ariel, Beatrice,
Belle, Brigitta, Christina, Edelina, Elianora, Elisabetha, Elsa, Gisella,
Gueanor, Hegelina, Isabella, Ivetta, Jacobina, Jaquelinne, Jeanette,Jennet, Joan, Joanna, Linette, Loreena, Magdalen, Mariana, Mariel,
Rochilda, Rosaline, Rose, Sabeline, Sara, Selova, Seraphina, Simmonete
Dwarf
MaleArathas, Baridouk, Betrac, Bhaznith, Bradal, Braddak, Dhuker, Folguk,
Gimmod, Gizzog, Gladrag, Grolgron, Herdock, Jadrath, Jaggaed,Jolmaes,
Jorreth, Kifrug, Kovrid, Krazzud, Kromir, Kromrok, Morgrud, Skognam,
Snargat, Thafrim, Thaldrim, Thastut, Thobroum, Thrazzean, Throlgrik,
Thughael, Thutreak, Umirhead, Urbak, Welgrid, Wegrus, Yurgen
FemaleAstelynn, Bezolda, Bozeline, Dakilsia, Danihilda, Daznelin, Devarra,
Doraselsia, Dossomora, Dossorra, Erighelda, Fimwalda, Grozibella,
Grundina, Herobella, Hilda, Homolsia, Jorbarika, Jossealynn, Jowathra,
Kangrelda, Kherrana, Masgribela, Muzolynn, Notihilda, Nussira, Nuvealda,
Olgebella, Sirfalsia, Thindroula, Thodwirra, Thubulda, Thuggulsia
5. Professions
Characters are also sorted into professions, which is simply their job, what
they do. Some fight their way, other are traders and some unravel the mysteries of
magic (more commonly, they’re casters). In addition, they get different amounts of
initial wealth when they start. These professions are:
NameCasterInitial
WealthDescription
KnightNo120gKnights offer their muscles and weapons for a payday. They
can be mercenaries for hire, soldiers or guards in a King's
court. Their numbers are always in need so while they're not
living a rich life, they still manage pretty well.
ClericYes60gClerics are the natural defensive casters of Planeverse.
They draw energy by praying to their deities and they can be
found in holy places such as Abbeys. They are usually poor
and don't have much in wealth.
WizardYes180gWizards are the natural offensive casters of Planeverse.
They usually found in some laboratory studying spells or old
enhanced items. Because they're dealing with expensive
jewelry all the time, they usually live a rich life.
5.1. Hit points
The hit points is a number that defines the maximum life points i.e. how much
damage you can take before getting knockout or worse. The Profession defines
primarily a base for the hit points calculation while Race may or may not provide an
additional bonus. The following table shows the starting hit points for every
profession:ProfessionBase HPHP / Level
Knight40 + (5 * ToughnessMod)+6
Cleric28 + (3 * ToughnessMod)+3
Wizard28 + (3 * ToughnessMod)+3
5.2. Spells points
Opposite to hit points, spells doesn't have points; instead a fixed number of
spells slots (i.e. times to cast a spell) are provided. The ability IntelligenceMod
defines the total number of spells a caster can use, sorted by skill expertise.
5.2.1. Expertise
The spells, like the weapons, requires some kind of experience or expertise
to be used appropriately; the main logic is:
•
•
•
•
the ability IntelligenceMod defines the total number of spells
the total number of spells are allocated per expertise level
the lower the expertise, the fewer & weakened spells a caster can use
the higher the expertise, the more & stronger spells a caster can use
The base expertise levels, which can be used for everything that requires an
expertise level i.e. weapons, are the following:
Initiate / Apprentice / Adept / Master / Grandmaster
Since the total points are divided per expertise level, a spell slot list for a
player may look like 10 / 7 / 4 / 2 / 1. This can be broken down to this:
•
•
•
•
•
10 Initiate spells
7 Apprentice spells
4 Adept spells
2 Master spells
1 Grandmaster spell
Obviously, a caster can only cast a spell of given expertise if he's trained in
the required skill (see Skills). In addition, when there are no available spells to cast
on an expertise, the caster requires some resting (see Resting) to restore his spell
slots.5.2.2. Generate spell totals
Initially, the spell slots are shared in the following allocation, provided the
character belongs to a caster profession, such as a Wizard; if the profession is not
a caster, the total number of spells will be zero (0), as well their spell allocation. So,
initially, the casters are provided the following spell allocation:
10 / 7 / 4 / 2 / 1
However, the value of IntelligenceMod (see Abilities) can be used to determine
the final spell allocation to the different expertise levels. If for example, the
Intelligence is 19, this will gives as a IntelligenceMod of 0. We then add that up to
the first expertise (Initiate) in the above allocation, which is 10 and we get the total
number of Initiate spells. To calculate the total spells of the remaining expertise
levels, multiply the current number of spells for the expertise with 70%, then round
down to get the final value of the number of spells for the next expertise. The
following steps can be used to compute this more easily:
•
•
•
•
•
•
If profession is not a caster, give him an initial 0 / 0 / 0 / 0 / 0 spell allocation
If profession is a caster, give him an initial 10 / 7 / 4 / 2 / 1 spell allocation
Compute the ability modifier of Intelligence
Apply any racial / profession bonuses to IntelligenceMod
Add the final value of IntelligenceMod to the first expertise number
Multiply remaining expertise numbers by 70% of previous, rounded down
Another example, an Intelligence of 10 computes an IntelligenceMod of -5.
Applying this bonus to Initiate starting number of 10 will give 5 and the following
sharing (after using the above calculations):
5/3/2/1/0
The above indicates that this caster can only cast 11 spells at the moment,
allocated from lowest to highest expertise. However, if he trains hard and raise his
Intelligence to 24, he'll get an IntelligenceMod of 2, which it will change his
allocation of spell slots to this:
12 / 8 / 5 / 3 / 2
If you instead prefer the spells slots for the first 40 static ability values of
Intelligence, the chapter Initial computed values can be used for quick reference.
However, in a developed CRPG, the developer has to implement a computation
mechanism:
5.2.3. Initial computed values
Static ability
for 0...23
Spell slots
Static ability
for 24...41
Spells slots5-63/2/1/0/024-2512 / 8 / 5 / 3 / 2
7-84/2/1/0/026-2713 / 9 / 6 / 4 / 2
9-105/3/2/1/028-2914 / 9 / 6 / 4 / 2
11-126/4/2/1/030-3115 / 10 / 7 / 4 / 2
13-147/4/2/1/032-3316 / 11 / 7 / 4 / 2
15-168/5/3/2/134-3517 / 11 / 7 / 4 / 2
17-189/6/4/2/136-3718 / 12 / 8 / 5 / 3
19-2110 / 7 / 4 / 2 / 138-3919 / 13 / 9 / 6 / 4
22-2311 / 7 / 4 / 2 / 140-4120 / 14 / 9 / 6 / 4
5.3. Strong / weak Abilities
Professions have two (2) Abilities that are best suited for those characters.
Those Abilities provide an additional bonus to the initial Ability values (static) when
a character is created, specifically seven (7) points. There’s also an Ability that is
unsuited for that Profession, which causes an additional penalty to the initial Ability
value for that Ability by the same amount. Keep in mind that the aforementioned
bonuses / penalties are only applied (once) on Character creation procedure. The
following table shows those abilities for each Profession:
ProfessionStrong abilitiesWeak abilities
KnightPower, ToughnessIntelligence
ClericIntelligence, PersonalityPower
WizardIntelligence, PerceptionPower
6. Character progression
An adventurer's life is full of dangers, exploration and killing, which in turn
provides the adventurer with experience. This experience can then be used to reach
milestones for a character progression, more commonly named levels in the RPG
world. Levels are the natural progression mechanism in the system. To advance in a
level, one needs to reach the required experience points for that lever.
However, the way characters gains experience vary greatly in this dynamic
world. The experience is always shared between live / active members. Dead or
paralyzed characters wont get a share of the experience gained. This system uses
a (somewhat) complex algorithm to compute the experience required for a given
level, which is presented below in the C++ programming language (but can be
converted easily to any language):
uint32_t experience_required_for_level(double level) {
double exp = 0;}
for(double x = 1; x<level; x++) {
exp += std::floor(x + (300 + (level * 100)) * std::pow(2, (x / 10)));
}
exp = (std::round(std::floor(exp) / 10) * 10);
return (uint32_t)exp;
The above mechanism produces reasonable, yet increasingly difficult to
reach, levels. At the 1st level you will advance pretty quickly by killing some
monsters, but at the 2nd level the advancement will come harder and so on for every
level. If instead prefer a limited table for the first 20 levels & experience required, the
chapter Initial computed levels & experience can be used for quick reference.
However, in a developed CRPG, the developer has to implement a computation
mechanism.
6.1. Initial computed levels & experience
Level 1...10Experience
RequiredLevel 11...20Experience
Required
101120960
25401225680
313401331070
424201437210
538201544160
655801651990
777201760800
8102801870670
9133101981710
10168502094020
6.2. Advancing levels by quests
Level advancement can be done in various ways and not just by killing
monsters. One of such ways is by completing a quest. The XP given may be a
fixed value but this poses a balancing problem since characters can be either very
weak or very strong for that fixed value & there’s also the difficulty of computing a
balanced experience value. The system uses a balanced approach, which is the
following:
•
•
•
•
take the average level of all live / active characters
take the experience needed for (average level + 1)
multiply by 0.5 that experience
share the final experience amount to all live / active characters.Thus, the experience shared will always be balanced. In this case, if only a
character is alive / active then he will advance in level by completing two (2)
quests. Otherwise, if all characters are alive / active, the party will need to
complete eight (8) quests to advance in level, just by completing quests without
counting the intermediate killing of monsters or anything else providing XP.
7. Skills
Besides the character's profession, you will need to practice some skills to
improve yourself and your party's survival chances. Those skills are sorted into skill
groups, which are Weapon, Armor, Magic and Misc (miscellaneous). A character
can choose as many skills as he wants, there's no restriction, except the time
invested & the amount of money the party will need in order to progress on these
skills. That is, advancing into a skill requires serious time & money and there's a
standard procedure.
This procedure starts with you buying the right to practice a skill for a modest
price. At this time you're basically an Initiate, which is not an official recognition of
your skill level and therefore you won't be referred as such; it just means you have
the right to start your skill progress and work under the wandering Masters, which
you need to seek and find them, on your own.
This procedure is called qualification and must be done for every expertise
you wish to reach in the skill. Each Master have some requirements before promote
you to the next level of expertise. These are:
•
•
•
•
provide a fixed amount of gold
gain the required skill level (i.e. Long Blade of 5 skill points)
gain the required base ability score (i.e. Power of 20 ability score)
train a specific amount of time, along with Master
You can't expect to advance to a Grandmaster status at 1st level of your skill
just because you're rich, nor without months of intense training. Provided you have
the gold, each Master requires to work with him for a fixed period of time; this is
done automatically, the Master is just a member of your party and when the party
walks, he’s working with you and evaluates your progress. In the end of training, the
character is trained to the next expertise level & the Master then leaves the party.
The following table lists the expertise levels, with all the advancement requirements:
NameDescription
*InitiateYou just bought a piece of paper, allowing you to practice a skill. Yawn.
Initial requirement: Base ability 20, 100g cost, profession eligibiity
What to do next: Seek out a trainer to start your training as Apprentice.
ApprenticeAn Apprentice is learning a trade from a skilled master, having agreed to work for
a fixed period at low wages.
Initial requirement: Skill level 5, 500g cost, 1 week of training
What to do next: Seek out a trainer to start your training as an Adept.AdeptAn Adept is a skilled apprentice who has successfully completed an official
apprenticeship qualification. To further continue, the Adept needs to find a
Grandmaster of his skill to start his Master qualification.
Initial requirement: Base ability 30, Skill level 10, 2000g cost, 2 weeks training
What to do next: Seek out a trainer to start your training as a Master.
MasterA Master is a seasoned Adept that shown great proficiency in his skill.
He is now able to start his own business to further advance his skill to
Grandmaster status.
Initial requirement: Skill level 15, 5000g cost, 1 month of training
What to do next: Seek out Guild headquarters to get assigned a quest.
GrandmasterA Grandmaster is a veteran master that achieved the highest level in his
skillmanship.
Initial requirement: Base ability 40, Skill level 20, 10000g cost, assigned quest
What to do next: Nothing, you’ve reached the maximum potential of your skill
* An initiate in a skill is not referenced as such
7.1. Relation to D&D skills
D&D provides a number of skills, associated with an attribute. The D&D
attributes relates to skills in the form of applied restrictions, that is, a character can’t
acquire / use a skill if he doesn’t have the necessary D&D attribute score for the
associated D&D attribute. The exact same mechanism applies to ORS as well.
Furthermore, some events require some skill check:
•In D&D, challenges provide a Difficulty Class (DC) to be checked against a
(related) skill score, which describes the difficulty of the challenge.
•In ORS, challenges require a specific Expertise to be checked against a
(related) skill expertise, which describes the difficulty of the challenge.
In both cases, if the check passes, the challenge is overcome. The character with
the highest expertise with said skill is always used. Those skills belong to the Misc
group of skills i.e. Lore or Dwarvish (language) are such skills. A close interpretation
of D&D DC and ORS expertise checks is shown on the following table:
ORS
expertiseD&D
Difficulty Class (DC)DC to ORS
expertise
range (1-20)
InitiateVery Easy (DC 5)1-4
ApprenticeEasy (DC 10)5-8
AdeptMedium (DC 15)9-12
MasterHard (DC 20)13-16
GrandmasterVery Hard (25)17-20+The DC to ORS expertise range (1-20) column is used to cap D&D DC ranges to an
ORS range, which then maps to appropriate ORS expertise. ORS skill scores are
not used for checks; only the mapped ORS expertise.
Some examples between D&D and ORS challenge checks:
D&D DC (12) on a related X skill → ORS Adept expertise on a related X skill
D&D DC (19) on a related X skill → ORS Grandmaster expertise on related X skill
An example of an ORS challenge check with a party of three (3) characters:
ORS challenge requires a check on Lore skill (Expertise required: Adept)
•
•
•
•
Merlin (Have Lore Expertise at Master level)
Amon (Have Lore Expertise at Grandmaster Level; Paralyzed)
Selina (Have no Lore skill)
Percival (Have Lore Expertise at Initiate level)
The ORS chooses the highest expertise among all alive (i.e. no dead) & active (i.e.
no paralyzed, maddened etc.). Thus, the higher expertise of the party is that of
Merlin (Master). We check his expertise against the expertise the challenge
requires, that is, Master vs Adept. Since Master >= Adept, the challenge check is
passed and the party overcome the challenge.
7.2. Mapping ORS skills to D&D skills
ORS provides fewer skills than D&D does but they do provide more context in
general. A rough mapping of ORS skills to D&D skills follows:
ORS skillD&D equivalent skill
Fitness (Power)Athletics (Strength)
Dwarvish (Intelligence)-
Lore (Intelligence)Arcana, History, Religion (Intelligence)
Persuasion (Personality)Deception, Persuasion, Intimidation (Charisma)
Taming (Toughness)Animal Handling (Wisdom)
Quickhand (Technique)Sleight of Hand (Dexterity)
Stealth (Quickness)Stealth (Dexterity)
Awareness (Perception)Perception, Survival (Wisdom)
7.3. Benefits and restrictions
A high expertise should provide some benefits in opposite to lower expertise.
This is handled differently for each skills group (Weapons, Magic etc.). The followingtable shows the benefits / restrictions for each expertise for each skill group:
Skill group
Weapon
Armor
Magic
Misc
Benefits / Restrictions
ExpertiseDescription
InitiateCan use weapons of +0 only (no modifier at all)
ApprenticeCan use weapons of +1 as well
AdeptCan use weapons of +2 as well
MasterCan use weapons of +3 as well
GrandmasterCan use weapons of +4 as well
InitiateCan use armors of +0 only (no modifier at all)
ApprenticeCan use armors of +1 as well
AdeptCan use armors of +2 as well
MasterCan use armors of +3 as well
GrandmasterCan use armors of +4 as well
InitiateCan use Initiate spell scrolls only
Can use Initiate spell books only
ApprenticeCan use Apprentice spell scrolls as well
Can use Apprentice spell books as well
AdeptCan use Adept spell scrolls as well
Can use Adept spell books as well
MasterCan use Master spell scrolls as well
Can use Master spell books as well
GrandmasterCan use Grandmaster spell scrolls as well
Can use Grandmaster spell books as well
InitiateInitiate expertise skill check
ApprenticeApprentice expertise skill check
AdeptAdept expertise skill check
MasterMaster expertise skill check
GrandmasterGrandmaster expertise skill check
7.4. List
Everything you can wear, use or fight with is considered a skill on its own and
making the best out of it will determine your fate. The following table shows the base
skills, the expertise level that each profession may attain to and all the fine details
that fully characterizes a skill.
Skills that have a - rather an expertise level are not allowed for this
Profession. Some skills require another skill to be learned first. For example
Chained armor can't be used unless Leather armor is learned to Adept expertise.
This requirement is only used when you are trying to learn a skill. Finally, someskills, especially of the Misc group, may have different rules for learning. For
example, languages are either learned or not; only one trainer is required to
advance you to the Grandmaster status. The list of skills follows:
Name
Profe Initial
Gro Adv Utilized by
ssion* Requirement up ance
*** ****
K C W **
N L
Description
I
Short bladeM G G Technique 20WeADagger, Short swordSmall blades;
physical
Long bladeG -WeAFalchion, Long sword,
Scimitar, GreatswordLong blades;
physical
BowG M - Technique 20WeABow, CrossbowRanged weapons;
physical
BludgeonG M - Power 20WeAClub, Mace, Morning
star, Flail, HammerThick poles with
heavy ends;
physical
Short axeG M - Technique 20WeABroad axe, Hand axeSmall axes;
physical
Long axeG -- Power 20
Short axeWeABattle axe, War axeLong axes;
physical
PolebladeG -- Power 20
PoleWeABardiche, Halberd,
Spear, ScytheLong sticks with
edged ends;
physical
PoleM G G Technique 20WeAQuarterstaffLong sticks;
physical, magical
ShieldG M - Power 20ArAShieldProtective plate;
protection
Leather armor G M M Technique 20ArALeather armorProtective leather;
protection
Chained armor G -- Power 20
Leather armorArAChain mailProtective chains;
protection
Scaled armorG -- Technique 20
Leather armorArAScale mail,
Ring mailProtective scales;
protection
Plated armorG -- Power 20
Chained armorArAPlate mailProtective plates;
protection
Fire magic- M G Intelligence 20MaAFire based spellsFire element
spells; magical
Air magic- M G Intelligence 20MaAAir based spellsAir element
spells; magical
Water magic- M G Intelligence 20MaAWater based spellsWater element
spells; magical
Earth magic- M G Intelligence 20MaAEarth based spellsEarth element
spells; magical
Energy magic-G G Intelligence 20MaAEnergy based spellsEnergy element
spells; magical
Mental magic- G M Intelligence 20MaAMental based spellsMental element
spells; magical
Soul magic- G M Intelligence 20MaASoul based spellsSoul element
spells; magical
FitnessG M M Power 20MiAClimbing, Jumping,Environmental
- Power 20
Short bladeSwimming, Pushing
challenges
DwarvishG G G Intelligence 20MiBPlaques, Books, People Know the language
LoreM G G Intelligence 20MiAGlyphs, Plaques, Magic Knowledge on
/ Ancient objects
ancient stuff
PersuasionG G G Personality 20MiAPersuade, Intimidate,
Influence others
Manipulate the
will of others
TamingG M M Toughness 20MiAWild monsters, Avoid
fights, Acquire animal
companions
Tame, drive off or
calm down wild
beasts
QuickhandM G G Technique 20MiAQuick hand reflexes,
Pickpocketing
Actions involving
quick hand actions
StealthG G G Quickness 20MiAConceal from enemies,
guards, go unnoticed
Move unnoticed in
an environment
AwarenessM G G Perception 20MiASounds, Environmental
signs, Observeness
Generic sense of
the environment
* Maximum expertise (on Profession) is defined as: M = Master, G = Grandmaster
If Profession expertise gives - it means this skill is not allowed for this Profession
** If a skill requires another skill, that skill has to be taught on Adept level first
*** Group is sorted into: We = Weapon, Ar = Armor, Ma = Magic and Mi = Misc
**** The procedure followed to advance the skill to Grandmaster status, they are:
A = Advance from Initiate to Grandmaster; Multiple trainers
B = Advance from Initiate to Grandmaster; One trainer
7.5. Character progression in skills
Skills need to be developed by frequent use for the character to improve their
use & efficiency. Characters gets experience in skills when they use them (mostly),
the same way their character level progresses. A skill consists of:
•
•
•
the level
the experience
the expertise
Initially, an acquired skill is set to level 1, experience at 0 and expertise of Initiate.
Each time a character uses an acquired skill through an item or action, the skill
experience is advanced by one (1) experience point. Each skill belongs to a specific
group, indicating their use method to gain experience. Those skill groups are:
•Weapon – Involves skills such as Short Blade, Long Blade, Pole etc.
Experience comes by using weapons in a battle.
•Armor – Involves skills such as Shield, Chained Armor, Plated Armor etc.
Experience comes by getting hit / miss by a monster while wearing armor.
•Magic – Involves skills such as Fire Magic, Water Magic etc.
Experience comes by using magic in a battle.
NOTE: Magic can used through staffs, wands, scrolls etc.•
Misc– Involves skills such as Dwarvish (language), Lore etc..
Experience is here is very context-based. A convenient method of gaining
experience on such skills is by utilizing items such as Books or similar
methods. For example, reading a Book on Lore should improve one’s skill
experience, provided he’s initiated on that skill.
If a skill reaches a specific level, the character might be eligible to advance
his expertise on this particular skill. The chapter Skills shows the skill requirements
for a character to advance his expertise. This system uses a (somewhat) complex
algorithm to compute the experience required for a given skill level, which is
presented below in the C++ programming language (but can be converted easily to
any language):
uint32_t experience_required_for_skill_level(double level) {
double exp = 0;
for(double x=1;x<level;x++) {
exp += std::floor(x + (150 + (level * 5)) * std::pow(2, (x / 10)));
}
exp = (std::round(std::floor(exp) / 10) * 10);
return (uint32_t)exp;
}
The above mechanism produces reasonable, yet increasingly difficult to
reach, skill levels. At the 1st level you advance somewhat quickly by using the skill,
but at the 2nd level the advancement will come harder and so on for every level. If
instead prefer the full table for the 20 levels & experience required, the chapter
Initial computed skill levels & experience can be used for quick reference.
However, in a developed CRPG, the developer has to implement a computation
mechanism.
7.6. Initial computed skill levels & experience
Skill Level
1...10Experience
RequiredSkill Level
11...20Experience
Required
10113110
2170123650
3370134240
4590144890
5840155610
61130166390
71440177260
81800188200
92190199250
10263020103808. Combat
Planeverse is a very dangerous place & hostile encounters can show in
literally every step. A battle occurs when hostile characters (humans, monsters,
things etc.) gets too close to the party. The battle is progressing through mutual
actions, based on specific statistical computation (see Combat order). The battle
ends when either party or the hostile characters are dead.
8.1. Combat order
When you are next to monsters, a combat order must be computed i.e. in
which order the combatants are taking actions. The ability used to determine the
combat order is Quickness, which used for both party and monsters. The value of
QuicknessMod is always used. The procedure of determining the combat order is
quite straightforward:
•First verify that you're facing monsters in close encounter of some direction
i.e. front, back, left or right. regardless of your orientation.
•Compute the QuicknessMod for all, both party and monsters.
•Sort combatants by their QuicknessMod, in descending order.
The combatants are acting based on combat order. They can use both items
on their hands in one turn i.e. if you have 2 swords in your hands (single-handed),
you can use both before ending your turn or you can just skip one or both hands to
next combatant in order (which can be another party member or an enemy).
When a party member uses one of his hands, this hand can't be used again
in current turn. In addition, item equipping is limited while you're engaged in a fight
(see Equipping items in combat). When all combatants ends their turn, a
Movement (see Movement) is initiated and combat order repeats itself.
8.2. Equipping items in combat
When the party is engaged in a combat, their number of actions are limited.
One of such actions is equipping items. A character can only equip an item under
the following conditions:
•
•
It’s his turn to act
One of his hand slot has not been used
For example, if a character has a Longsword on his right hand and has used
it to attack, he can not swap it with some other item while he is pondering the use of
his (unused) left hand. However, an unused hand can be swapped with some otheritem such as weapon, a healing potion or a spell scroll. The list is an example, any
item can be swapped as long the basic rules of equipping apply i.e. a 2-handed
weapon can not be equipped even if the other hand has already been used.
8.3. Damage
The damage is a measurement of how powerful is an offensive item, such a
weapon or a spell. It is usually not fixed since damage can be affected by a number
of factors, including simple luck. Another important point is that damage is hardly
just a matter of muscle; there is a number of damage types and only some of them
involve raw power. For each kind of damage a specific procedure is followed to
compute the final damage:
8.3.1. Damage by Bare hands
If there's no weapon in hand i.e. the attack is made with bare hands (melee
attack), then only PowerMod score is considered as a damage. The target’s
Protection is considered as defence. To ease the calculations below, we assume a
target with no protection at all (Protection = 0). For example a Wizard with Power
score of 14 decides to attacks with his bare fists. To compute the final damage:
PowerMod = compute_ability_bonus( 14 ) // PowerMod is -3 (Power 14)
finaldamage = PowerMod
finaldamage -= target_protection
if (finaldamage < 0) { finaldamage = 0 }
Thus, the resulted damage its 0. That is, the target successfully absorbed the
attacker’s damage. Another example, a Knight with Power score of 24 (+2) attacks.
To compute that final damage:
PowerMod = compute_ability_bonus( 24 ) // PowerMod is +2 (Power 24)
finaldamage = PowerMod
finaldamage -= target_protection
if (finaldamage < 0) { finaldamage = 0 }
That is, Knight deals a damage of 2. Obviously, only very strong characters (or very
weakly protected targets) would be able to cause decent damage with their fists or a
character provided with strong enhancements.
8.3.2. Damage by Melee weapons
Melee weapons are any handheld weapons that can be used in hand-to-hand
battle. Typical melee weapons include swords and flails. When attacking with amelee weapon, the Power ability is primarily used, then the item’s offensive
capability is considered. Melee weapons usually provide their damage in a from / to
range. The target’s Protection is considered as defense. To ease the calculations
below, we assume a target with no protection at all (Protection = 0). For example a
Knight with Power score of 24 (+2) decides to attacks with his Long sword (melee
weapon, belonging to Long blade skill). To compute the final damage:
PowerMod = compute_ability_bonus( 24 ) // PowerMod is +2 (Power 24)
finaldamage = PowerMod
finaldamage += random(weapon_damage_from, weapon_damage_to)
finaldamage -= target_protection
if (finaldamage < 0) { finaldamage = 0 }
// if item is enchanted and cause elemental damage(s):
loop (item_enchantments) {
if (enchantment_cause_elemental_damage) {
damage = random(elem_dmg_from, elem_dmg_to)
if (target_vulnerable_to_elemental_skill) { damage *= 2 }
if (target_resistant_to_elemental_skill) { damage /= 2 }
finaldamage += damage
}
}
if (target_vulnerable_to_item_skill) { finaldamage *= 2 }
if (target_resistant_to_item_skill) { finaldamage /= 2 }
if (item_has_doubledamage_enchant_vs_monster_type) { finaldamage *= 2 }
Things to consider:
•
•
•
•
A melee weapon can be enchanted (see Named enchantments), which may
cause elemental damage(s).
If the target is vulnerable to the melee weapon’s skill, that is Long Blade, it
will receive double damage.
The damage will be halved if the target is resistant to weapon’s skill.
If the melee weapon is enchanted by double damage vs type, the target will
receive double damage.
8.3.3. Damage by Ranged weapons
Ranged weapons are any weapons capable of engaging targets at a
distance. Typical ranged weapons include bows and crossbows. When attacking
with a ranged weapon, the Technique ability is primarily used, then the item’s
offensive capability is considered. Ranged weapons usually provide their damage in
a from / to range. The target’s Protection is considered as defense. To ease the
calculations below, we assume a target with no protection at all (Protection = 0).
For example a Knight with Technique score of 24 (+2) decides to attacks with his
Bow (ranged weapon, belonging to Bow skill). To compute the final damage:
TechMod = compute_ability_bonus( 24 ) // TechMod is +2 (Technique 24)
finaldamage = TechMod
finaldamage += random(weapon_damage_from, weapon_damage_to)
finaldamage -= target_protectionif (finaldamage < 0) { finaldamage = 0 }
// if item is enchanted and cause elemental damage(s):
loop (item_enchantments) {
if (enchantment_cause_elemental_damage) {
damage = random(elem_dmg_from, elem_dmg_to)
if (target_vulnerable_to_elemental_skill) { damage *= 2 }
if (target_resistant_to_elemental_skill) { damage /= 2 }
finaldamage += damage
}
}
if (target_vulnerable_to_item_skill) { finaldamage *= 2 }
if (target_resistant_to_item_skill) { finaldamage /= 2 }
if (item_has_doubledamage_enchant_vs_monster_type) { finaldamage *= 2 }
Things to consider:
•
•
•
•
A ranged weapon can be enchanted (see Named enchantments), which
may cause elemental damage(s).
If the target is vulnerable to the ranged weapon’s skill, that is Bow, it will
receive double damage.
The damage will be halved if the target is resistant to weapon’s skill.
If the ranged weapon is enchanted by double damage vs type, the target
will receive double damage.
8.3.4. Damage by Magic
Magic damage can come from any item capable of casting offensive spells.
Typical magical items include staffs, wands and scrolls. When attacking with a
magical item, the Skill level of magic spell is primarily used. However, there are
cases where the caster isn’t initiated in the magic skill the spell belongs to. For
example, a Knight may cast a fire-based spell by using a wand, without actually be
initiated in Fire magic, which would be impossible for a Knight profession. Initially,
the non-caster professions (such as Knight) have a skill level of 0 when they cast a
spell. However, internally they’re provided by skill level of 1 to be able to cast, albeit
with the lowest effect. The same happens when the profession is a caster but not
initiated in the magic skill the spell belongs to. Magical items provide their damage
in a from / to range. However, this damage is further modified by the caster’s skill
level in the magic skill the spell belongs to. The target’s Resistance to the spell’s
skill is considered as defense. However, this is computed differently if the target is a
monster or the party. Magical damage is also capped to the skill’s expertise (i.e.
Initiate, Apprentice…), which results in a max damage. Finally, some spells may
cause a non-elemental damage as well. The target’s Protection can be used as
defense in this case. To ease the calculations below, we assume a target with no
protection at all (Resistance = 0). For example a Wizard with Fire magic skill level
of 1 decides to attacks with a Firebolt spell (a fire-based spell, belonging to Fire
magic skill). To compute the final damage:
expertise = 0
// 0 = Initiate, 1 = Apprentice...
if (not_a_caster) { skill_level = 1 } // non-casters are always level 1if (not_initiated) { skill_level = 1 } // casters missing the magic skill
starting_skill_level = (expertise = * 5) // used to cap the magic damage
if (skill_level > starting_skill_level + 5) {
skill_level = starting_skill_level + 5
}
finaldamage = 0
loop (skill_level times) {
finaldamage += random(spell_damage_from, spell_damage_to)
}
// target is a monster
if (target_vulnerable_to_spell_skill) { finaldamage *= 2 }
if (target_resistant_to_spell_skill) { finaldamage /= 2 }
// target is a party's character
finaldamage -= target_resistance
if (damage < 0) { damage = 0 }
if (spell_causes_nonelemental_damage) {
damage = 0
loop (skill_level times) {
damage += random(spell_nonelem_dmg_from, spell_nonelem_dmg_to)
}
damage -= target_protection
if (damage < 0) { damage = 0 }
finaldamage += damage
}
Things to consider:
•
•
•
If the target is vulnerable to the ranged weapon’s skill, for example,
Fire magic, it will receive double damage.
If the target is resistance to weapon’s skill, for example Long Blade, it will
receive half damage.
Magic damage can also be non-elemental. In this case, Protection will be
used as a defense.
8.3.5. Damage by Action
While party characters are usually act through their equipped items such as
swords or staffs, monsters act through actions. A monster may have one or more
actions to use on his turn against the party. Their effects are various and related to
the monster in question.
For example, a Goblin may possess an action named Broad Axe (dealing
physical damage) while a Dragon may possess an action named Fire Breath
(dealing elemental damage). Some actions may look like they’re dealing with an
item (ex. Broad Axe) but they’re not related to ORS items at or with an action with
the same name of diffferent monsters.
For example, a Dragon may possess an action named Bite that deals X
physical damage. However, a Wolf may also possess an action named Bite that
deals Y damage. Just because they have the same name, doesn’t mean they’re
dealing the same damage. Each action’s properties are exclusive to its monster.Actions can deal physical damage (against a character’s Protection) or
elemental damage (against a character’s specific Resistance) or cause a condition.
The current properties of an action follows (see Monster List for monster actions):
To compute the final damage of an action:
finaldamage = 0
variant = 0
if (action_cause_physical_damage) {
dmg_from = floor(action_physical_dmg_from)
dmg_to = floor(action_physical_dmg_to)
// filter by monster’s variant
float perc = (1.0f + (float)variant * 0.15f);
dmg_from = round(action_physical_dmg_from * perc)
dmg_to = round(action_physical_dmg_to * perc)
// final damage
finaldamage += random(dmg_from, dmg_to)
finaldamage -= target_protection
}
if (action_cause_elemental_damage) {
dmg_from = floor(action_elemental_dmg_from)
dmg_to = floor(action_elemental_dmg_to)
// filter by monster’s variant
float perc = (1.0f + (float)variant * 0.15f);
dmg_from = round(action_physical_dmg_from * perc)
dmg_to = round(action_physical_dmg_to * perc)
// final damage
finaldamage += random(dmg_from, dmg_to)
finaldamage -= target_resistance
}
if (finaldamage < 0) { finaldamage = 0 }
Monster variants
There are some monsters that have improved variants from the original monster,
like Goblin → Goblin Warrior etc. These improved variants shows an improved
damage on the same actions (when the action is offensive, like the action Broad
Axe of Goblin). Not only these stronger variants have increased level and hit points,
but they hit harder with the same actions.
The calculation is based on the original action, provided by the original
monster (first). On the code above, variant = 0 really means the original monster;
replace with variant = 1 (stronger than original), variant = 2 (stronger than variant =
1) and so on. If a monster doesn’t have variants, just leave it as variant = 0.
9. ConditionsA condition (mostly negative) is caused usually by a spell, environment or
character choices. Its intention is to inflict direct or indirect damage to a character's
statistics for as long the condition lasts or until its cured. The base conditions are:
NameDescription
DeadA dead character's hit points has reached 0 or less and can't take actions
(immobilized) until he's raised back to life. Rest of conditions are removed.
CAUSE: hit points reduced to 0 or less.
CURE: spells and temple visits.
PoisonedA poisoned character has reduced Power, Personality, Toughness, Technique,
Quickness, Perception by 25% and increased Earth resistance by 100%. *Each
action loses 2% of maximum hp. Resting while poisoned leads to certain death.
CAUSE: monster actions, traps, potions.
CURE: spells, potions and temple visits.
FlamedA flamed character has reduced Personality, Technique and Perception by 50%,
increased Quickness by 50% and increased Fire resistance by 100%. *Each
action loses 5% of maximum hp.
CAUSE: monster actions, traps.
CURE: spells, potions and temple visits.
ParalyzedA paralyzed character can't take actions (immobilized).
CAUSE: monster actions, traps.
CURE: spells, potions and temple visits.
FrightenedA frightened character has reduced Personality, Quickness, Perception and
Mental resistance by 50%.
CAUSE: monster actions, spells, events.
CURE: spells, potions and temple visits.
MaddenedA mad character has reduced Personality by 100%, increased Power, Quickness
by 50% and increased Mental resistance by 100%. He also randomly attacks
party members (*per-turn), causing a damage of 5% of his maximum hp.
CAUSE: monster actions, spells.
CURE: spells, potions and temple visits.
ExhaustedAn exhausted character has reduced Power, Technique, Perception by 50% and
reduced experience gained by 50%.
CAUSE: party has not rested for a day.
CURE: rest, spells, potions and temple visits.
CursedA cursed character can't restore his HP/SP (restless) while resting.
CAUSE: monster actions, spells.
CURE: spells, potions and temple visits.
* Actions are counted in per-turn basis. Such actions are party movement and
combat turns. In addition, there’s a 50% chance to cause those effects (per-turn).
NOTE: if the entire party becomes one of:
Dead, Paralyzed, Maddened
the game ends.
9.1. Chance to inflict conditions
Computing the chance for inflicting a condition is straightforward and is used forboth party and monsters:
condition_chance = floor(chance + (attacker_level / 4))
For example, if a character casts a spell that have 10% chance to inflict the Flamed
condition, he will instead have 16% chance if he is on level 25.
9.2. Reduce the condition chance by Ability
Some conditions provide a way to reduce the chance to get inflicted by using an
ability such as Power for example. In this case, the condition chance, set by both
condition and attacker’s level, is further subtracted by the provided AbilityMod,
multiplied by 2:
condition_chance -= (AbilityMod * 2)
For example, a character have a Power of 25 (+2) and got hit by a condition-based
attack, with a chance of 40% of causing the condition, the ability to reduce that
chance is Power and the attacker level is 25. Based on attacker’s level, the chance
rises to 40 + (25 / 4) = 46%. However, the PowerMod of defender is 2, which
updates that final chance to 46 – (2*2) = 42%
9.3. Inflict conditions by items
Some enhanced weapons can cause conditions i.e. a special long sword may
be infused with poison effect to cause Poisoned condition when it hits its target. In
addition, the weapon must deal a damage before causing a condition as well.
9.4. Inflict conditions by spells
Some spells are causing conditions i.e. a the Flamed condition. The formula
takes into consideration the caster's level only, therefore the higher the caster's
level, the more his chance to cause conditions with his spells. Some spells have
higher initial condition chances which leads to high chance if the caster is high
leveled.
NOTE: if a spell causes damage as well, then a condition can only be caused if the
spell actually caused some damage. If an offensive spell misses, there is no chance
for a condition effect to be used. This is not a requirement for non-offensive spells.9.5. Inflict conditions by actions
The formula used for spells is also used in actions to cause conditions. The
only difference is that an action must deal some kind of damage for the condition to
apply. If an action is supposed to deal some damage but it missed, either by target's
protection or resistances, even a successful condition check can't be applied. For
example, a giant rat's Bite action is supposed to cause the Poisoned condition and
is supposed to deal damage. However, it won't be able to cause anything if it
misses.
9.6. Resistances
There are many types of damage types out there: physical, magical,
elemental and more. Furthermore, there are conditions that can get inflicted by
absence of some resistance. A character may be strong enough to withstand raw
power but can die in agony in few hours by getting Poisoned through a spider bite.
This kind of damaging, called elemental damage, requires more planning
since the typical Protection of a character (usually provided by armor, boots etc.)
wont help much against since they’re only protecting against physical damage.
Fortunately, there is a way to reduce the effects of such damage types; by improving
the other kind of character protection; the resistances. They’re specifically:
ResistanceDescription
FireProtects against the element of fire i.e. dragon breaths, spells like Firejolt etc.
AirProtects against the element of air such as cold, lightnings, thunders etc.
WaterProtects against water and ice related attacks.
EarthProtects against earth based attacks such as poison, stone and acid.
EnergyProtects against pure non-elemental magical energy
MentalProtects against attacks that cause mental effects such as confusion, insanity etc.
SoulProtects against attacks that cause aging, divine spells etc.
9.7. Relation to D&D resistances
D&D provides a number of damage types such a Fire, Cold etc. A close
interpretation of D&D damage types and ORS resistance types is shown on the
following table:
ORS
resistance typeD&D
damage type
FireFireAirCold
Thunder
WaterCold
EarthPoison
Acid
EnergyForce
Lightning
MentalPsychic
SoulRadiant
Necrotic
ProtectionSlashing
Piercing
Bludgeoning
10. Monsters
Monsters are the natural inhabitants of the wilderness. Some of them are
intelligent, other are not but all of the them have a purpose and their location is
never random. Some of them guard a fortress, others are hired for protecting some
place, others are magically constructed by some mad wizard, others may came from
another plane etc. Every monster has a specific set of attacks. Those attacks are
defined by weapons, spells & actions.
10.1. D&D challenge rating to monster level
ORS system provides levels for monsters. However, D&D provides a
Challenge Rating (CR) for its monsters, which is, as the name suggests, the
difficulty to kill a monster. The maximum CR for D&D is 30, while the level cap in
ORS system is 100. An easy way to convert a D&D monster’s CR to ORS monster
level is to multiply the CR with 3.3, round up.
monster_level = std::ceil(CR * 3.3)
Some examples:
D&D Goblin (CR: ¼) → (¼) * 3.3 = Level 1
D&D Troll (CR: 5) → (5 * 3.3) = Level 17
10.2. Compute Hit Points for monster
To compute the hit points for a monster, two (2) need to be known, its level &its toughness. First, multiply its level by 5 and add to initial hit points. Then, perform
a somewhat complex formula add to total hit points:
hp = (monster_level * 5)
hp += ceil(0.4f + (floor(monster_level * (Toughness * 0.4f)) * 0.125f));
Some examples:
Goblin (Level 1, Toughness 15) → 7 HP
Goblin (Level 5, Toughness 15) → 30 HP
10.3. List
Notice that monsters doesn’t have skills and, obviously, skill levels. As a
result, they don't have an expertise as well. In any case an action requires a skill
level or expertise i.e. spells, the monster's level is used as a skill level and the
spell's base expertise is used instead. Monsters belong to a type, have a Level
(which defines its HP), a fixed Protection (which is defined by either a natural armor
or by equipped items), a Toughness (which adds to its HP), a Quickness (which
defines its initiative in battle), a number of one-liner Actions (which can use in
combat) and, optionally, a number of Resistances & Vulnerabilities (which can
alter the damage they receive).
Actions that cause a condition provide all the necessary information (the condition,
the chance of causing it and the ability to reduce that chance by the defender). Keep
in mind that chance is further modified by attacker’s level (see Chance to inflict
conditions) and by defender’s ability, related to this condition (see Reduce the
condition chance by Ability). Actions are defined by a number of properties:
•Target
This can be either 1 (one character) or N (all characters)
•Reach
Either S (short reach; only when on front-rank) or L (long reach; on all ranks)
•Damage
Can be either physical (Ph) or elemental (eX), where X can be one of the
F/A/W/E/N/M/S, each one for an element, like F = Fire. Example: Ph:1-2
NOTE: For the increased damage, dealt by improved monster variants (i.e.
Goblin Warrior), see Damage by Action.
•Condition
Condition can be defined by providing the first 2 characters, like De = Dead,
Po = Poisoned and so on. There’s also the chance to cause the condition
(ex: 40%), as well as the ability used to reduce that chance.The base monsters are:
NameTypeLV HP Pro Tou Qui Actions
+ Res*
- Vul*
Cube, OozeOoze7463307Jelly Slap (1,S,eE:3-18)DoppelgangerMagical10 6182129Slap (1,S,Ph:5-10)-
GoblinHumanoid 1761523Broad Axe (1,S,Ph:3-8)-
Goblin, WarriorHumanoid 21261523Broad Axe (1,S,Ph:3-9)
Bow (1,L,Ph:3-9)-
Goblin ChiefHumanoid 53081523Falchion (1,S,Ph:4-10)
Bow (1,L,Ph:4-10)-
SnailAnimal173208Lick (1,S,Ph:1-2, eE:1-4)+Earth
Snail FireAnimal3193208Lick (1,S,Ph:1-3, Ef:1-4)
Erupting Flame (1,L, eF:2-12)-Water
+Fire
Snake
ConstrictorAnimal1751823Bite (1,S,Ph:2-4)
Grapple (1,S,Ph:2-5,Co:Pa,40%,Pow)-
* Each resistance & vulnerability refers to a skill
10.4. Experience
The monster's experience to give is computed by weighting all of its properties in a
predefined way. Starting with its Level, we use the following simple formula:
XP = (Level * 25)
That is, a monster of Level 14 will give an experience of 350, at this point.
Next, we consider its Protection and Quickness with the following formula:
XP += (Protection * 2)
XP += (Quickness * 2)
As well, a monster with Protection of 10 will give 20 experience.
Finally, a monster with Quickness of 8 will give 15 experience.
Next, we consider its Number of actions with the following formula:
XP += (number_of_actions * 25)
That is, a monster with Number of actions of 2 will give 50 additional experience.Finally, we consider its Resistances with the following formula:
XP += (number_of_resistances * 10)
That is, a monster with resistance to Bludgeon and Earth Magic will provide 20
additional experience.
11. Items
Items are very versatile and can be used differently by profession or not at all,
for example a spell book item can't be used by non-casters such as Knights and a
regular Longsword can't be used by a caster. However, all items have common
elements such as name, body part to be worn and value.
In addition, most items have improved versions which are more efficient, as
well costing more and are rarer to find; those items have a plus + symbol next to
their name, for example an item named Longsword +1 it's an improved version of
Longsword.
11.1. Equipping
One needs to have an expertise in the weapon’s skill before using it,
otherwise the item can not be used / equipped. In addition, items belong to specific
body parts; that is, most of the items have to be worn in a specific body part when
they're equipped to be used correctly.
For example, a Longsword is a weapon that belongs to the hand and unless
it's not equipped there, it can't be used. However, they can be placed anywhere in
inventory, although not used then. In addition, you can't equip an item while you're
engaged in a fight. The following table shows the body parts, some example items
that belongs there and how many instances of that body part exist in a character:
Body partItemsNumber
HeadHelmet1
NeckAmulet1
ShoulderCloak1
ChestPlate mail1
ArmGauntlets1
HandLongsword2
FingerRing4
FeetBoots111.2. Enchantments
Some items have magical features, called enchantments. Those
enchantments are providing the wearer effects such as Power or Hit Points increase
or decrease, as long as the wearer have those items equipped. Such items are the
staffs, which provides the wearer i.e. a caster, with a permanent bonus of
Intelligence, as long as they hold the staff. A rule of thumb is that an enchantment
can increase / decrease temporary any of character’s statistics.
11.2.1. Mode of calculation
The effects an enchantment provides to a statistic can be computed with the
following modes. The same enchantment can work differently though item because
the mode of calculation used is different. The following list shows the calculation
modes, along with a description & the formula used:
NameDescriptionFormula*
Fixed valueApplies directly to statisticstatistic = statistic + effect
EfficiencyUses the efficiency bonus i.e. +1 statistic = statistic + (effect * (efficiency) + 1)
% of valueUses % of provided valuestatistic = statistic + ((effect / 100) * value)
% of stat totalUses % of statistic total valuestatistic = statistic + ((effect / 100) * stat total)
NameSelf-describes the enchantmentBy context
RangeRandom select from 2 numbersUsed supplementary with other modes
DoubleDoubles the effectUsed supplementary with other modes
* statistic = the current & final value of character’s statistic after the calculation,
effect = the value indicated by the enchantment i.e. Power +2,
stat total = the total value of a character’s statistic i.e. not current or filtered
11.2.2. Named enchantments
Enchantments can also be grouped under a common name that indicates
their purpose. This named group may have one or more enchantments, providing an
arsenal of enchantment effects to the wearer of item. Items may or may not be
infused with a named enchantment. By default, only one named enchantment may
infuse the item and inform players about. However, an item may further enchanted
by multiple enchantments. In such case, the context of the game decides the correct
way to present the item’s various enchantments to the player.
All items can get infused by an enchantment except items that are defined by
magic or have a single use such as wands, books, scrolls & potions. The following
tables shows the named enchantments, along with the effects they provide, the
mode which are using for calculating the effect & the list of item types on which canbe infused:
NameEffectModeAllowed
of Protection+5 ProtectionEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Fire Resistance+5 Fire ResistanceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Water Resistance+5 Water ResistanceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Earth Resistance+5 Earth ResistanceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Energy Resistance+5 Energy ResistanceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Mental Resistance+5 Mental ResistanceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Soul Resistance+5 Soul ResistanceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Health+10 HPEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Life+1 HP / **turnEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Greater Life+10 HP, +1 HP / **turnEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Power+2 PowerEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Intelligence+2 IntelligenceEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Personality+2 PersonalityEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Toughness+2 ToughnessEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Technique+2 TechniqueEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Quickness+2 QuicknessEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Perception+2 PerceptionEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Fire Damage1-4 Fire DamageRange,
EfficiencyWeapon
of Air Damage1-4 Air DamageRange,
EfficiencyWeapon
of Water Damage1-4 Water DamageRange,
EfficiencyWeapon
of Earth Damage1-4 Earth DamageRange,
EfficiencyWeapon
of Energy Damage1-4 Energy DamageRange,
EfficiencyWeapon
of Mental Damage1-4 Mental DamageRange,
EfficiencyWeapon
of Soul Damage1-4 Soul DamageEfficiencyWeapon
of Knights+2 Power,
+2 ToughnessEfficiencyWeapon, *Armor, Cloak, Amulet,
Staff, Ring
of Clerics+2 Intelligence,
+2 PersonalityEfficiencyWeapon, *Armor, Cloak, Amulet,
Staff, Ring
of Wizards+2 Intelligence,
+2 PerceptionEfficiencyWeapon, *Armor, Cloak, Amulet,
Staff, Ring
of Wizardry+4 Intelligence,
+4 PerceptionEfficiencyWeapon, *Armor, Cloak, Amulet,
Staff, Ring
of Cavalier+2 Personality,
+2 TechniqueEfficiencyWeapon, *Armor, Cloak, Amulet,
Staff, Ring
of Shadow+2 Technique,EfficiencyWeapon, *Armor, Cloak, Amulet,+2 Quickness
Staff, Ring
of Giant+2 Toughness,
+2 ProtectionEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Titan+4 Toughness,
+4 ProtectionEfficiency*Armor, Cloak, Amulet, Staff, Ring
of Hydra+2 Toughness,
+1 HP / **turnEfficiencyWeapon, *Armor, Cloak, Amulet,
Staff, Ring
of Scholar+10% Experience gained% of value Weapon, *Armor, Cloak, Amulet,
Staff, Ring
of Savant+25% Experience gained% of value Weapon, *Armor, Cloak, Amulet,
Staff, Ring
of Animalsx2 damage vs AnimalsDoubleWeapon
of Oozesx2 damage vs OozesDoubleWeapon
of Demonsx2 damage vs DemonsDoubleWeapon
of Elementalsx2 damage vs Elementals DoubleWeapon
of Dragonsx2 damage vs DragonsDoubleWeapon
of MedicineImmune to PoisonedName*Armor, Cloak, Amulet, Staff, Ring
of HumidityImmune to FlamedName*Armor, Cloak, Amulet, Staff, Ring
of MobilityImmune to ParalyzedName*Armor, Cloak, Amulet, Staff, Ring
of CourageImmune to FrightenedName*Armor, Cloak, Amulet, Staff, Ring
of LogicImmune to MaddenedName*Armor, Cloak, Amulet, Staff, Ring
of InvigorateImmune to ExhaustedName*Armor, Cloak, Amulet, Staff, Ring
of BlessingImmune to CursedName*Armor, Cloak, Amulet, Staff, Ring
* Armor here includes the types: Armor, Shield, Gauntlets, Helmet & Boots
** Stat affections apply 50% of the time when applied on per-turn basis
11.3. Worth
Some items are more expensive than other because are constructed by
specific components, which can be either common or rare and require different
expertise for their making. All item types have a base worth that shows how much
this item is worth initially.
11.3.1. Worth by evolution
Evolved versions of item are built upon base worth to increase the item worth. The
formula to calculate the worth of an evolved item is the following, rounded up:
worth_evolved = (base worth * (1 + (2.50 * evolved level)))
For example the weapon Longsword has a base worth of 50g; an evolved version of
it like Longsword +1 will increase its worth to (50 * (1 + (2.5 * 1))) = 175g.11.3.2. Worth by property
The item can break down into its properties such damage on weapons,
protection on armors, magic on amulets etc. Each property and amount of it
increases the item's worth. Note that some items provides one or more of these
properties; for that reason we don't deal with item types here rather properties
themselves. The following table shows the worth per property type & amount:
PropertyWorthExample
+1 damage2g2-4 damage = 12g
+1 protection2g8 protection = 16g
+1 enchantment affection, valued4g+4 Power = 16g
+1 enchantment affection, named15gPotion of Cure Poison = 35g
+1 named enchantment50gof Protection = 50g
11.3.3. Worth by spell
If item contains a spell i.e. wands, the expertise of spell and also its number
of charges are used to define the additional price. The formula to calculate the
additional worth of a spell-contained item is the following:
worth_spell = (((expertise + 1) * 5) * number_of_spell_charges)
The above equation assumes that expertise is a number from 0...n, where the first
(0) means the Initiate expertise and gets increased from then. Since this rulebook is
all about CRPGs, it’s game developer duty to implement this mechanism.
11.4. List
In the following content, the base items are presented. Base means that
those items are the basis for other, more specialized versions. Those specialized
versions may differ in efficiency, including added effects. However, they will always
share the basic properties of the item, the skill, the usable body part etc.
11.4.1. Weapon
Weapons are the primary tool to cause damage to your foes and there's a
large variety of them. Each weapon has one or more improved variations thatincreases damage as the Efficiency increases; that is, an improved version of a
weapon is stronger that previous. Some weapons starts slow, then increased rapidly
in much improved versions, others are already somewhat strong from the start but
they doesn't improve a lot. Finally, some weapons are restricted to some
professions. The base weapons are:
NameEffici Damage
encyDmg
TypeNum Body Used Skill
Hands part byBase Price
Worth
Bardiche+04-18MeleeTwoHandKnight Poleblade70g114g
Bardiche +1+48-22MeleeTwoHandKnight Poleblade70g305g
Bardiche +2+812-26MeleeTwoHandKnight Poleblade70g496g
Bardiche +3+1014-28MeleeTwoHandKnight Poleblade70g679g
Battle axe+04-10MeleeOneHandKnight Long axe40g68g
Battle axe +1+48-14MeleeOneHandKnight Long axe40g184g
Battle axe +2+610-16MeleeOneHandKnight Long axe40g292g
Battle axe +3+812-18MeleeOneHandKnight Long axe40g400g
Bow*+06-12 / 1-6Ranged TwoHandKnight Bow
Cleric65g101g**
Bow* +1+28-14 / 1-6Ranged TwoHandKnight Bow
Cleric65g272g**
Bow* +2+511-17 / 1-6Ranged TwoHandKnight Bow
Cleric65g446g**
Bow* +3+814-20 / 1-6Ranged TwoHandKnight Bow
Cleric65g621g**
Broad axe+03-8MeleeOneHandKnight Short axe35g57g
Broad axe +1+36-11MeleeOneHandKnight Short axe35g157g
Broad axe +2+69-14MeleeOneHandKnight Short axe35g256g
Broad axe +3+912-17MeleeOneHandKnight Short axe35g356g
Club+01-4MeleeOneHandKnight Bludgeon
Cleric15g25g
Club +1+34-7MeleeOneHandKnight Bludgeon
Cleric15g75g
Club +2+67-10MeleeOneHandKnight Bludgeon
Cleric15g124g
Club +3+910-13MeleeOneHandKnight Bludgeon
Cleric15g174g
Crossbow*+04-14 / 1-6Ranged TwoHandKnight Bow60g96g**
Crossbow* +1+37-17 / 1-6Ranged TwoHandKnight Bow60g258g**
Crossbow* +2+610-20 / 1-6Ranged TwoHandKnight Bow60g420g**
Crossbow* +3+913-23 / 1-6Ranged TwoHandKnight Bow60g582g**
Dagger+01-3MeleeOneHandKnight Short blade 15g
Cleric
Wizard23g
Dagger +1+45-7MeleeOneHandKnight Short blade 15g
Cleric
Wizard77g
Dagger +2+78-10MeleeOneHandKnight Short blade 15g
Cleric126gWizard
Dagger +3+910-12MeleeOneHandKnight Short blade 15g
Cleric
Wizard172g
Falchion+04-10MeleeOneHandKnight Long blade40g68g
Falchion +1+48-14MeleeOneHandKnight Long blade40g184g
Falchion +2+610-16MeleeOneHandKnight Long blade40g292g
Falchion +3+812-18MeleeOneHandKnight Long blade40g400g
Flail+03-8MeleeOneHandKnight Bludgeon35g57g
Flail +1+25-10MeleeOneHandKnight Bludgeon35g153g
Flail +2+47-12MeleeOneHandKnight Bludgeon35g248g
Flail +3+811-16MeleeOneHandKnight Bludgeon35g352g
Greatsword+06-20MeleeTwoHandKnight Long blade90g142g
Greatsword +1+39-23MeleeTwoHandKnight Long blade90g379g
Greatsword +2+713-27MeleeTwoHandKnight Long blade90g620g
Greatsword +3+1218-32MeleeTwoHandKnight Long blade90g865g
Halberd+04-18MeleeTwoHandKnight Poleblade70g114g
Halberd +1+48-22MeleeTwoHandKnight Poleblade70g305g
Halberd +2+812-26MeleeTwoHandKnight Poleblade70g496g
Halberd +3+1014-28MeleeTwoHandKnight Poleblade70g679g
Hammer+08-12MeleeTwoHandKnight Bludgeon70g110g
Hammer +1+513-17MeleeTwoHandKnight Bludgeon70g305g
Hammer +2+1018-22MeleeTwoHandKnight Bludgeon70g500g
Hammer +3+1523-27MeleeTwoHandKnight Bludgeon70g695g
Hand axe+04-7MeleeOneHandKnight Short axe
Cleric30g52g
Hand axe +1+48-11MeleeOneHandKnight Short axe
Cleric30g143g
Hand axe +2+610-13MeleeOneHandKnight Short axe
Cleric30g226g
Hand axe +3+812-15MeleeOneHandKnight Short axe
Cleric30g309g
Long sword+04-12MeleeOneHandKnight Long blade50g82g
Long sword +1+48-16MeleeOneHandKnight Long blade50g223g
Long sword +2+812-20MeleeOneHandKnight Long blade50g364g
Long sword +3+1014-22MeleeOneHandKnight Long blade50g497g
Mace+02-8MeleeOneHandKnight Bludgeon
Cleric35g55g
Mace +1+35-11MeleeOneHandKnight Bludgeon
Cleric35g155g
Mace +2+68-14MeleeOneHandKnight Bludgeon
Cleric35g254g
Mace +3+1012-18MeleeOneHandKnight Bludgeon
Cleric35g358g
Morning star+05-10MeleeOneHandKnight Bludgeon50g80gMorning star +1+27-12MeleeOneHandKnight Bludgeon50g213g
Morning star +2+510-15MeleeOneHandKnight Bludgeon50g350g
Morning star +3+813-18MeleeOneHandKnight Bludgeon50g487g
Quarterstaff+02-6MeleeOneHandKnight Pole
Cleric
Wizard20g36g
Quarterstaff +1+24-8MeleeOneHandKnight Pole
Cleric
Wizard20g94g
Quarterstaff +2+46-10MeleeOneHandKnight Pole
Cleric
Wizard20g152g
Quarterstaff +3+68-12MeleeOneHandKnight Pole
Cleric
Wizard20g210g
Scimitar+07-9MeleeOneHandKnight Long blade50g82g
Scimitar +1+310-12MeleeOneHandKnight Long blade50g219g
Scimitar +2+613-15MeleeOneHandKnight Long blade50g356g
Scimitar +3+916-18MeleeOneHandKnight Long blade50g493g
Scythe+01-8MeleeTwoHandKnight Poleblade
Cleric60g78g
Scythe +1+56-13MeleeTwoHandKnight Poleblade
Cleric60g248g
Scythe +2+1011-18MeleeTwoHandKnight Poleblade
Cleric60g418g
Scythe +3+1516-23MeleeTwoHandKnight Poleblade
Cleric60g588g
Short sword+03-7MeleeOneHandKnight Short blade 25g45g
Short sword +1+25-9MeleeOneHandKnight Short blade 25g116g
Short sword +2+510-14MeleeOneHandKnight Short blade 25g190g
Short sword +3+914-18MeleeOneHandKnight Short blade 25g269g
Spear+02-12MeleeTwoHandKnight Poleblade50g78g
Spear +1+46-16MeleeTwoHandKnight Poleblade50g219g
Spear +2+810-22MeleeTwoHandKnight Poleblade50g360g
Spear +3+1214-26MeleeTwoHandKnight Poleblade50g501g
War axe+05-7MeleeOneHandKnight Long axe40g64g
War axe +1+49-11MeleeOneHandKnight Long axe40g180g
War axe +2+813-15MeleeOneHandKnight Long axe40g296g
War axe +3+1217-19MeleeOneHandKnight Long axe40g412g
* Additional elemental damage (right side), if the item is of elemental type
** Prices are for non-elemental type items; they change if the item gets elemental
11.4.2. ArmorThe armor is what gets in between from any kind of attack out there. Without
armor, you wouldn't go much further as you would literally take damage to its fullest.
There are various armors for your chest and as in weapons, there are improved
versions of the same armoring which adds a bit more protection to it. The base
armors are:
NameEffici Protection
encyBody Used Skill
part byBase Price
worth
Chain mail+09Chest Knight Chained
armor100g
136g
Chain mail +1+211Chest Knight Chained
armor100g
394g
Chain mail +2+514Chest Knight Chained
armor100g
656g
Chain mail +3+817Chest Knight Chained
armor100g
918g
Leather armor+04 + TechniqueModChest Knight Leather
Cleric armor40g
56g
Leather armor +1 +26 + TechniqueModChest Knight Leather
Cleric armor40g
166g
Leather armor +2 +59 + TechniqueModChest Knight Leather
Cleric armor40g
276g
Leather armor +3 +711 + TechniqueModChest Knight Leather
Cleric armor40g
386g
Plate mail+013Chest Knight Plated
armor200g252g
Plate mail +1+417Chest Knight Plated
armor200g768g
Plate mail +2+821Chest Knight Plated
armor200g1284g
Plate mail +3+1225Chest Knight Plated
armor200g1800g
Ring mail+07Chest Knight Scaled
armor70g98g
Ring mail +1+411Chest Knight Scaled
armor70g289g
Ring mail +2+815Chest Knight Scaled
armor70g480g
Ring mail +3+1219Chest Knight Scaled
armor70g671g
Robe+01 + TechniqueModChest Knight -
Cleric
Wizard20g24g
Robe +1+12 + TechniqueModChest Knight -
Cleric
Wizard20g78g
Robe +2+23 + TechniqueModChest Knight -
Cleric
Wizard20g132g
Robe +3+34 + TechniqueModChest Knight -
Cleric
Wizard20g174g
Scale mail+07 + TechniqueModChest Knight Scaled80g108garmor
Scale mail +1+29 + TechniqueModChest Knight Scaled
armor80g318g
Scale mail +2+512 + TechniqueModChest Knight Scaled
armor80g528g
Scale mail +3+714 + TechniqueModChest Knight Scaled
armor80g738g
11.4.3. Shield
A shield is armor worn in the hand and provides extra armoring if a character
decides to use a shield. There are various shields for the hand and as in weapons,
there are improved versions of the same shield which adds a bit more protection to
it. The base shields are:
NameEffici
encyProtectionBody
partUsed
by
Buckler+01HandBuckler +1+12Buckler +2+2Buckler +3
Skill
Base
worthPrice
Knight Shield
Cleric
Wizard20g24g
HandKnight Shield
Cleric
Wizard20g78g
3HandKnight Shield
Cleric
Wizard20g132g
+34HandKnight Shield
Cleric
Wizard20g186g
Shield+04HandKnight Shield
Cleric40g54g
Shield +1+15HandKnight Shield
Cleric40g158g
Shield +2+26HandKnight Shield
Cleric40g262g
Shield +3+37HandKnight Shield
Cleric40g366g
Kite shield+05HandKnight Shield60g90g
Kite shield +1+16HandKnight Shield60g271g
Kite shield +2+38HandKnight Shield60g452g
Kite shield +3+510HandKnight Shield60g633g
11.4.4. Gauntlets
The gauntlets are providing yet another layer of protection and they're worn inhands. The protection they offer is not as much as armors and shields but it could
make a difference on difficult situations. They also do not require a skill to be used
and can be used by all professions. The base gauntlets are:
NameEffici
encyProtectionBody
partUsed
by
Gauntlets+01ArmGauntlets +1+12Gauntlets +2+2Gauntlets +3+3
Skill
Base
worthPrice
Knight -
Cleric
Wizard10g14g
ArmKnight -
Cleric
Wizard10g43g
3ArmKnight -
Cleric
Wizard10g72g
4ArmKnight -
Cleric
Wizard10g101g
11.4.5. Helmet
The helmet provides basic protection for the head. They're more like
supplementary armoring to the real thing, armors. However, as with gauntlets and
shields they provide good protection in improved versions. They also do not require
a skill to be used. The base helmets are:
NameEffici
encyProtectionBody
partUsed
by
Helmet+01HeadHelmet +1+12Helmet +2+2Helmet +3Base
worthPrice
Knight -
Cleric10g14g
HeadKnight -
Cleric10g43g
3HeadKnight -
Cleric10g72g
+34HeadKnight -
Cleric10g101g
Mage hat+00 + IntelligenceModHeadCleric -
Wizard20g20g
Mage hat +1+11 + IntelligenceModHeadCleric -
Wizard20g70g
Mage hat +2+22 + IntelligenceModHeadCleric -
Wizard20g120g
Mage hat +3+33 + IntelligenceModHeadCleric -
Wizard20g170g
11.4.6. Amulet
SkillThe amulets are usually magically enchanted and the majority of them are
expensive because of the jewelry they're covered with, as well the amount of magic
they contain. They also do not require a skill to be used and can be used by all
professions. The base amulets are:
NameEfficiency*Body
partUsed
by
Bone amulet+0NeckCeltic amulet+1Stone amulet
Skill
Base
worthPrice
Knight -
Cleric
Wizard100g140g
NeckKnight -
Cleric
Wizard100g350g
+2NeckKnight -
Cleric
Wizard100g600g
Crystal amulet+3NeckKnight -
Cleric
Wizard100g850g
Idol amulet+4NeckKnight -
Cleric
Wizard100g1100g
Pentagram
amulet+5NeckKnight -
Cleric
Wizard140g1350g
* Efficiency on amulets should not be shown as they are self-described by name
11.4.7. Cloak
The cloaks are worn above armors and usually give a small protection.
However, the power of cloaks is often magical and they boost one or more abilities.
They also do not require a skill to be used and can be used by all professions.
The base cloaks are:
NameEffici
encyProtectionBody
partUsed
by
Cloak+01ShoulderCloak +1+12Cloak +2+2Cloak +3+3
Skill
Base
worthPrice
Knight -
Cleric
Wizard10g14g
ShoulderKnight -
Cleric
Wizard10g43g
3ShoulderKnight -
Cleric
Wizard10g72g
4ShoulderKnight -
Cleric
Wizard10g101g11.4.8. Boots
The boots, as well shields, helmets and gauntlets are serving supplementary
role, providing similar protection to these armors, yet a worthy one if they're put all
together. They also do not require a skill to be used and can be used by all
professions. The base boots are:
NameEffici
encyProtectionBody
partUsed
by
Boots+01FeetBoots +1+12Boots +2+3Boots +3+5
Skill
Base
worthPrice
Knight -
Cleric
Wizard10g14g
FeetKnight -
Cleric
Wizard10g45g
4FeetKnight -
Cleric
Wizard10g76g
6FeetKnight -
Cleric
Wizard10g107g
11.4.9. Staff
The staffs are the primary equipment for spell casters as it allows to channel
divine and elemental forces in the form of a spell. Without it, casters won't be able to
cast the spells they possess. Staffs are always magically enchanted. They also do
not require a skill to be used. The base staffs are:
NameEffici
encyEnchantmentsNum Body Used
Hands part by
Staff+0+2 IntelligenceOne
Hand
Staff +1+2+4 IntelligenceOne
Staff +2+4+6 IntelligenceStaff +3+6Staff +4Staff +5
11.4.10. Wand
Skill
Base
worthPrice
Cleric -
Wizard100g108g
HandCleric -
Wizard100g358g
OneHandCleric -
Wizard100g608g
+8 IntelligenceOneHandCleric -
Wizard100g858g
+8+10 IntelligenceOneHandCleric -
Wizard100g1108g
+10+12 IntelligenceOneHandCleric -
Wizard100g1358gThe wands are practically staffs that cast one particular spell. Each wand
contains a certain number of charges. In addition, wands are the only magical items
that can be used by non spell-casting professions, such as Knights, although only
wands of weaker power can be used by them. They also do not require a skill to be
used. The base wands are:
NameEffectNum Body Used
Hands part by
Initiate wandCasts an Initiate* spell
(12 charges)One
Hand
Apprentice wandCasts an Apprentice* spell
(12 charges)One
Adept wandCasts an Adept* spell
(12 charges)Master wandCasts a Master* spell
(12 charges)
Grandmaster wand Casts a Grandmaster* spell
Base
worthPrice
Knight -
Cleric
Wizard50g110g
HandKnight -
Cleric
Wizard50g**
OneHandKnight -
Cleric
Wizard50g230g
OneHandCleric
-
Wizard50g290g
OneHandCleric
-
Wizard50g350g
(12 charges)
Skill
* a spell of an appropriate expertise must infuse the wand
** no spells yet for this type of wand (based on expertise)
11.4.11. Ring
Rings are an important property of every adventurer because of flexibility, as
well the fact that wearer can equip up to four (4) of them. In addition, they can be
enchanted & equipped by every profession. They also do not require a skill to be
used. The base rings are:
NameEfficiency*Body
part
Bronze ring+0Iron ring
Used
by
Skill
Base
worthPrice
Finger Knight -
Cleric
Wizard25g25g
+0Finger Knight -
Cleric
Wizard25g25g
Silver ring+1Finger Knight -
Cleric
Wizard50g175g
Golden ring+1Finger Knight -
Cleric
Wizard50g175g
Jewel ring+2Finger Knight -
Cleric
Wizard75g450g
Pearl ring+2Finger Knight -
Cleric
Wizard75g450gEmerald ring+3Finger Knight -
Cleric
Wizard100g850g
Opal ring+3Finger Knight -
Cleric
Wizard100g850g
* Efficiency on rings should not be shown as the rings are self-described by name
11.4.12. Book / Scroll
Books and scrolls are very versatile items in the sense that they can be the
basic weapon of spell casters and at the same improve anyone's ability or
knowledge permanently. They can contain both knowledge and magic powers and
their effects varies. They are usable by hand. A scroll is also used for casting spells
but only once and caster doesn't actually learn anything about that particular spell.
They also do not require a skill to be used. The base books and scrolls are:
NameEffectNum Body Used
hand part
by
s
Initiate bookTeaches an Initiate spellOne
Hand
Apprentice bookTeaches an Apprentice spellOne
Adept bookTeaches an Adept spellMaster book
Skill
Base
worthPrice
Cleric
-
Wizard100g105g
HandCleric
-
Wizard150g*
OneHandCleric
-
Wizard200g215g
Teaches a Master spellOneHandCleric
-
Wizard250g270g
Grandmaster bookTeaches a Grandmaster spellOneHandCleric
-
Wizard300g325g
Initiate scrollCasts an Initiate spellOneHandCleric
-
Wizard20g25g
Apprentice scrollCasts an Apprentice spellOneHandCleric
-
Wizard40g*
Adept scrollCasts an Adept spellOneHandCleric
-
Wizard60g75g
Master scrollCasts a Master spellOneHandCleric
-
Wizard80g100g
Grandmaster scrollCasts a Grandmaster spellOneHandCleric
-
Wizard100g125g
Book of Power+1 Power permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Personality +1 Personality permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Intelligence +1 Intelligence permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Toughness +1 Toughness permanentlyOneHandKnight
Cleric100g100g
-Wizard
Book of Technique+1 Technique permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Quickness+1 Quickness permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Perception+1 Perception permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Fitness+50 skill XP permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Lore+50 skill XP permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Persuasion +50 skill XP permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Taming+50 skill XP permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Quickhand+50 skill permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Stealth+50 skill permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Awareness +50 skill permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Fire
Element+1 Fire resistance permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Air Element +1 Air resistance permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Water
Element+1 Water resistance permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Earth
Element+1 Earth resistance permanentlyOneHandKnight -
Cleric
Wizard100g100g
Book of Energy
Element+1 Energy resistance permanently OneHandKnight -
Cleric
Wizard100g100g
Book of Mental
Element+1 Mental resistance permanentlyHandKnight -
Cleric
Wizard100gBook of Soul
Element+1 Soul resistance permanentlyKnight -
Cleric
Wizard100g
One
One
Hand
* no spells yet for this type of book / scroll (based on expertise)
100g
100g11.4.13. Potion
Potions are one of the most flexible items because their effects vary greatly
and can be consumed by anyone. They are usable by hand. They also do not
require a skill to be used. The basic potions are:
NameEffectNum
handsBody
partUsed
by
Potion of HealingRestores 2-6 Hit pointsOneHandPotion of Healing +1 Restores 4-12 Hit pointsOnePotion of Healing +2 Restores 6-18 Hit points
Skill
Base
worthPrice
Knight -
Cleric
Wizard10g18g
HandKnight
Cleric
Wizard-10g43g
OneHandKnight
Cleric
Wizard-10g68g
Potion of Healing +3 Restores 8-24 Hit pointsOneHandKnight
Cleric
Wizard-10g93g
Potion of Cure
PoisonCures Poisoned conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of Cure
FlamingCures Flamed conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of Cure
ParalysisCures Paralyzed conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of Cure FearCures Frightened conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of Cure
InsanityCures Maddened conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of Cure
ExhaustionCures Exhausted conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of Cure
CurseCures Cursed conditionOneHandKnight
Cleric
Wizard-10g35g
Potion of PoisonCauses Poisoned conditionOneHandKnight
Cleric
Wizard-10g35g
11.4.14. Misc
Finally, there are items that couldn’t be placed into any of the aforementioned
categories, mostly because their features vary a lot. Most of these don’t have any
relation to each other but they still can be quite common in the world and/or provide
common abilities, while on occasion share some some abilities with all common-type items referred in previous chapters. Finally, such items are more open to
interpretation, for example Torch has 24 turns before burning out. Such items are:
NameNum Body Used
Hands part bySkillFeaturesBase Price
Worth
TorchOne-Lighting (24 turns)
Damage (1-4, Melee)3g
Hand
*
7g
* Usable by all professions
12. Spells
Spells are the workhorse of casting professions such as Wizards and Clerics
i.e. Knights can't cast spells. A caster can cast a spell with various methods such as
using his Staff (i.e. not quarterstaff), a Scroll or a Wand. For a caster to cast a spell
using a staff, the spell must be learned first by using a spell book. In addition, caster
is required to learn the particular magic skill first i.e. to even learn a fire-based spell
one has to learn the Fire magic skill first. Some spells can't be used by some casting
professions. They're sorted primarily by their expertise because of the varied
amount of energy required for casting and secondly by profession.
12.1. Relation to D&D spell levels
D&D provides a number of levels, specifically nine (9) levels per casting
class, which levels is a general indicator of how powerful the spell is. ORS uses
descriptive expertise levels i.e. Master, rather numeric ones. A close interpretation of
D&D spell levels & ORS expertise levels is shown on following table:
ORS
expertise levelD&D
spell level(s)
Initiate0 (cantrips), Level 1
ApprenticeLevel 2, Level 3
AdeptLevel 4, Level 5
MasterLevel 6, Level 7
GrandmasterLevel 8, Level 9
12.2. Duration
Spells may have an instant effect i.e. causing damage, while some may have
a continuous effect on the target, for a predefined amount of turns / skill level. Forexample, the spell Light, which it casts on caster himself, provides lighting for 24
turns / skill level. One (1) turn is equivalent to the following:
•
•
•
1 minute (on a party move)
1 minute (on a combat turn)
5 minutes (on a resting turn)
12.3. Capped effect by level
Some spells are using the caster's expertise level for their effect. These
spells have a maximum limit of levels based on the expertise's starting level, plus 5
levels. If the caster has more than expertise's level plus 5 levels, the level used is
limited to this number. Check the following formula:
expertise_level = (expertise_level > starting_expertise_level + 5 ?
starting_expertise_level + 5 :
expertise_level)
In game context, the starting expertise level can be easily computed if developer
gives an index of 0..n to expertise i.e. Initiate = 0, Apprentice = 1 etc. Therefore, the
starting expertise level can be computed with the following formula:
starting_expertise_level = (expertise * 5)
NOTE: Since monsters do not have an expertise level, their level is used instead.
The following formula does this, shrinking the monster's level by 4 to normalize high
levels:
monster_expertise_level = (monster_level / 4)
12.4. Casting a spell as a non spell-caster
There are cases where a character can cast a spell without being a spell-
caster or simply not knowing the skill at all. One of such cases is casting a spell
from a Wand or a Scroll, which doesn’t take professions into account. In this case,
the character may not have the skill of the spell contained in the wand, therefore his
expertise level is simply zero (0). In such cases, the non-caster’s skill level
becomes one (1).
skill_level = (skill_level == 0 || not_caster ? 1 : skill_level)12.5. List
Spells are the primary weapons of caster professions, such as Wizards &
Clerics. They’re sorted into the element they’re drawing their power from, by which
profession(s) can be used, the expertise level that is required and such. Wherever a
level is mentioned, the caster’s skill level is considered, not the caster’s level. The
base spells are:
NameSkill*** Profe Expe
ssion rtise*Dura
tion**OnAction
Acid BubblesEarthWizardINInstantOne1-2 Earth damage / level
CureSoulClericINInstantOne1-8 Hit points healing
FireboltFireWizardINInstantOne1-2 Fire damage / level
10% Flamed condition
Freezing Spikes AirWizardINInstantOne1-4 Air damage / level
-5 Quickness (1 turn / level)
Holy FlameSoulClericINInstantOne1-4 Soul damage / level
Iron WardMentalWizardIN4 turnsSelf+3 Protection
LightEnergyCleric
WizardIN24 turnsSelfNormal lighting
Magical ArmorEnergyClericIN4 turnsParty+2 Protection
* Expertise: ΙΝ: Initiate, AP: Apprentice, AD: Adept, MA: Master, GR: Grandmaster
** Duration can be either instant or lasting a predefined amount of turns / level
*** The skill the spell belongs to i.e. Fire magic
13. Starting equipment & Spells
At the start of adventuring, the party characters require some basic
equipment to get going, without getting killed in minutes. For spell casters, they’re
supposed to know some spells as well. The chosen Profession and Skills are used
to define the character’s starting equipment. The following tables provides a list of
starting equipment, based on each character’s properties:

13.1. By Profession
Professions may define a starting set of equipment. The following table lists
all professions and the equipment they give to starting-out characters:
Profession				Starting equipment
Knight					Helmet, Boots
Cleric					Robe, Boots
Wizard					Robe, Boots

13.2. By Skill
The items & spells the character starts with are based primarily on starting
Skills. The following table lists all the skills and the starting equipment & spells:
Skills					Starting equipment			Spells
Short blade				Dagger					-
Bow					Bow					-
Bludgeon				Club					-
Short axe				Hand axe				-
Pole					Quarterstaff				-
Shield					Shield					-
Leather armor				Leather armor				-
Fire magic*				Wooden staff				Firebolt
Air magic*				Wooden staff				Freezing Spikes
Water magic*				Wooden staff				-
Earth magic*				Wooden staff				Acid Bubbles
Energy magic*				Wooden staff				Light
Mental magic*				Wooden staff				Iron Ward
Soul magic*				Wooden staff				Cure
* one item, regardless the number of magic skills
