# KBC 
Command-line based simulator of KBC/Who Wants to Be a Millionaire, created in C from scratch 


Computer Programming (CS F111) Take Home Assignment 

Members : 
1. 2019B1PS0904P  Anushka Jain 
2. 2019B5PS0809P  Payal Basrani 
3. 2019B4PS0554P  Suchismita Tripathy 



Kaun Banega Crorepati is a popular Indian game show where contestants win money based on the number of quiz questions answered correctly. The questions have increasing money values, with the greatest amount, in this case, being 5 crores. Each question has 4 options of which only one is correct. The game also offers a variety of lifelines that the contestant can use to use to help answer the question correctly. The format we have followed has 15 questions, with the highest prize being 5 crores with 2 lifelines available to be used only once each, even at the same time. The 50 - 50 lifeline removes two wrong options from the current question and the 'Flip the Question' lifeline displays a new question for the player to answer. The 15 questions are divided into 3 blocks, getting a question wrong before 5 questions leaves you with no money, getting a question wrong before 10 questions leaves you with 20,000 rupees and getting a question wrong before 15 questions leaves you with 6,40,000 rupees. The player may also quit or withdraw at any time and keep all the money they have earned till then. 



Running the code : 

1. There is only one file that needs to be compiled and run.
The input file (questions.csv) needs to be saved in the same directory as the .c file before compiling. 

2. The input file is questions.csv. It acts as the question bank for the quiz. The three blocks of questions (1 - 5, 6 - 10 and 11 - 15) are taken in increasing difficulty. Hence, there are 3 difficulty levels, even though there are actually 15 levels of questions. The input file contains questions taken directly from the internet. We have taken 50 questions of the first difficulty level, 40 of the next and 20 of the last. The code is so written that these numbers can be changed (if more questions were added for a given level) and only the variables n1, n2 and n3 need to be changed (the rest of the code depends only on these variables). Comma delimiters are used to separate the question, the 4 options in random order (as taken from the internet) and finally the correct option. A marker for the difficulty level was not required as the questions of each difficulty level are saved in order itself, making it easier to read and store into arrays. 

The function storeByLevel reads the file using strtok with a comma delimiter and stores the questions (according to the difficulty level) in a three dimensional array with 6 elements (question, option 1, option 2, option 3, option 4, correct option - A/B/C/D). As the file pointer stays at its last place unless it is closed and opened again, the storeByLevel functions are called thrice, one after the other, for each difficulty level. 

3. As the program starts, the logo is displayed and the player is asked to press ENTER to read more information. The next prompt shows the rules, after which they are asked to enter their name and then asked to press ENTER to start. All of this is run through the function named start. 

4. A random question is picked from the given level of difficulty using the printRandomQ function. Status integer arrays for each difficulty level are created (st1, st2 and st3) that store 1 in case a question has already been asked in the quiz. Thus the printRandomQ function generates a random index number and the corresponding question from the array of questions passed as an argument is printed if and only if the corresponding entry in the status integer array is not 1, after which that entry is changed to 1 so that it cannot be asked again in the same game. A separate array was created for this reason instead of simply adding another element to the questions array just to make its functioning more clear and to reduce code complexity. 

The first question is thus displayed. Before each question, a logo is displayed, along with the level (or question number) the player is currently at, their current total winnings, and general rules to play. The status of the lifelines is also displayed (the number of lifelines remaining, and the question number where a particular lifeline was used, if it has already been used). The four options are displayed on new lines after the question and the player is prompted to enter an answer. This is done using the displayG and displayQ functions. 

5. If the player enters 1, given that their 50 - 50 lifeline has not yet been used, two of the 3 wrong options are removed and the two remaining options are displayed on the screen. If the player enters any of the other two options as their answer, an error message is displayed and the player is prompted to enter a valid answer. Before the question, a message is displayed asking the player to enter only one of the two displayed options. This is done using the life50 function. If this lifeline has already been used (the question number where this was previously used is displayed at the top), entering 1 leads to an error message. If the player has quit and then enters 1, they are asked to enter a valid answer. 

6. If the player enters 2, given that their 'Flip the Question' lifeline has not yet been used, a new question is displayed on the screen in place of the old one. This is done using the lifeFlip function, which calls displayG and displayQ as well. If this lifeline has already been used, entering 2 leads to an error message. If the player has quit and then enters 2, they are asked to enter a valid answer. 

7. If the player enters the correct answer (not case sensitive), the player progresses to the next level, and their current winnings are set to the new amount and displayed at the top as the next question is displayed. The winnings are stored in a char array of size 12 and the money values for the questions are stored in a two dimensional char array. The data type char was used for these as integer values are not required (arithmetic operators are not used to update the current winnings). 

8. If the player's answer is incorrect, the correct answer is displayed on the screen. The game ends and based on the number of questions they have cleared, they are demoted to level 0, level 5 or level 10. Their winnings are thus changed and displayed with the end message. 

9. If the player enters an invalid answer (a character that is not a/A/b/B/c/C/d/D or not one of the 2 displayed options when the 50 - 50 lifeline is used) they are prompted to enter a valid answer or use an available lifeline (if all lifelines have not yet been used). All this is done through the checkA function that calls itself recursively if an invalid answer is entered or if the 50 - 50 lifeline has been used.  

10. If the player enters q or Q, they quit the game. A global int variable, flag, is assigned the value 1 and this is used as a signal by many functions. The player is then asked to guess an option and if their answer is incorrect, the correct answer is displayed. The player's winnings are not changed and the end message is displayed. If the player enters q or Q, 1 or 2 or an option that has not been displayed if the player has quit right after using the 50 - 50 lifeline, an error message is displayed. 

11. The end message is displayed if the player quits, answers incorrectly or reaches the end of the game. It is run through the function named end and displays the status of the lifelines by the end of the game. 

12. All the functions are called and controlled by the questionCall function, which is run thrice in the game, once for each block of questions (1 - 5, 6 - 10 and 11 - 15) if and only if each answer of the previous block was answered correctly (using the integer endCheck). 



Known Limitations : 

The player can press any key to continue and does not need to press any key and then ENTER. The functions scanf and getchar are such that the input is buffered until a '\n'. This problem can be fixed by changing the system settings from cooked to raw just before scanf or getchar is used (then changing it back). When we tried it on V.S. Code (on Windows), an extra message was printed on the screen which ruined the display but not on a virtual Ubuntu machine online, where everything looked as it should (the documentation also indicates that this message should not be printed on any Linux O.S.). This is, however, not a portable method to fix this problem and we were not able to find other successful solutions. 
