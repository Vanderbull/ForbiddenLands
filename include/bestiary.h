#ifndef BESTIARY_H
#define BESTIARY_H

std::string bestiaryDecription[100];
std::ifstream bestiaryFile ("./data/bestiary");
std::string theLine;
std::string savedLine;

static int counting = 0;

int loadBestiary()
{
    return 0;
    if (bestiaryFile.eof())
    {
        return 0;
    }
    else
    {
        getline(bestiaryFile,theLine);
        if(theLine.find("#")==std::string::npos)
        {
            //RenderText(savedLine.c_str(), Black, 20, current.h - 40,fontSize);
            //RenderText(std::to_string(counting), Black, 20, current.h - 80,fontSize);
            counting++;
            return 1;
        }
        else
        {
            savedLine = theLine;
            //RenderText(theLine.c_str(), Black, 20, current.h - 40,fontSize);
            //RenderText(std::to_string(counting), Black, 20, current.h - 80,fontSize);
            counting++;
            return 1;
        }
    }
}
#endif
