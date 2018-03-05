#include "downsize.hpp"
#include "trim.hpp"

int downsize(const std::string f_input, const std::string f_output)
{
    std::ifstream r_file(f_input, std::ios::out);
    if (!r_file.is_open())
    {
        std::cout << "Error: File " << f_input << "does not exist" << std::endl;
        return EXIT_FAILURE;
    }
    if ((f_input.find(".sqf") == std::string::npos) && (f_input.find(".hpp") == std::string::npos) && (f_input.find(".ext") == std::string::npos))
    {
        std::cout << "Error: File extension is not supported" << std::endl;
        r_file.close();
        return EXIT_FAILURE;
    }

    std::map<std::string, std::string> dic_map = {
        {", ", ","},
        {" > ", ">"},{" < ", "<"},
        {" = ", "="},
        {" != ", "!="},
        {" || ", "||"},
        {" && ", "&&"},
        {"if (", "if("},
        {" - ", "-"},
        {" +", "+"},{"+ ", "+"},
        {" then ", "then"},{" then", "then"},
        {"waitUntil ", "waitUntil"},
        {" {", "{"},{"} ", "}"},
        {" exitWith ", "exitWith"},{" exitWith", "exitWith"},
        {": ", ":"},
        {"\n", ""},
        {"\r", ""},
        {"\t", ""}
    };

    std::string line;
    std::vector<std::string> content;
    bool header = false;
    while (getline(r_file, line))
    {
        const std::string s_trim = trim(line);

        if (s_trim[0] == '/' && s_trim[1] == '*') {
            header = true;
        } else if (s_trim[0] == '*' && s_trim[1] == '/') {
            header = false;
            line = line + '\n';
        }

        if (header) {
            line = line + '\n';
        } else if (s_trim[0] != '*' && s_trim[1] != '/' && s_trim[1] != '#') {
            size_t pos;
            unsigned int deletion = 0;
            std::vector<size_t> positions;
            pos = line.find("\"", 0);
            while (pos != std::string::npos)
            {
                positions.push_back(pos);
                pos = line.find("\"", pos + 1);
            }

            for (auto const &x : dic_map)
            {
                pos = line.find(x.first, 0);
                while (pos != std::string::npos)
                {
                    bool removed = false;
                    // std::cout << "--------------------------------" << std::endl;
                    // std::cout << x.first << " | position :" << pos << std::endl;
                    bool in_string = false;
                    for (unsigned int a = 0 ; a < positions.size() ; ++a)
                    {
                        if ((positions[a] - deletion) > pos)
                        {
                            // std::cout << "next string found :" << positions[a] - deletion << std::endl;
                            if ((a % 2) == 1) {
                                // std::cout << "is in string" << std::endl;
                                in_string = true;
                            }
                            break;
                        }
                    }

                    // std::cout << "before : [" << line << "]" << std::endl;
                    if (!in_string)
                    {
                        if (x.second.empty())
                        {
                            line.erase(pos, 1);
                            deletion++;
                            removed = true;
                        } else {
                            line.replace(pos, x.first.length(), x.second);
                        }
                    }
                    // std::cout << "after : [" << line << "]" << std::endl;
                    // std::cout << "remove count : " << deletion << std::endl;

                    pos = line.find(x.first, removed ? pos : pos + 1);
                }
            }
        }

        if (!(line[0] == '/' && !header)) {
            content.push_back(line);
        }
    }

    r_file.close();

    std::ofstream w_file(f_output, std::ios::in | std::ios::trunc);
    for (std::string n : content) {
        w_file << n;
    }
    w_file.close();

    return EXIT_SUCCESS;
}
