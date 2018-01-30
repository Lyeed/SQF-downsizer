#include "downsize.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: cleaner [source_file] [dest_file]" << std::endl;
        return EXIT_FAILURE;
    }
    return downsize(argv[1], argv[2]);
}
