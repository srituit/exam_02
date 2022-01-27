#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int j;
    int alpha[128];

    if (argc == 3)
    {
        i = 0;
        while (i < 128)
            alpha[i++] = 0;
        i = 1;
        while (i < argc)
        {
            j = 0;
            while (argv[i][j])
            {
                if (alpha[(int)argv[i][j]] == 0)
                {
                    alpha[(int)argv[i][j]] = 1;
                    write(1, &argv[i][j], 1);
                }
                j++;
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}