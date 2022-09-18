#include "name_generator.h"

char NamePrefix[7][5] = {
    "", //who said we need to add a prefix?
    "bel", //lets say that means "the good"
    "nar", //"The not so good as Bel"
    "xan", //"The evil"
    "bell", //"the good"
    "natr", //"the neutral/natral"
    "ev", //Man am I original
};

char NameSuffix[16][5] = {
    "", "us", "ix", "ox", "ith",
    "ath", "um", "ator", "or", "axia",
    "imus", "ais", "itur", "orex", "o",
    "y"
};

const char NameStems[20][10] = {
    "adur", "aes", "anim", "apoll", "imac",
    "educ", "equis", "extr", "guius", "hann",
    "equi", "amora", "hum", "iace", "ille",
    "inept", "iuv", "obe", "ocul", "orbis"
};

void NameGen(char* PlayerName)
{
    PlayerName[0]=0; //initialize the string to "" (zero length string).
    //add the prefix...
    strcat(PlayerName, NamePrefix[(rand() % 7)]);
    //add the stem...
    strcat(PlayerName, NameStems[(rand() % 20)]);
    //add the suffix...
    strcat(PlayerName, NameSuffix[(rand() % 16)]);
    //Make the first letter capital...
    PlayerName[0]=toupper(PlayerName[0]);
    return;
};
