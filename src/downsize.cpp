#include "downsize.hpp"
#include "trim.hpp"

static std::map<std::string, std::string> dic_map = {
    {", ", ","},
    {" >", ">"},{"> ", ">"},
    {" < ", "<"}, {"<  ", "<"},
    {" = ", "="},
    {" != ", "!="},
    {" || ", "||"},
    {" && ", "&&"},
    {" (", "("},
    {") ", ")"},
    {" -", "-"},{"- ", "-"},
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

static std::string downsize_line(std::string line)
{
    static bool header = false;
    static bool first_header = false;
    std::string s_trim = trim(line);
    if (s_trim.find("/*") != std::string::npos)
    {
        if (first_header) {
            line = '\n'+ line;            
        }
        if (s_trim.find("*/") == std::string::npos) {
            header = true;
        }
        first_header = true;
    } else if ((s_trim.find("*/") != std::string::npos) && header) {            
        header = false;
        line = line + '\n';
    } else if ((s_trim.find("//") != std::string::npos) || (s_trim[0] == '#')) {
        line = line + '\n';
    } else {
        if (header) {
            line = line + '\n';
        } else {
            line = s_trim;
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
                    bool in_string = false;
                    for (unsigned int a = 0 ; a < positions.size() ; ++a)
                    {
                        if ((positions[a] - deletion) > pos)
                        {
                            if ((a % 2) == 1) {
                                in_string = true;
                            }
                            break;
                        }
                    }

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

                    pos = line.find(x.first, removed ? pos : pos + 1);
                }
            }
        }
    }
    return line;
}

int downsize(const std::string f_input, const std::string f_output)
{
    std::ifstream r_file(f_input, std::ios::out);
    if (!r_file.is_open()) {
        std::cout << "Error: File " << f_input << " does not exist" << std::endl;
        return EXIT_FAILURE;
    }
    if (
            (f_input.find(".sqf") == std::string::npos) &&
            (f_input.find(".hpp") == std::string::npos) &&
            (f_input.find(".ext") == std::string::npos) &&
            (f_input.find(".cpp") == std::string::npos)
        ) {
        std::cout << "Error: File extension is not supported" << std::endl;
        r_file.close();
        return EXIT_FAILURE;
    }

    std::string line;
    std::vector<std::string> content;
    while (getline(r_file, line)) {
        content.push_back(downsize_line(line));
    }
    r_file.close();

    std::ofstream w_file(f_output, std::ios::in | std::ios::trunc);
    for (std::string n : content) {
        w_file << n;
    }
    w_file.close();

    return EXIT_SUCCESS;
}
