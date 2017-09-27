#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: cleaner [file] [options]" << std::endl;
        std::cout << "Available options : -v (verbose)" << std::endl;
        return EXIT_FAILURE;
    }

    fstream file_read(argv[1]);
    if (!file_read.is_open())
    {
        std::cout << "Error: Can't find file " << argv[1] << "." << std::endl;
        return EXIT_FAILURE;
    }
    if (!strstr(argv[1], ".sqf"))
    {
        std::cout << "Error: The file must be be a .sqf extension file." << std::endl;
        return EXIT_FAILURE;
    }

    bool option_verbose;
    if (argv[2] && (strstr(argv[2], "-v"))) {
    	option_verbose = true;
    } else {
    	option_verbose = false;
    }

    string dico[11][2] =
    {
        {", ", ","},
        {" = ", "="},
        {"\t", "ERASE"},
        {" || ", "||"},
        {" && ", "&&"},
        {"if (", "if("},
        {" - ", "-"},
        {" + ", "+"},
        {" then", "then"},
        {"waitUntil ", "waitUntil"}
    };

    string line;
    vector<string> new_file_content;
    bool comment = false, apply_ac, last_special = false, first = true;
    while (getline(file_read, line, '\n'))
    {
        apply_ac = true;

        if ((line.find("/*") != -1) && (line.find("*/") == -1)) {
            comment = true;
        } else if (line.find("*/") != -1) {
            comment = false;
            apply_ac = false;
        } else if (((line.find("#include") != -1) || (line.find("#define") != -1) || (line.find("//") != -1)) && !comment) {
            if (!last_special && !first)
                line.insert(0, "\n");
            apply_ac = false;
            last_special = true;
        } else {
            last_special = false;
        }

        if (comment || !apply_ac) {
            line.insert(line.length(), "\n");
        } else {
            size_t pos;

            vector<size_t> positions;
            pos = line.find("\"", 0);
            while (pos != string::npos)
            {
                positions.push_back(pos);
                pos = line.find("\"", pos + 1);
            }

            for (int i = 0 ; i < (sizeof(dico) / sizeof(dico[0])) ; ++i)
            {
                pos = line.find(dico[i][0], 0);
                while (pos != string::npos)
                {
                    bool in_string = false;
                    for (int a = 0 ; a < positions.size() ; ++a)
                    {
                        if (positions[a] > pos)
                        {
                            if ((a % 2) == 1)
                            {
                                in_string = true;
                            }
                            break;
                        }
                    }

                    if (!in_string)
                    {
                        if (option_verbose)
                        {               
                            std::cout << "=========================" << std::endl;
                            std::cout << "Dico [" << dico[i][0] << "]" << std::endl;
                            std::cout << "Transformation [" << dico[i][1] << "]" << std::endl;
                            std::cout << "Old line : " << line << std::endl;
                        }

                        if (dico[i][1] == "ERASE")
                        {
                            line.erase(pos, 1);
                            pos = pos - 1;
                        } else {
                            line.replace(pos, dico[i][0].length(), dico[i][1]);
                        }

                        if (option_verbose)
                        {
                            std::cout << "New line : " << line << std::endl;
                            std::cout << "=========================" << std::endl;
                        }
                    }

                    pos = line.find(dico[i][0], pos + 1);
                }
            }
     	}

        new_file_content.push_back(line);
        first = false;
    }
    file_read.close();

    ofstream file_write(argv[1]);
    for (string n : new_file_content)
    {
        file_write << n;
    }
    file_write.close();

    return EXIT_SUCCESS;
}
