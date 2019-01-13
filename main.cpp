#include <iostream>
#include <algorithm>
#include <string>

#include "nickname.h"

int main (int argc, char** argv)
{
    RadixTree nicknames;

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            nicknames.add(argv[i]);
        }
    }
    else
    {
        std::string newNick;

        while (std::cin)
        {
            std::cin >> newNick;
            nicknames.add(newNick);
        }
    }

    nicknames.printMinP();
    nicknames.printTree();

    return 0;
}
