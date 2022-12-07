#!/bin/bash
sudo apt install codeblocks -y
sudo apt install libsdl2-* -y
sudo apt install libsdl2-dev libsdl2-2.0-0 -y
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y
sudo apt-get install -y libsqlite3-dev -y
sudo apt-get install libboost-all-dev -y
sudo apt install graphviz -y
sudo apt install python3-pip -y
cd ~/Documents/GitHub/ForbiddenLands/dependency-graph-master
pip3 install -r requirements.txt
pip install graphviz
