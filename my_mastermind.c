#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_ATTEMPTS 10
#define CODE_LENGTH 4

int main(int argc, char **argv) 
{
    char secret_code[CODE_LENGTH + 1];
    int attempts = MAX_ATTEMPTS;

    srand(time(NULL));

    // Handle command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "c:t:")) != -1) 
    {
        switch (opt) 
        {
            case 'c':
                strncpy(secret_code, optarg, CODE_LENGTH);
                break;
            case 't':
                attempts = atoi(optarg);
                break;
        }
    }

    // Generate random code if none was specified
    if (!secret_code[0]) 
    {
        for (int i = 0; i < CODE_LENGTH; i++) 
        {
            secret_code[i] = rand() % 10 + '0';
        }
    }

    // Print introduction
    printf("Will you find the secret code?\n");
    printf("Please enter a valid guess\n");

    // Loop for each attempt
    for (int i = 0; i < attempts; i++) 
    {
        char guess[CODE_LENGTH + 1];
        int well_placed = 0, misplaced = 0;

        // Get guess from user
        printf("Round %d\n", i + 1);
        printf("> ");

        int bytes_read = read(STDIN_FILENO, guess, sizeof(guess)-1);
            if(bytes_read <= 0)
            {
                printf("\n");
                break;                
            }

        for(int j = 0; j < bytes_read; j++)
        {
               if (strlen(guess) != CODE_LENGTH) 
        {
        // Print result
        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);

        }        

        // Check for invalid input
        if (strlen(guess) != CODE_LENGTH) 
        {
           // Print result
            printf("Well placed pieces: %d\n", well_placed);
            printf("Misplaced pieces: %d\n", misplaced);
            continue;
        }
        }

        // Check for well-placed and misplaced pieces
            for(int j = 0; j < bytes_read; j++)
        {
               if (strlen(guess) != CODE_LENGTH) 
        {
        // Print result
        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);

        }        

        //Check for invalid input
        // int fd = open("input_string", O_RDONLY);
        // int bytes_read = 0;

        // bytes_read = read(fd, guess, CODE_LENGTH);

        // if (bytes_read != CODE_LENGTH) 
        // {
        // // Print result
        //     printf("Well placed pieces: %d\n", well_placed);
        //     printf("Misplaced pieces: %d\n", misplaced);
        // continue;
        // }


        // Check for well-placed and misplaced pieces
        for (int j = 0; j < CODE_LENGTH; j++) 
        {
            if (guess[j] == secret_code[j]) 
            {
                well_placed++;
            } else {
                for (int k = 0; k < CODE_LENGTH; k++) 
                {
                    if (guess[j] == secret_code[k]) 
                    {
                        misplaced++;
                        break;
                    }
                }
            }
        }

        // Check for win
        if (well_placed == CODE_LENGTH) 
        {
            printf("Congratz! You did it!\n");
            return 0;
        }

        //Print result
        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);

    }
    }
};