# FORBIDDEN LANDS

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
