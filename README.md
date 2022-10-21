# FORBIDDEN LANDS

## Using GNOME Keyring as Git Credential Helper
https://blog.scottlowe.org/2016/11/21/gnome-keyring-git-credential-helper/
https://stackoverflow.com/questions/13385690/how-to-use-git-with-gnome-keyring-integration

## Coding rules
All local developed code should be pushed and commited into the "development" branch and not the main, the main branch is only for
merging development commits.

## Character generation idea
- Define generations of relatives for the character


## World actions
- Define what actions that can be executed in the world view
- How should the actions available be presented to the player?

## General game development decisions
- NO classes
- NO genders
- NO general experience points or level

## Experience development
Should the characters develop there skills by using them or should they improve them by getting experience and leveling up and distribute experience points.

### Pros usage of skills
- More dynamic development of the character
### Cons usage of skills
- More difficult to learn new skills



## Character classes
Should we have character classes or not? What do they contribute to the the immersion of the game?
- Is it better to just let the player develop its character how it wants and let them decide if they are a magician or a warrior bunny?

## Two stamina system
Daily and action based stamina
- What is a good number for daily stamina?
- Should the action based stamina drain be the same for daily stamina?
- Should the action based stamina be affected by the daily stamina?

### Examples on stamina draining actions
- Sneaking
- Searching
- Moving
- Fighting


### Examples on stamina recovering actions
- Eating & Drinking
- Resting
- Quaff recovering potions


## Skill tree v.s Skill list
https://gamedev.stackexchange.com/questions/57553/when-should-i-use-skill-trees-versus-skill-lists-in-an-rpg

Summary: Lists provide more agency, while trees provide more easily anticipated results that are simpler to balance and utilize in design.

To be as concise as possible, the difference between lists and trees of decisions is the level of freedom the individual making the choices has.

When speaking of skills and character progression specifically, lists such as found in Elder Scrolls provide freeform decision making. Trees provide a more guided approach, usually representing classes or sub-classes of some form. There is less freedom in character progression/creation, as the concept of a tree necessitates requirements to unlock latter levels/branches.

The freeform list provides a greater sense of agency for the player, allowing a greater number of options. The more guided tree provides a simpler system to consider and anticipate as a designer, resulting in a system easier to balance. So, the end result is that you have a choice for a potentially more balanced system versus a system that provides more agency.


Summary: Lists provide more agency, while trees provide more easily anticipated results that are simpler to balance and utilize in design.

To be as concise as possible, the difference between lists and trees of decisions is the level of freedom the individual making the choices has.

When speaking of skills and character progression specifically, lists such as found in Elder Scrolls provide freeform decision making. Trees provide a more guided approach, usually representing classes or sub-classes of some form. There is less freedom in character progression/creation, as the concept of a tree necessitates requirements to unlock latter levels/branches.

The freeform list provides a greater sense of agency for the player, allowing a greater number of options. The more guided tree provides a simpler system to consider and anticipate as a designer, resulting in a system easier to balance. So, the end result is that you have a choice for a potentially more balanced system versus a system that provides more agency.

To answer your edit questions:

    Complexity largely depends on the specifics of implementation. However, all else being equal, a freeform system is far more complex as the potential number of results are significantly higher.

    Yes, the traditional usage of the two is for lists to be atomic actions (such as Elder Scrolls' system) while trees are used for "Perks" or "Abilities" to simulate a focus on developing enhanced skills in a specific domain. However, this is hardly a requirement.

    Much changed between Morrowind and Skyrim, largely due to a number of decisions far too complex to attribute simply to "using a list-based skill system".

A skill tree works usually better in a scenario, where:

    The skill points are limited,
    Skills provide a more significant advantage,
    The game 'feels' better, if the player characters are more specialized (the character classes / roles are easier to distinguish).

The Elder Scrolls - style skill advancement is on the other hand:

    More realistic,
    Encourages players to try many different approaches (the player won't have a significant disadvantage if he switches from melee to magic at level 30, for example),
    Easier to balance,
    Provides a feel of continuous progression (no "the best skill is unlocked at level 30 in the fire magic skill tree, I'll just try to survive until then" effect).

In my opinion, the Elder Scrolls approach is more viable in a single-player game. The player doesn't have to start over if he wants to try a different play style. In Morrowind for example, you can be an armored melee fighter for the first 30 levels or so - and then decide to try the thieving skills / quests without receiving any penalty (or having to create a new character and start from level 1).

![image](https://user-images.githubusercontent.com/1743820/147721022-8b4d722f-9ca1-48e1-a2df-37edf2b1f3e7.png)
## New image editing tool
### 2022-01-21
pixlr.com a online image editor

### Teleport
```c++
void teleport(int dest_x , int dest_y, int& src_x, int& src_y)
{
    src_x=dest_x;
    src_y=dest_y;
}

teleport(4,4,PlayerCoordinate.x,PlayerCoordinate.y);
```

- On target
The caster appears in the correct location.
- Off target
The caster appears safely, a random distance away
from the destination in a random direction. Distance off target
is 1d10x1d10% of the distance that was to be travelled. The
direction off target is determined randomly
- Similar area
The caster winds up in an area that is visually or
thematically (depending on how the caster identifi ed it while
casting) similar to the target area. It is possible (25% chance)
that this result will indicate that the correct location has been
reached but that the caster and party will arrive too high, fall-
ing 1d% ft unless there is means to arrest the fall. If the party
arrives too high and the result would entomb them in a solid
surface, they die instantly. Generally, the caster will appear
in the closest similar place within range. If no such area exists
within the spell’s range, the spell simply fails.
- Mishap
The caster and anyone else teleporting with him or
her arrive beneath the destination point, causing instant death
if the area is solid.

<img src="https://user-images.githubusercontent.com/1743820/147882641-b59d7eea-24dc-4e21-af9a-22ef5a8fd5d0.png" width="150" height="150">

### Bless ( Reversible )
- Clerical Conjuration/Summoning
- level: Cleric 1
- Range: 60 ft
- duration: 6 rounds
- area of effect: 50 x 50 ft
- components: V,S,M
- casting time: 1 round
- Saving throw: None

<p>
This minor benison raises the morale and attack rolls of any
creatures allied with the casting cleric by +1 or +5% as appro-
priate. Any creatures already engaged in melee combat will
not gain the spell’s benefi ts. The spell is reversible, allowing
the cleric to curse his or her enemies with—5% morale and
–1 to hit.
The spell’s area of effect is a circular area centred at the tar-
get point, which cannot be more than 60 ft from the cleric.
Holy water is required to cast the spell (unholy water for the
reverse).
</p>

<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">

### Command
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Create Water (Reversible)
- Clerical Transmutation/Alteration
- level: Cleric 1
- Range: 10 ft
- duration: Instantaneous (permanent)
- area of effect: Up to 30 cubic ft
- components: V,S,M
- casting time: 1 round
- Saving throw: None

<p>
This spell creates potable water, four gallons per level of the
caster. The water may be created in a receptacle or in thin
air (whence it will, of course, fall). Water cannot be created
inside a creature, nor can it be created in any place the caster
cannot see. The reverse of the spell destroys water (including
fog, steam, mist, etc.) in the same quantities as create water .
</p>

<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Cure critical wounds
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Cure serious wounds
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Cure light wounds
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Detect evil
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Detect magic
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Light
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Protection from evil
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Purify food and drink
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Remove fear
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Resist cold
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">
### Sanctuary
<img src="https://user-images.githubusercontent.com/1743820/147883166-fa90ac0d-bb71-4fc0-a552-2f89a2c6e7ae.png" width="150" height="150">

sudo apt install g++
sudo apt-get install -y libsqlite3-dev
sudo apt install libsdl2*

[Contribution guidelines for this project](CONTRIBUTING.md)

![This is an image](https://myoctocat.com/assets/images/base-octocat.svg)

## Setting up the developer enviroment

sudo apt install git git-lfs

sudo apt install codeblocks

## SDL 2 and supporting libraries:

## SDL2 base:

sudo apt install libsdl2-dev libsdl2-2.0-0

## SDL Image:

sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0

## SDL Mixer (for audio):

sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0

## SDL True Type Fonts:

sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0

## OpenGL and GLEW:

This command will install the essentials to get going with OpenGL:

sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev

## Install GLEW:

sudo apt install libglew-dev

![sqlite3](https://upload.wikimedia.org/wikipedia/commons/thumb/3/38/SQLite370.svg/320px-SQLite370.svg.png)

## Install sqlite3

- sudo apt-get install -y libsqlite3-dev

## OBJ Loader code example
http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

## Cross compiling on linux for windows
https://wiki.codeblocks.org/index.php/Code::Blocks_and_Cross_Compilers

http://www.weekendwastemonster.net/crpgs/pool/dragonbait/PoR_page2.html

http://forums.codeblocks.org/index.php?topic=3343.0

sudo apt-get install libboost-all-dev

https://github.com/pvigier/dependency-graph

## dependency-graph

A python script to show the "include" dependency of C++ classes.

It is useful to check the presence of circular dependencies.
Installation

The script depends on Graphviz to draw the graph.

On Ubuntu, you can install the dependencies with these two commands:

- sudo apt install graphviz
- sudo apt install python3-pip
- ~/Documents/Vanderbull/ForbiddenLands/dependency-graph-master
    - pip3 install -r requirements.txt
- ~/Documents/Vanderbull/ForbiddenLands/dependency-graph-master
- pip install graphviz

Manual

usage: dependency_graph.py [-h] [-f {bmp,gif,jpg,png,pdf,svg}] [-v] [-c]
                           folder output

positional arguments:
  folder                Path to the folder to scan
  output                Path of the output file without the extension

optional arguments:
  -h, --help            show this help message and exit
  -f {bmp,gif,jpg,png,pdf,svg}, --format {bmp,gif,jpg,png,pdf,svg}
                        Format of the output
  -v, --view            View the graph
  -c, --cluster         Create a cluster for each subfolder

## GIT SETUP ( LINUX )
    Make Git store the username and password and it will never ask for them.

git config --global credential.helper store

    Save the username and password for a session (cache it);

git config --global credential.helper cache

## GIT COMMIT CONDUCT
https://gist.github.com/robertpainsi/b632364184e70900af4ab688decf6f53


Formatting your README
READMEs generally follow one format in order to immediately orient developers to the most important aspects of your project.

Project name: Your project’s name is the first thing people will see upon scrolling down to your README, and is included upon creation of your README file.

Description: A description of your project follows. A good description is clear, short, and to the point. Describe the importance of your project, and what it does.

Table of Contents: Optionally, include a table of contents in order to allow other people to quickly navigate especially long or detailed READMEs.

Installation: Installation is the next section in an effective README. Tell other users how to install your project locally. Optionally, include a gif to make the process even more clear for other people.

Usage: The next section is usage, in which you instruct other people on how to use your project after they’ve installed it. This would also be a good place to include screenshots of your project in action.

Contributing: Larger projects often have sections on contributing to their project, in which contribution instructions are outlined. Sometimes, this is a separate file. If you have specific contribution preferences, explain them so that other developers know how to best contribute to your work. To learn more about how to help others contribute, check out the guide for setting guidelines for repository contributors.

Credits: Include a section for credits in order to highlight and link to the authors of your project.

License: Finally, include a section for the license of your project. For more information on choosing a license, check out GitHub’s licensing guide!

Your README should contain only the necessary information for developers to get started using and contributing to your project. Longer documentation is best suited for wikis, outlined below.


https://levelup.gitconnected.com/how-to-create-a-bitmap-font-with-freetype-58e8c31878a9
