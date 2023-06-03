#include <stdio.h>      // ?
#include <stdlib.h>     // ?
#include <time.h>       // ?
#include <string.h>     // ?
#include <unistd.h>     // ?
#include <fcntl.h>      // ?

#include <ctype.h>      // isdigit(3) <-- implement my_isdigit(3)
#include <stdbool.h>    // bool typedef

#define ROUND_LEN   11
#define CODE_LEN    4
#define READ_LEN    5
// #define LINE_LEN    (READ_LEN + 1)
// change naming conv (user/code (buf))

//*(buf)++; ! (*buf)++
// void print_char_buf(char* buf, int size)
// {
//     printf("[ ");
//     while (size--)
//     printf(size == 0 ? "\'%c\'" : "\'%c\', ", *buf++);
//     printf(" ]\n");
// }

// Generate random code if none specified
void generate_code(char* code) 
{
    if (!code[0])// if (code[0] == 0)
    {
        for (int round = 0; round < CODE_LEN; round++) 
        {
            code[round] = rand() % 10 + '0';
        }
    }// mv to own function simplicity!!!
    //printf("Random code: "); // debug! to be removed
    //print_char_buf(code, CODE_LEN); // debug! to be removed
}

// handles wrong inputs (too long or too short) 
// Check for invalid input
void check_user_input(bool* valid_input, char input)
{
    if (valid_input == false || input != '\n') 
    {
        if (input != '\n')
            printf("Invalid input, please enter a %d digit number\n", CODE_LEN);
        while (input != '\n')
        {
            // \n is end of user input (when user press enter => \n is sent to read)
            read(0, &input, 1);
        }
        *valid_input = false; // * <-- to deref
        printf("Wrong input!\n");
        // continue;//<-- bad design? not executed in if?
    }
}

void print_result(int well_placed, int misplaced)
{
    printf( "Well placed pieces: %d\n" 
              "Misplaced pieces: %d\n", 
               well_placed, misplaced);
}

bool iswin(int well_placed) 
{
    if (well_placed == CODE_LEN) 
    {
        printf("Congratz! You did it!\n");
        return true;
    }
    return false;
}

// Check for well-placed and misplaced pieces
void check_placing(char* guess, char* code, int* well_placed, int* misplaced)
{
    int used[CODE_LEN];
    for (int i = 0; i < CODE_LEN; i++)
    {
        used[i] = 0;
    }

    for (int i = 0; i < CODE_LEN; i++)
    {
        if (guess[i] == code[i])
        {
            (*well_placed) += 1;
            used[i] = 1;
        }
        else
        {
            for (int j = 0; j < CODE_LEN; j++)
            {
                if (guess[i] == code[j] && !used[j])
                {
                    (*misplaced) += 1;
                    used[j] = 1;
                    break;
                }
            }
        }
    }
}


int main(int argc, char **argv)
{
    (void)argc; (void)argv;
    // code non-init might be random memory values
    // code = [123402983, 0, 0, 2343434, 0023434] not initialized
    char code[CODE_LEN + 1] = {0}, input = '0';
    int rounds = ROUND_LEN, round = 1, index = 0, well_placed, misplaced;
    // ! bool guess2short = false;
    bool valid_input = true;
    // ssize_t => signed long int (nb_bytes_read with -1 as error)
    ssize_t nbytes;
    // man setbuf(3)
    setbuf(stdout, NULL);
    srand(time(NULL));

    // Handle command line arguments
    int opt;
    // check if '-' -> switch to option mode and check if valid option
    // else handle wrong input
    while ((opt = getopt(argc, argv, "c:t:")) != -1)// can't use getopt!!!!
    {
        switch (opt) 
        {
            case 'c':
                strncpy(code, optarg, CODE_LEN);
                break;
            case 't':
                rounds = atoi(optarg);
                break;
        }
    }
    generate_code(code);
    // Print intro
    // void greet_user(void);
    printf( "Will you find the secret code?\n" 
            "Please enter a valid guess\n");

    //  Conditional statement for each attempt
    while (round < rounds && !iswin(well_placed)) 
    {
        char guess[READ_LEN + 1] = {0};// '\0'<-- not good? + cREAD_LEN vs CODE..
        valid_input = true;
        well_placed = 0, misplaced = 0;
        // Get guess from user
        // printf("rounds %d\n", rounds);
        // printf("Guess: %s\n", guess);
        if (valid_input == true)
        {
            printf("Round %d\n", round);
        }
        printf("> ");//STDIN_FILENO
        // (void)read(0, guess, sizeof(guess)-1);// read 4 no matter
        input = '0';
        index = 0;
        // while (index < CODE_LEN) {
        valid_input = true;
        while (index < READ_LEN) { // ['0', '2', '2', '3', '\n', '\0']
            if (isdigit(input) == false)
            {   // \n
                // break; && continue; ?
                valid_input = false;
                break;
            }
            nbytes = read(0, &input, 1);
            if (nbytes == 0)
            {//read more than 1by1 of strcmp("exit")
                printf("exit\n");
                return EXIT_SUCCESS;// return 0;
            }
            if (nbytes == -1)
            {
                printf("error: read(2)\n");//make errno/err... fn
                return EXIT_FAILURE;// return 1;
            }
            guess[index] = input;// <-- should be '\n'
            index += 1;
        }

        check_user_input(&valid_input, input);
        if (valid_input == false)
            continue;
        
        //sizeof operator less efficient here!
        //print_char_buf(guess, sizeof(guess));
        
        check_placing(guess, code, &well_placed, &misplaced);
        if (iswin(well_placed) == true) 
        {
            return EXIT_SUCCESS;
        }
        print_result(well_placed, misplaced);
        round += 1;
    }
}