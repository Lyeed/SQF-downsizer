#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./cleaner [file]" << std::endl;
        return EXIT_FAILURE;
    }

    fstream file_read(argv[1]);
    if (!file_read.is_open())
    {
        std::cout << "Error: Can't find file " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    string line;
    vector<string> v;
    size_t index;
    bool apply = true, first = true;
    while (getline(file_read, line, '\n'))
    {
        if ((line.find("/*") != -1) && (line.find("*/") == -1)) {
            apply = false;
            if (!first) {
                line.insert(0, "\n");
            }
        } else if (line.find("*/") != -1) {
            apply = true;
            line.insert(0, "\n");
            line.insert(line.length(), "\n");
        } else if ((line.find("#include") != -1) || (line.find("#define") != -1) || (line.find("//") != -1) || !apply) {
            line.insert(0, "\n");
            line.insert(line.length(), "\n");
        } else {
            while ((index = line.find(", ")) != -1)
            {
                line.replace(index, 2, ",");
            }
            while ((index = line.find(" = ")) != -1)
            {
                line.replace(index, 3, "=");
            }
            while ((index = line.find("\t")) != -1)
            {
                line.erase(index, 1);
            }
            while ((index = line.find(" || ")) != -1)
            {
                line.replace(index, 4, "||");
            }
            while ((index = line.find(" && ")) != -1)
            {
                line.replace(index, 4, "&&");
            }
            while ((index = line.find("if (")) != -1)
            {
                line.replace(index, 4, "if(");
            }
     	}

        first = false;
        v.push_back(line);
    }
    file_read.close();

    ofstream file_write(argv[1]);
    for (string n : v)
    {
        file_write << n;
    }
    file_write.close();

    return EXIT_SUCCESS;
}
