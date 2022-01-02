# FORBIDDEN LANDS

![image](https://user-images.githubusercontent.com/1743820/147721022-8b4d722f-9ca1-48e1-a2df-37edf2b1f3e7.png)

## Races

### DWARF
Dwarfs are a short and burly race, living in mountain fastnesses
underground. They are loyal friends and fi erce adversaries,
known for their steadfastness in all things.
The dwarfs are inherently resistant to many spells and spell-like
effects. Dwarfi sh characters gain bonuses against the use of
most magic, including all spells, wands, rods, and staves. The
amount of the bonus depends upon the dwarf’s constitution:
every 3.5 points of constitution (rounding down fractions)
grants a bonus of +1 against such magic. Moreover, the hardy
dwarfi sh nature imparts a similar bonus on any saving throws
against poison.
Dwarfs are not a numerous folk, but they are adventurous,
loving the lustre of gold, the glitter of gems, and the quality
of well-wrought metals. Dwarfs can live to an age of 350 years
or more.

#### Summary of dwarﬁsh Racial abilities:
- +1 constitution, -1 charisma (with respect to all but
dwarfs)
- +1 to hit against goblins, half-orcs, hobgoblins, and orcs
- +1 bonus per 3.5 points of Con to saves against magic and
poison
- -4 penalty to any attacks made against the dwarf by giants,
ogres, ogre mages, titans and trolls.

- languages: Dwarfish, gnomish, goblin, kobold, and orcish,
and the common tongue and the appropriate alignment
tongue. Regardless of intelligence, a dwarf may only ever learn
two languages in addition to those listed.

- Infravision * : 60 ft
Within ten ft, a dwarf can detect certain facts concerning
engineering, stonework, etc. Although no signifi cant time is
required, the character must deliberately observe his or her
surroundings (i.e., the player must state that the dwarf is using
this particular talent in order to gain information).
- Detect the existence of slopes or grades: 75%
- Detect the existence of new construction: 75%
- Detect sliding or shifting rooms or walls: 66%
- Detect traps involving stonework: 50%
- Determine depth underground: 50%

### ELF
### GNOME
### HALF-ELF
### HALFLING
### HALF-ORC
### HUMAN

## Spells

### cleRIc SpellS BY leVel

#### Level one
Bless
Command
Create Water
Cure Light Wounds
Detect Evil
Detect Magic
Light
Protection From Evil
Purify Food and Drink
Remove Fear
Resist Cold
Sanctuary

#### Level two
Augury
Chant
Detect Charm
Find Traps
Hold Person
Know Alignment
Resist Fire
Silence 15’ Radius
Slow Poison
Snake Charm
Speak With Animals
Spiritual Weapon

#### Level three
Animate Dead
Continual Light
Create Food and Water
Cure Blindness
Cure Disease
Dispel Magic
Feign Death
Glyph of Warding
Locate Object
Prayer
Remove Curse
Speak with Dead

#### Level four
Cure Serious Wounds
Detect Lie
Divination
Exorcise
Lower Water
Neutralise Poison
Protection From Evil 10 ft Radius
Speak With Plants
Sticks to Snakes
Tongues

#### Level five
Atonement
Commune
Cure Critical Wounds
Dispel Evil
Flame Strike
Insect Plague
Plane Shift
Quest
Raise Dead
True Seeing

#### Level Six
Aerial Servant
Animate Object
Blade Barrier
Conjure Animals
Find the Path
Heal
Part Water
Speak With Monsters
Stone Tell
Word of Recall

#### Level Seven
Astral Spell
Control Weather
Earthquake
Gate
Holy Word
Regenerate
Restoration
Resurrection
Symbol
Wind Walk

### dRUId SpellS BY leVel
| Level one | Level two | Level three |
|     :---:      |     :---:      |     :---:      |
| Bless     | Augury     | Animate dead     |
| Command       | Chant       | Continual light       |

### maGIc USeR SpellS BY leVel
| Level one | Level two | Level three |
|     :---:      |     :---:      |     :---:      |
| Bless     | Augury     | Animate dead     |
| Command       | Chant       | Continual light       |

### IllUSIOnISt SpellS BY leVel
| Level one | Level two | Level three |
|     :---:      |     :---:      |     :---:      |
| Bless     | Augury     | Animate dead     |
| Command       | Chant       | Continual light       |

<img src="https://user-images.githubusercontent.com/1743820/147883065-d65eac70-4d8e-4dd9-9f4d-efde43d89d72.png" width="150" height="150">

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

##

Here is a simple footnote[^1].

A footnote can also have multiple lines[^2].  

You can also use words, to fit your writing style more closely[^note].

[^1]: My reference.
[^2]: Every new line should be prefixed with 2 spaces.  
  This allows you to have a footnote with multiple lines.
[^note]:
    Named footnotes will still render with numbers instead of the text but allow easier identification and linking.  
    This footnote also has been made with a different syntax using 4 spaces for new lines.
    
## Setting up the developer enviroment

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
- pip3 install -r requirements.txt
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
