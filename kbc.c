#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <time.h> 
#include <unistd.h> 



// Function Declarations : 

void storeByLevel(int n, char l[n][6][150], FILE *fp); 
// Stores all questions of a level into their corresponding arrays from the question bank. 

int randomN(int n); 
// Generates a random number less than n 

void start(char money[15][12], char name[150]); 
// Prints the rules and general information at the beginning of the game 

void header(); 
// Logo

void printRandomQ(int n, char l[n][6][150], int st[n]); 
// Prints a question at random from the given difficulty level, as long as that question 
// has not yet been asked 

int displayQ(int n, char l[n][6][150], int st[n], int f[2][2], int num, char w[12], char ch[2]); 
// Displays a question and checks its answer by calling printRandomQ and checkA 

int checkA(int n, char l[n][6][150], int st[n], int f[2][2], char ans, int num, char w[12], char ch[2]); 
// Checks the answer and calls life50 and lifeFlip or itself recursively 

void life50(int n, char l[n][6][150], int num, char ch[2]); 
// For the 50 - 50 lifeline 

void lifeFlip(int n, char l[n][6][150], int st[n], int f[2][2], int num, char w[12], char ch[2]); 
// For the 'Flip the Question' lifeline 

void displayG(int f[2][2], int num, char w[12]); 
// Displays general instructions and lifeline status before any question is printed 

void questionCall(int n, char l[n][6][150], int st[n], int f[2][2], int* endCheck, char money[15][12], char w[12], char name[150], char ch[2]); 
// Displays the questions one after the other (level - wise) if the answer is correct 

void pressAnyKey(); 
// To press a key and progress without having to hit enter 

void end(int f[2][2], char w[12]); 
// Displays information at the end of the program 



int ind; 
// A global integer variable that stores the index number of the question being 
// displayed and checked 
int flag = 0; 
// Flag used in case the player quits the game 
int flagl = 0; 
// Flag used in case the 50 - 50 lifeline has been used 
// 
// These int variables are made global to reduce code complexity and prevent having to pass 
// pointers and pointers to pointers throughout. 



void main() 
{ 
    int n1, n2, n3; 
    n1 = 50; // 50 questions have been taken for the first level. 
    n2 = 40; // 40 questions have been taken for the first level.
    n3 = 20; // 20 questions have been taken for the first level. 

    char l1[n1][6][150], l2[n2][6][150], l3[n3][6][150]; 
    // 
    // Three dimensional arrays are created for each level of difficulty. 
    // Each question's array has 6 elements : the question, 4 options and the 
    // option number of the correct option. 

    FILE *fp; 
    fp = fopen("questions.csv", "r"); 
    // 
    // Opens the file questions.csv which is the question bank for this quiz 
    // The questions have been already saved in order of difficulty and hence there 
    // was no need to use an extra field to save a marker for the difficulty level. 

    if (fp == NULL) 
    { 
        printf ("Error"); 
    }
    
    storeByLevel(n1, l1, fp); 
    storeByLevel(n2, l2, fp); 
    storeByLevel(n3, l3, fp); 

    fclose(fp); 
    // 
    // Once all the questions have been stored into their respective arrays, the stream 
    // can be closed. 

    int st1[n1], st2[n2], st3[n3]; 
    char money[15][12] = {"1,000", "3,000", "5,000", "10,000", "20,000", "40,000", "80,000", "1,60,000", "3,20,000", "6,40,000", "12,50,000", "25,00,000", "50,00,000", "1,00,00,000", "5,00,00,000"}; 


    int lifelines[2][2]; // Stores the status of the lifelines 
    lifelines[0][0] = 1; 
    lifelines[1][0] = 1; 
    // 
    // These are set to 1 to indicate that 1 of each kind of lifeline is available 
    // at the start of the quiz. 
    // lifeline[0][1] will store the question number where the 50 - 50 lifeline is used, 
    // whenever it is used and lifeline[1][1] will store the question number where the 
    // 'Flip the Question' lifeline is used whenever it is used. 

    char ch[2]; 
    int endCheck = 1; 
    char name[150]; 

    start(money, name); 

    char winnings[12] = "0"; 

    questionCall(n1, l1, st1, lifelines, &endCheck, money, winnings, name, ch); 
    if (endCheck == 1)
    { 
        questionCall(n2, l2, st2, lifelines, &endCheck, money, winnings, name, ch); 
    }
    if (endCheck == 1)
    { 
        questionCall(n3, l3, st3, lifelines, &endCheck, money, winnings, name, ch); 
    } 
} 



// Function Definitions : 

void storeByLevel(int n, char l[n][6][150], FILE *fp) 
{ 
    // Stores all questions of a level into their corresponding arrays from the question bank 

    for (int i = 0; i < n; i++) 
    { 
        char temp[250]; 
        // Temporary array to store each line from the .csv file without seprating the elements
        fgets(temp, 250, fp); 

        char* point = strtok(temp, ","); 
        // The strtok function in string.h is used to divide the line using the comma delimiter. 

        int j = 0; 
        while (point != NULL) 
        { 
            strcpy (l[i][j], point); 
            // Copies each element of the line into the array at the correct position 

            j++; 
            point = strtok(NULL, ","); 
        } 
    } 
} 

int randomN(int n) 
{ 
    // Generates a random number less than n 

    int r = rand() % n; 
    // The n factor makes sure that the random number generated is from 0 to n. 
    return r; 
} 

void start(char money[15][12], char name[150]) 
{ 
    // Prints the rules and general information at the beginning of the game 
    
    system ("clear"); // Clear screen function in stdlib.h
    printf ("\n \n \n"); 

    printf("oooo    oooo       .o.       ooooo     ooo ooooo      ooo       oooooooooo.        .o.       ooooo      ooo oooooooooooo   .oooooo.          .o\n");
    printf("`888   .8P'       .888.      `888'     `8' `888b.     `8'       `888'   `Y8b      .888.      `888b.     `8' `888'     `8  d8P'  `Y8b        .888. \n");
    printf(" 888  d8'        .8\"888.      888       8   8 `88b.    8         888     888     .8\"888.      8 `88b.    8   888         888               .8\"888.  \n");
    printf(" 88888[         .8' `888.     888       8   8   `88b.  8         888oooo888'    .8' `888.     8   `88b.  8   888oooo8    888              .8' `888.\n");
    printf(" 888`88b.      .88ooo8888.    888       8   8     `88b.8         888    `88b   .88ooo8888.    8     `88b.8   888    \"    888     ooooo   .88ooo8888.\n");
    printf(" 888  `88b.   .8'     `888.   `88.    .8'   8       `888         888    .88P  .8'     `888.   8       `888   888       o `88.    .88'   .8'     `888.\n");
    printf("o888o  o888o o88o     o8888o    `YbodP'    o8o        `8        o888bood8P'  o88o     o8888o o8o        `8  o888ooooood8  `Y8bood8P'   o88o     o8888o\n\n\n");
   
    printf("                .oooooo.   ooooooooo.     .oooooo.   ooooooooo.   oooooooooooo ooooooooo.         .o.       ooooooooooooo ooooo\n");
    printf("               d8P'  `Y8b  `888   `Y88.  d8P'  `Y8b  `888   `Y88. `888'     `8 `888   `Y88.      .888.      8'   888   `8 `888'\n");
    printf("              888           888   .d88' 888      888  888   .d88'  888          888   .d88'     .8\"888.          888       888\n");
    printf("              888           888ooo88P'  888      888  888ooo88P'   888oooo8     888ooo88P'     .8' `888.         888       888\n");
    printf("              888           888`88b.    888      888  888`88b.     888    \"     888           .88ooo8888.        888       888\n");
    printf("              `88b    ooo   888  `88b.  `88b    d88'  888  `88b.   888       o  888          .8'     `888.       888       888\n");
    printf("               `Y8bood8P'  o888o  o888o  `Y8bood8P'  o888o  o888o o888ooooood8 o888o        o88o     o8888o     o888o     o888o\n \n \n");
    sleep(1); 

    printf ("Get ready to play a game for the kind of life changing money that most of us just dream about.\n\nWelcome to KAUN BANEGA CROREPATI! \n\n"); 
    printf ("KAUN BANEGA CROREPATI is a game based on the U.K. show 'Who Wants To Be A Millionaire?'. \n\n"); 
    printf ("Press any key to continue : "); 
    pressAnyKey(); 
    printf ("\n\nHere is what you are up against : 15 questions with increasing money values from 1,000 all the way up to 5 crores.\n"); 
    printf ("The money won after each question is roughly doubled from the previous amount won until the player reaches the \n"); 
    printf ("final question, where they can win the maximum prize of 5 crores.\n\n"); 
    printf ("    QUESTION -- PRIZE MONEY\n");

    for(int i = 15; i > 0; i--) 
    { 
        printf ("    %8d -- %s\n", i, money[i - 1]);
    } 

    printf ("\n\nPress any key to continue : "); 
    pressAnyKey(); 
    printf ("\n\nRULES : \n1) Every question has four options A/B/C/D and only the option number must be entered "); 
    printf ("(A/B/C/D) corresponding to the chosen option.\n2) Answering each question correctly will advance the player to the next level. \n"); 
    printf ("3) There is no time limit for the player to come up with an answer.\n"); 
    printf ("4) The player can quit the game anytime after a question is displayed with the money he/she has earned up to that point.\n"); 
    printf ("5) After submitting an answer, the player will not be allowed to change the answer.\n"); 
    printf ("6) If the player gives an incorrect answer, the prize money will be reduced to zero or to the intermediate level.\n"); 
    printf ("   The intermediate levels are 20,000 (at question 5) and 6,40,000 (at question 10).\n"); 
    printf ("7) There are two lifelines : 50 - 50 and 'Flip the Question'. \n\ta) 50 - 50 \n\t   Two wrong answers are removed from the question\n\t"); 
    printf ("   leaving one right and one wrong answer.\n\tb) 'Flip the Question' \n\t"); 
    printf ("   The current question is thrown - out and replaced with a new question.\n\t"); 
    printf ("   Any lifelines expended on the original question remain expended.\n\tThe player can use lifelines at any point during the game.\n\t"); 
    printf ("Each lifeline can only be used once (even at the same time). "); 
    printf ("\n\nLet's give it a go!\n\nWhat is your name?\n"); 
    // scanf("%[^\n]",name); 
    for (int i = 0; i < 150; i++) 
    { 
        scanf ("%c", &name[i]); 
        if (name[i] == '\n') 
        { 
            name[i] = '\0'; 
            break; 
        }
    } 
    // 
    // This method of saving the string is used instead of scanf ("%s", name) as with %s, 
    // scanf reads only till a space (' ') character. 
} 

void header() 
{ 
    // Logo 

    printf("_  _ ____ _  _ _  _       ___  ____ _  _ ____ ____ ____       ____ ____ ____ ____ ____ ___  ____ ___ _ \n");
    printf("|_/  |__| |  | |\\ |       |__] |__| |\\ | |___ | __ |__|       |    |__/ |  | |__/ |___ |__] |__|  |  | \n");
    printf("| \\_ |  | |__| | \\|       |__] |  | | \\| |___ |__] |  |       |___ |  \\ |__| |  \\ |___ |    |  |  |  | \n\n\n"); 
}

void printRandomQ(int n, char l[n][6][150], int st[n]) 
{ 
    // Prints a question at random from the given difficulty level, as long as that question 
    // has not yet been asked 

    while (1) 
    { 
        srand(time(0)); 
        // 
        // This creates a new seed for the random function each time it is called 
        // so that a new random number is generated each time, otherwise the same 
        // number is generated and hence the same question will be displayed. 
        ind = randomN(n); 
        if (st[ind] != 1) 
        { 
            break; 
        }
    } 
    printf ("%s \n", l[ind][0]); 
    // Prints the question 

    printf ("A. %s \n", l[ind][1]); 
    printf ("B. %s \n", l[ind][2]); 
    printf ("C. %s \n", l[ind][3]); 
    printf ("D. %s \n", l[ind][4]); 
    // Prints the options 

    st[ind] = 1; 
    // 
    // Marker to indicate that this question has already been asked in the game 
    // The if statement before makes sure that using this marker, only questions 
    // that have not already been asked are used in the quiz. 
} 

int displayQ(int n, char l[n][6][150], int st[n], int f[2][2], int num, char w[12], char ch[2]) 
{ 
    // Displays a question and checks its answer by calling printRandomQ and checkA 
    
    char ans; 

    printf ("Q.%d ", num); 
    printRandomQ(n, l, st); 
    printf ("\nEnter your answer : "); 
    scanf (" %c", &ans); 

    int a = checkA(n, l, st, f, ans, num, w, ch); 
    return a; 
} 

int checkA(int n, char l[n][6][150], int st[n], int f[2][2], char ans, int num, char w[12], char ch[2]) 
{ 
    // Checks the answer and calls life50 and lifeFlip or itself recursively 
    
    if (ans == '1') 
    { 
        if (flag != 1) 
        { 
            if (f[0][0] == 1) 
            { 
                
                flagl = 1; 
                f[0][0] = 0; 
                f[0][1] = num; 
                // The 50 - 50 lifeline cannot be used again. 

                system ("clear"); // Clear screen function in stdlib.h 
                displayG(f, num, w); 
                life50(n, l, num, ch); 
                if (f[1][0] != 0) 
                { 
                    printf ("Enter your answer or use an available lifeline : "); 
                } 
                else 
                { 
                    printf ("Enter your answer : "); 
                } 
                scanf (" %c", &ans); 
                checkA(n, l, st, f, ans, num, w, ch); 
            } 
            else // If lifeline[0][0] == 0
            { 
                printf ("\nYou have already used your '50 - 50' lifeline in question %d. \n", f[0][1]); 
                if (f[1][0] != 0) 
                { 
                    printf ("Enter your answer or use an available lifeline : "); 
                } 
                else 
                { 
                    printf ("Enter your answer : "); 
                } 
                scanf (" %c", &ans); 
                checkA(n, l, st, f, ans, num, w, ch); 
            }
        } 
        else // If the player chooses to withdraw from the game 
        { 
            printf ("\nPlease enter a valid answer : "); 
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        }
    }    
    else if (ans == '2') 
    { 
        if (flag != 1 && flagl != 1) 
        { 
            if (f[1][0] == 1) 
            { 
                f[1][0] = 0; 
                f[1][1] = num; 
                // The 'Flip the Question' lifeline cannot be used again. 

                lifeFlip(n, l, st, f, num, w, ch); 
            } 
            else // If lifeline[1][0] == 0
            { 
                printf ("\nYou have already used your 'Flip the Question' lifeline in question %d. \n", f[1][1]); 
                if (f[0][0] != 0) 
                { 
                    printf ("Enter your answer or use an available lifeline : "); 
                } 
                else 
                { 
                    printf ("Enter your answer : "); 
                } 
                scanf (" %c", &ans); 
                checkA(n, l, st, f, ans, num, w, ch); 
            }
        } 
        else if (flag != 1 && flagl == 1) 
        { 
            flagl = 0; 
            if (f[1][0] == 1) 
            { 
                f[1][0] = 0; 
                f[1][1] = num; 
                // The 'Flip the Question' lifeline cannot be used again. 

                lifeFlip(n, l, st, f, num, w, ch); 
            } 
            else // If lifeline[1][0] == 0
            { 
                printf ("\nYou have already used your 'Flip the Question' lifeline in question %d. \n", f[1][1]); 
                if (f[0][0] != 0) 
                { 
                    printf ("Enter your answer or use an available lifeline : "); 
                } 
                else 
                { 
                    printf ("Enter your answer : "); 
                } 
                scanf (" %c", &ans); 
                checkA(n, l, st, f, ans, num, w, ch); 
            }
        }
        else // If the player chooses to withdraw from the game 
        { 
            printf ("\nPlease enter a valid answer : "); 
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        }
    } 
    else if (ans == 'Q' || ans == 'q') // If the player chooses to withdraw from the game 
    {
        if (flag != 1) 
        { 
            printf ("You have withdrawn from the game. Now guess an option : "); 
            // 
            // The player can now answer the question but their answer will be of no consequence 
            // and will not change the amount of money they have won. 
            scanf (" %c", &ans); 
            // 
            // The extra space before %c tells scanf to ignore and new line characters or 
            // spaces and to not store these in ans. 

            flag = 1;  
            checkA(n, l, st, f, ans, num, w, ch); 
        } 
        else 
        { 
            printf ("\nYou have already quit. Please enter a valid answer : "); 
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        }
    } 
    else if (ans == l[ind][5][0] || ans == (l[ind][5][0] + 32)) // Uppercase or lowercase
    { 
        printf ("\nCongratulations! Your answer is correct! \n"); 
        return 1; 
    } 
    else if (flagl != 1 && ans != 'a' && ans != 'b' && ans != 'c' && ans != 'd' && ans != 'A' && ans != 'B' && ans != 'C' && ans != 'D') 
    { 
        // If any character other than a, b, c, d in uppercase or lowercase is entered given that 
        // the 50 - 50 lifeline has not been used 

        if (flag != 1) 
        { 
            if ((f[0][0] + f[1][0] != 0)) 
            { 
                printf ("\nPlease enter a valid answer or use an available lifeline : "); 
            } 
            else 
            { 
                printf ("\nPlease enter a vaild answer : "); 
            }
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        } 
        else // If the player chooses to withdraw from the game 
        { 
            printf ("\nPlease enter a valid answer : "); 
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        }
    } 
    else if (flagl == 1 && ans != ch[0] && ans != ch[1] && ans != (ch[0] + 32) && ans != (ch[1] + 32)) 
    { 
        if (flag != 1) 
        { 
            if ((f[0][0] + f[1][0] != 0)) 
            { 
                printf ("\nPlease enter a valid answer or use an available lifeline : "); 
            } 
            else 
            { 
                printf ("\nPlease enter a vaild answer : "); 
            } 
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        } 
        else // If the player chooses to withdraw from the game 
        { 
            printf ("\nPlease enter a valid answer : "); 
            scanf (" %c", &ans); 
            checkA(n, l, st, f, ans, num, w, ch); 
        } 
    } 
    else 
    { 
        printf ("\nUnfortunately, your answer is incorrect. \n"); 
        printf ("The correct answer is : %c \n", l[ind][5][0]); 
        return 0; 
    } 
} 

void life50(int n, char l[n][6][150], int num, char ch[2]) 
{ 
    // For the 50 - 50 lifeline 

    printf("\nThe options after applying your 50 - 50 lifeline are : "); 
    ch[0] = l[ind][5][0]; 

    while(1)
    {
        int x = randomN(3);
        switch (x)
        {
            case 0 : ch[1] = 'A';
              break;
            case 1 : ch[1] = 'B';
              break;
            case 2 : ch[1] = 'C';
              break;
            case 3 : ch[1] = 'D';
              break;
        }
        if (ch[1] != ch[0]) 
        { 
            break; 
        } 
    } 

    if (ch[0] < ch[1]) 
    { 
        printf ("(Please enter either option %c or option %c) \n ", ch[0], ch[1]); 
    } 
    else 
    { 
        printf ("(Please enter either option %c or option %c) \n ", ch[1], ch[0]); 
    } 
    printf ("\n"); 
    printf ("Q.%d ", num); 
    printf("%s \n", l[ind][0]); 

    if (ch[0] < ch[1])
    {
        switch (ch[0])
        { 
          case 'A' : printf("A. %s \n", l[ind][1]);
            break;
          case 'B' : printf("B. %s \n", l[ind][2]);
            break;
          case 'C' : printf("C. %s \n", l[ind][3]);
            break;
          case 'D' : printf("D. %s \n", l[ind][4]);
            break;
          default: printf("hello");
        }
        switch (ch[1])
        {
          case 'A' : printf("A. %s \n", l[ind][1]);
            break;
          case 'B' : printf("B. %s \n", l[ind][2]);
            break;
          case 'C' : printf("C. %s \n", l[ind][3]);
            break;
          case 'D' : printf("D. %s \n", l[ind][4]);
            break;
        }
    }
    else
    {
        switch (ch[1])
        {
          case 'A' : printf("A. %s \n", l[ind][1]);
            break;
          case 'B' : printf("B. %s \n", l[ind][2]);
            break;
          case 'C' : printf("C. %s \n", l[ind][3]);
            break;
          case 'D' : printf("D. %s \n", l[ind][4]);
            break;
        }
        switch (ch[0])
        { 
          case 'A' : printf("A. %s \n", l[ind][1]);
            break;
          case 'B' : printf("B. %s \n", l[ind][2]);
            break;
          case 'C' : printf("C. %s \n", l[ind][3]);
            break;
          case 'D' : printf("D. %s \n", l[ind][4]);
            break;
          default: printf("hello");
        }
    } 
} 

void lifeFlip(int n, char l[n][6][150], int st[n], int f[2][2], int num, char w[12], char ch[2]) 
{ 
    // For the 'Flip the Question' lifeline 
    
    system ("clear"); // Clear screen function in stdlib.h 
    displayG(f, num, w); 
    printf ("\nYour new question is : \n \n"); 
    displayQ(n, l, st, f, num, w, ch); 
} 

void displayG(int f[2][2], int num, char w[12]) 
{ 
    // Displays general instructions and lifeline status before any question is printed 

    header(); 


    printf ("Level : %d                     Current winnings : I.N.R. %s \n", num, w); 
    if (flagl != 1) 
    { 
        printf ("\nPlease enter only an option number (A/B/C/D) as your answer or enter Q to quit. \n \n"); 
    } 
    else 
    { 
        printf ("\nEnter Q to quit. \n \n"); 
    }
    printf ("Remaining lifelines : %d \n \n", (f[0][0] + f[1][0])); 
    
    printf ("50 - 50 Lifeline : "); 
    if (f[0][0] == 1) 
    { 
        printf ("Unused (Enter 1 to use)          "); 
    } 
    else 
    { 
        printf ("Used in question %d              ", f[0][1]); 
    } 

    printf ("'Flip the Question' Lifeline : "); 
    if (f[1][0] == 1) 
    { 
        printf ("Unused (Enter 2 to use) \n"); 
    } 
    else 
    { 
        printf ("Used in question %d\n", f[1][1]); 
    } 
    printf ("\n \n"); 
} 

void questionCall(int n, char l[n][6][150], int st[n], int f[2][2], int* endCheck, char money[15][12], char w[12], char name[150], char ch[2]) 
{ 
    // Displays the questions one after the other (level - wise) if the answer is correct 

    int check = 0; // Stores the return value of the displayQ function 
    int ctr = 0 ; // To differentiate between the 3 levels 

    if (n == 50) // First difficulty level 
    { 
        ctr = 0; 
    } 
    else if (n == 40) // Second difficulty level 
    { 
        ctr = 5; 
    } 
    else if (n == 20) // Third difficulty level 
    { 
        ctr = 10; 
    } 

    int i = 0; 
    int num; 

    for(i = 0; i < 5; i++)
    { 
        num = i + ctr + 1; 

        if (num == 1) 
        { 
            printf("\nLet's start the game %s! \n", name); 
            printf ("Press any key : "); 
            pressAnyKey(); 
        } 
        else 
        { 
            printf ("Press any key for question %d : ", num); 
            getchar(); 
            pressAnyKey(); 
        } 

        displayG(f, num, w); 
        check = displayQ(n, l, st, f, num, w, ch); 
        flagl = 0; 

        if (flag == 1) // The player wishes to withdraw from the game. 
        {
            if (strcmp(w, "0") == 0) 
            { 
                printf ("Press any key : "); 
                getchar(); 
                pressAnyKey(); 
                header(); 
                printf ("\nSorry %s. Unfortunately, have not won any money. Better luck next time. \n", name, w); 
            } 
            else 
            { 
                printf ("Press any key : "); 
                getchar(); 
                pressAnyKey(); 
                header(); 
                printf ("\nCongratulations %s! After withdrawing, you have won %s rupees! \n", name, w); 
            }
            *endCheck = 0; 
            break; 
        } 
        else if (check == 1) // The answer the player has entered is correct. 
        { 
            strcpy (w, money[i + ctr]); 
            if ((i + ctr) == 14)
            { 
                system ("clear");  
                header(); 
                printf ("You have now won %s rupees! \n", w); 
                printf ("\nCongratulations %s, your knowledge of facts is unmatched!!! You have completed the quiz and won the maximum prize! \n", name); 
                printf ("Now you are a CROREPATI! \n"); 
                end(f, w); 
                break;
            } 
            else 
            { 
                printf ("You have now won %s rupees! \n", w); 
                continue; 
            }  
        }
        else if (check == 0) // The answer the player has entered is incorrect. 
        {
            if ((i + ctr) <= 4)
            { 
                strcpy (w, "0"); 
                printf ("You have been demoted to level 0. \n"); 
                printf ("Press any key : "); 
                getchar(); 
                pressAnyKey(); 
                header(); 
                printf ("Sorry %s. Unfortunately, you have not won any money. Better luck next time. \n", name);  
            }
            else if (((i + ctr) > 4) && ((i + ctr) <= 9)) // The first level has been cleared. 
            { 
                strcpy(w, money[4]); 
                printf ("You have been demoted to level 5. \n"); 
                printf ("Press any key : "); 
                getchar(); 
                pressAnyKey(); 
                header(); 
                printf ("Congratulations %s! You have won %s rupees! \n", name, w); 
            }
            else if (((i + ctr) > 9) && ((i + ctr) <= 14)) // The second level has been cleared. 
            { 
                strcpy(w, money[9]); 
                printf ("You have been demoted to level 10. \n"); 
                printf ("Press any key : "); 
                getchar(); 
                pressAnyKey(); 
                header(); 
                printf ("Congratualtions %s! You have won %s rupees! \n", name, w); 
            } 
            *endCheck = 0; 
            break;
        } 
    } 

    if (*endCheck == 0 && (i + ctr) != 14)
    { 
        printf ("You reached level %d. \n", num); 
        end(f, w); 
    }
} 

void pressAnyKey() 
{ 
    // To press a key and progress without having to hit enter 
    
    system ("/bin/stty raw"); 
    getchar(); 
    system ("/bin/stty cooked"); 
    system ("clear"); 
}

void end(int f[2][2], char w[12]) 
{ 
      // Displays information at the end of the program 
      
      if ((f[0][0] + f[1][0]) == 0) 
      { 
          printf ("You used the 50 - 50 lifeline in question %d and the 'Flip the Question' lifeline in question %d. \n", f[0][1], f[1][1]); 
      } 
      else if ((f[0][0] + f[1][0]) == 2) 
      { 
          printf ("You did not use any lifelines! \n"); 
      } 
      else if (f[0][0] == 0 && f[1][0] == 1) 
      { 
          printf ("You used the 50 - 50 lifeline in question %d and your 'Flip the Question' lifeline was unused. \n", f[0][1]); 
      } 
      else 
      { 
          printf ("You used the 'Flip The Question' lifeline in question %d and your 50 - 50 lifeline was unused. \n", f[1][1]); 
      } 
      if (strcmp(w, "0") == 0) 
      { 
           printf ("\nGOOD EFFORT!\n"); 
      } 
      else 
      { 
           printf("\n");
           printf("\n");
           printf("'||      ||` '||''''| '||     '||        '||'''|. .|''''|, '||\\   ||` '||''''|\n");
           printf(" ||      ||   ||   .   ||      ||         ||   || ||    ||  ||\\\\  ||   ||   . \n");
           printf(" ||  /\\  ||   ||'''|   ||      ||         ||   || ||    ||  || \\\\ ||   ||'''| \n");
           printf("  \\\\//\\\\//    ||       ||      ||         ||   || ||    ||  ||  \\\\||   ||     \n");
           printf("   \\/  \\/    .||....| .||...| .||...|    .||...|' `|....|' .||   \\||. .||....|\n");
           printf("\n");
           printf("\n");
      } 
      printf ("Run the program to play again. \n "); 
} 