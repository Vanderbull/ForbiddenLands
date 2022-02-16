#ifndef CREATE_WATER_H
#define CREATE_WATER_H

items createWater()
{
    items waterBottle(0);
    waterBottle.icon = "./icons/items/potion.png";
    std::cout << "creating water..." << std::endl;
    return waterBottle;
};

#endif
