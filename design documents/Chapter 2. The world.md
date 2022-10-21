Table of content


The Planeverse is a vast place, although not without rules, at least in the
Natural Plane. The party can move, can get hungry, buy stuff, need to rest & there’s
a day-night cycle like in real life. All this may sound too obvious & perhaps a time of
waste to even consider, but in a CRPG, a set of rules will be required to restrict
things in favor of common sense & balance.

**2.1. Time**
The time can be broken down into minutes, hour, day, month & year. There
are no different rules than the ones already used in our reality, so 60 minutes
makes up an hour, 24 hours makes up a day, 30 days (strict) make up a month &12 months make up a year. Time can be increased through the following ways:
* Time is increased by one (1) minute when the party moves
* Time is increased by one (1) minute when a player makes a combat action
* Time is increased by eight (8) hours when the party performs a long rest
* Time is increased by a period when party makes a rest until fully healed
* Time is increased by a period when party travels to another map

2.2. Lighting
There are various states of lighting in the world environments. Those
environments can be either interior (interior) or exterior (etc. forest). Lighting can be
modified either by environment (i.e. daylight) or equipment/magic (i.e. torch, spells).
Interior areas can provide the following lighting states:
* None – Usually encountered in interior areas, such as dungeons. Visibility is
really low, allowing up to one (1) visible square before everything gets pitch
black.
* Normal – Stronger lighting that none. An interior area can be lit for up two (2)
visible squares & perhaps more but the rest remains pitch black.
Exterior areas can provide the following lighting states:
* Day – Very strong lighting.
* Night – Strong lighting.

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