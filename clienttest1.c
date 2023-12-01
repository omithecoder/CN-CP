// Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
    int clientSocket;
    struct sockaddr_in serverAddr;

int res;

// register contents
#define MAX_STRING_LEN 100


void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

void clearScreen() {
    printf("\033[2J");
    printf("\033[H");
    fflush(stdout);
}


typedef struct
{
    int serialnum;
    char fullName[MAX_STRING_LEN];
    char emailAddress[MAX_STRING_LEN];
    char country[MAX_STRING_LEN];
    char dateOfBirth[MAX_STRING_LEN];
    char headline[MAX_STRING_LEN];
    char profession[MAX_STRING_LEN];
    char industry[MAX_STRING_LEN];
    char institute[MAX_STRING_LEN];
    char employer[MAX_STRING_LEN];
    char student[MAX_STRING_LEN];
    char education[MAX_STRING_LEN];
    char skills[MAX_STRING_LEN];
    char certifications[MAX_STRING_LEN];
    char volunteerExperience[MAX_STRING_LEN];
    char languages[MAX_STRING_LEN];
    char projects[MAX_STRING_LEN];
    char username[MAX_STRING_LEN];
    char password[MAX_STRING_LEN];
    time_t lastLoginTime;
} user;


typedef struct
{
    char userid[MAX_STRING_LEN];
    char password[MAX_STRING_LEN];
}credentials;

void storeusername(const char *name)
{
    FILE *file = fopen("Userdata.txt", "a");

    if (file == NULL)
    {
        // Error opening the file
        printf("Error opening file for writing.\n");
        return;
    }

    // Move the file position to the end of the last line
    fseek(file, -1, SEEK_END);
    if (ftell(file) > 0)
    {
        // If the file is not empty, move back one more position
        fseek(file, -1, SEEK_CUR);
    }

    // Write the username to the end of the last line
    fprintf(file, "%s\n", name);

    fclose(file);
}


void storeCredentials(const char *password1)
{
    FILE *file = fopen("user.txt", "a");

    if (file == NULL)
    {
        // Error opening the file
        printf("Error opening file for writing.\n");
        return;
    }

    // Write username and password to the file
    fprintf(file, "%s\n", password1);

    fclose(file);
}





void printLinkedInHeader()
{
    gotoxy(10,3);

    printf("\n===============================================================================================================================================");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                          .:======================:.\t\t     ||");
    printf("\n||\t\t\t                                                                          :#######################*:\t\t     ||");
    printf("\n||\t\t\t:***:        :***.               -***.                             -***.  :###:..-################*:\t\t     ||");
    printf("\n||\t\t\t:*##:        +###-               -##*.                             -##*:  :##+   .*###############*:\t\t     ||");
    printf("\n||\t\t\t:*##:         .:.                -##*.                             -##*:  :###*=+*################*:\t\t     ||");
    printf("\n||\t\t\t:*##:        :===. :==-.:=+=-.   -##*.  .-==-. .:-=+=-..    .:=+=-.-##*:  :###=--+##---**=-:-+*###*:\t\t     ||");
    printf("\n||\t\t\t:*##:        -##*: =##########+. -##*..=###= .=###***##*. .=###***####*:  :###.  -##   .      .+##*:\t\t     ||");
    printf("\n||\t\t\t:*##:        -##*: =###=...+##*: -##*-*##*.  =##*.  .=##+.-##*..  .+##*:  :###.  -##   .+*#+   -##*:\t\t     ||");
    printf("\n||\t\t\t:*##:        -##*: =##*.   -##*: -##**##*.   +##########*.+##-     :##*:  :###.  -##   -####:  :##*:\t\t     ||");
    printf("\n||\t\t\t:*##:....... -##*: =##*.   -##*: -##*.=###-. -##+.    .   =##*.   .=##*:  :###.  -##   =####:  :##*:\t\t     ||");
    printf("\n||\t\t\t:*########*: -##*: =##*.   -##*: -##*. :*##+. =##*=-=*#*: .+###*++####*:  :###.  -##   =####:  :##*:\t\t     ||");
    printf("\n||\t\t\t:**********: -***: =***.   :***: -***.  .+***:  -*****=.    .=****-:***.  :###:..-##...=####:..:##*:\t\t     ||");
    printf("\n||\t\t\t                                                                          :#######################*:\t\t     ||");
    printf("\n||\t\t\t                                                                          .-======================:.\t\t     ||");
}

void printGetStartedButton()
{
    gotoxy(-50,6);
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t\t\t======================================                                                       ||");
    printf("\n||\t\t\t\t\t\t||            Press  Enter          ||                                                       ||");
    printf("\n||\t\t\t\t\t\t======================================                                                       ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n===============================================================================================================================================");
}


int displayauthScreen()
{
    int a;
gotoxy(10,3);
    printf("\n===============================================================================================================================================");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t\t\t\t                                              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    (_)     | |     | (_)                  \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |     _ _ __ | | ___| | _ __              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    | | '_ \\| |/ / ` | | ' \\             \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |____| | | | |   < (_| | | | | |            \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t|______|_|_| |_|_|\\_\\__,_|_|_| |_|            \t\t\t\t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||-------------------------------------------------------------------------------------------------------------------------------------------||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
gotoxy(15,14);
    printf("\n||                           @@@@@@@@@                         \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                         @@@@@@@@@@@@@                       \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                        @@@@@@@@@@@@@@@                      \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                       @@@@@@@@@@@@@@@@@                     \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                        @@@@@@@@@@@@@@@                      ==================================\t\t\t\t             ||");
    printf("\n||                          @@@@@@@@@@@                        || (press 1)  Log In            ||\t\t\t\t             ||");
    printf("\n||                            @@@@@@@                          ==================================\t\t\t\t             ||");
    printf("\n||                       @@@@@@@   @@@@@@@                     || (press 2)  Sign up           ||\t\t\t\t             ||");
    printf("\n||                   @@@@@@@@@@@@@@@@@@@@@@@@@                 ==================================\t\t\t\t             ||");
    printf("\n||                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@               || (press 3)  Exit              ||\t\t\t\t             ||");
    printf("\n||                @@@@@@@@@@@@       @@@@@@@@@@@@              ==================================\t\t\t\t             ||");
    printf("\n||                @@@@@@@@@  @@@@@@@@@  @@@@@@@@@              \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                @@@@@@  @@@@@ @@@ @@@@@  @@@@@@              \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                @@@@@  @@@@@@ @ @ @@@@@@  @@@@@              \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                  @@@  @@@@@       @@@@@  @@@                \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                       @@@@@   @   @@@@@                     \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                       @@@@@   @   @@@@@                     \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                        @@@@@@@@@@@@@@@                      \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||                           @@@@@@@@@                         \t\t\t\t\t\t\t\t\t             ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n===============================================================================================================================================");
    fflush(stdin);
    scanf("%d", &a);
    return a;
}



// Display Login Screen
char *displayLoginScreen()
{
    user u1;
    int auth;
    int i=8000;
    char userid[100];
    char* str = (char*)malloc(strlen("NuLL") + 1);
    strcpy(str, "NuLL");
    char password[100];
int x = 10;
    int y = 3;
    gotoxy(x, y);
    printf("\n===============================================================================================================================================");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t\t\t\t _      _       _       _ _                   \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    (_)     | |     | (_)                  \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |     _ _ __ | | ___| | _ __              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    | | '_ \\| |/ / ` | | ' \\             \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |____| | | | |   < (_| | | | | | |          \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t|______|_|_| |_|_|\\_\\__,_|_|_| |_|            \t\t\t\t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||-------------------------------------------------------------------------------------------------------------------------------------------||");
    printf("\n||\t\t\t                               Login Using Your Credentials                                         \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your Username (ID)   |                                               |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your Password        |                                               |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n===============================================================================================================================================");

    gotoxy(65, 19);
    scanf(" %[^\n]", u1.username); // Assuming you have a 'username' field in your user struct
    gotoxy(65, 21);
    scanf(" %[^\n]", u1.password); // Assuming you have a 'password' field in your user struct
    char* user = (char*)malloc(strlen(u1.username) + 1);
    strcpy(user,u1.username);
    send(clientSocket, u1.username, sizeof(u1.username), 0);
    send(clientSocket, u1.password, sizeof(u1.password), 0);

    gotoxy(65, 24);
    printf("\n\t\t\t\t\t\t\tAuthenticating");

    while (1)
    {
    int x = 71;
    int y = 25;
    gotoxy(x, y);
        for (int i = 0; i < 3; i++)
        {
            printf(".");
        }
        int x1 = 71;
    int y1 = 25;
    gotoxy(x1, y1);
        for (int j = 2; j >= 0; j--)
        {
            printf(" ");
        }
        i--;
        if (i == 0)
        {
            break;
        }
        
    }

    
    recv(clientSocket, &auth, sizeof(auth), 0);

    if (auth)
        {
            gotoxy(65, 27);
            printf("\n\t\t\t\t\t\tAuthentication Successful!");
            return user;
        }
        else
        {
            gotoxy(65, 27);
            printf("\n\t\t\t\t\t\tAuthentication Failed. Please check your credentials.");   
            return str;
        }
        
        
}



int isUsernameExists(const char *username)
{
    FILE *file = fopen("user.txt", "r");

    if (file == NULL)
    {
        // File doesn't exist, so username doesn't exist
        return 0;
    }

    char storedUsername[MAX_STRING_LEN];

    // Loop through the file to find the matching username
    while (fscanf(file, "%s", storedUsername) == 1)
    {
        // Compare the entered username with the one in the file
        if (strstr(storedUsername,username) !=NULL)
        {
            fclose(file);
            return 1; // Username exists
        }
    }

    fclose(file);

    return 0; // Username doesn't exist
}




    //create id & password
    void createidpass()
{
    int i = 8000;
    int w;
    char confpass[100];
    char username1[MAX_STRING_LEN];
    char password1[MAX_STRING_LEN];
    credentials c1;
int x = 10;
    int y = 3;
    gotoxy(x, y);
    printf("\n===============================================================================================================================================");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t\t\t\t                                              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    (_)     | |     | (_)                  \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |     _ _ __ | | ___| | _ __              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    | | '_ \\| |/ / ` | | ' \\             \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |____| | | | |   < (_| | | | | |            \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t|______|_|_| |_|_|\\_\\__,_|_|_| |_|            \t\t\t\t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||-------------------------------------------------------------------------------------------------------------------------------------------||");
    printf("\n||\t\t\t               One Last step to Go! Create Your UserID & Password For Login                         \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your Username (ID)   |                                               |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Set Your Password          |                                               |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Confirm Password           |                                               |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n===============================================================================================================================================");
    // Move the cursor to a new position
l:
    gotoxy(65, 19);
    scanf(" %[^\n]", username1); // Assuming you have a 'username' field in your user struct
k:
    gotoxy(65, 21);
    scanf(" %[^\n]", password1); // Assuming you have a 'password' field in your user struct
    gotoxy(65, 23);
    scanf(" %[^\n]", confpass); // Assuming you have a 'password' field in your user struct
   

    if (isUsernameExists(username1))
    {
        gotoxy(65, 27);
        printf("\n\t\t\t\t\t\tUsername already exists. Please choose a different username.");
        goto l;
    }
    if (strcmp(password1, confpass))
    {
        gotoxy(65, 27);
        printf("\n\t\t\t\t\t\tConfirm Password and set password not matching");
        goto k;
    }
    strcpy(confpass,username1);

    
    send(clientSocket,username1,strlen(username1),0);
    send(clientSocket,password1,strlen(password1),0);




    







  



    gotoxy(65, 24);
    printf("\n\t\t\t\t\t\t\tProcessing");

    while (1)
    {
    int x = 67;
    int y = 25;
    gotoxy(x, y);
        for (int i = 0; i < 3; i++)
        {
            printf(".");
        }
        int x1 = 67;
    int y1 = 25;
    gotoxy(x1, y1);
        for (int j = 2; j >= 0; j--)
        {
            printf(" ");
        }
        i--;
        if (i == 0)
        {
            break;
        }

    }
    strcat(username1,password1);
     storeCredentials(username1);
     storeusername(confpass);
    // strcat(username1," ");





    

    gotoxy(65, 27);
    printf("\n\t\t\t\t\t\t                                              ");
    gotoxy(65, 27);
    printf("\n\t\t\t\t\t\tLogin password created Successfully");
    
}





//Registration page
void displayregScreen()
{
    int resp;
    user u1;
int x = 10;
    int y = 3;
    gotoxy(x, y);
    printf("\n===============================================================================================================================================");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||\t\t\t\t\t\t\t                                              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    (_)     | |     | (_)                  \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |     _ _ __ | | ___| | _ __              \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |    | | '_ \\| |/ / ` | | ' \\             \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t| |____| | | | |   < (_| | | | | |            \t\t\t\t\t     ||");
    printf("\n||\t\t\t\t\t\t\t|______|_|_| |_|_|\\_\\__,_|_|_| |_|            \t\t\t\t\t     ||");
    printf("\n||\t\t\t                                                                                                    \t\t     ||");
    printf("\n||-------------------------------------------------------------------------------------------------------------------------------------------||");
    printf("\n||\t\t\t                                 PROFILE CREATION                                                   \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your Full Name        |                                              |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your Email Address    |                                              |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your location/Country |                                              |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your Date of Birth    |                                              |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Enter Your profile Headline |                                              |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
    printf("\n||\t\t\t\t|  Choose profession   =>      |  Student(press1)  | IndustryEmployer(press2) |          \t\t     ||");
    printf("\n||\t\t\t\t===============================================================================          \t\t     ||");

    // Move the cursor to a new position
    gotoxy(65, 16);
    scanf(" %[^\n]", u1.fullName); // Read until newline
    gotoxy(65, 18);
    scanf(" %[^\n]", u1.emailAddress);
    gotoxy(65, 20);
    scanf(" %[^\n]", u1.country);
    gotoxy(65, 22);
    scanf(" %[^\n]", u1.dateOfBirth);
    gotoxy(65, 24);
    scanf(" %[^\n]", u1.headline);
h:
    gotoxy(60, 26);
    scanf(" %[^\n]", u1.profession);

    if (!strcmp(u1.profession, "1"))
    {
        printf("\n||\t\t\t\t|  Enter Your Institute name   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your course details   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Education info   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your skills           |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Certifications   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Volunteer Exp    |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Languages you speak   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Projects info    |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t                                                                                                    \t\t     ||");
        printf("\n||\t\t\t                                                                                                    \t\t     ||");
        printf("\n===============================================================================================================================================");

        gotoxy(65, 23);
        scanf(" %[^\n]", u1.institute); // Read until newline
        gotoxy(65, 25);
        scanf(" %[^\n]", u1.student);
        gotoxy(65, 27);
        scanf(" %[^\n]", u1.education);
        gotoxy(65, 29);
        scanf(" %[^\n]", u1.skills);
        gotoxy(65, 31);
        scanf(" %[^\n]", u1.certifications);
        gotoxy(65, 33);
        scanf(" %[^\n]", u1.volunteerExperience);
        gotoxy(65, 35);
        scanf(" %[^\n]", u1.languages);
        gotoxy(65, 37);
        scanf(" %[^\n]", u1.projects);

        send(clientSocket,&u1,sizeof(u1),0);

        if(resp)
        {
            printf("\nRegistration Successful");
        }
        else
        {
            printf("\nRegistration Failed");
        }
        clearScreen();
        createidpass();
        return;
        // adduser(u1);
        // addprofile(u1);

    }
    else if (!strcmp(u1.profession, "2"))
    {
        printf("\n||\t\t\t\t|  Enter Your Company name     |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your working Position |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Education info   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your skills           |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Certifications   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Volunteer Exp    |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Languages you speak   |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t\t|  Enter Your Projects info    |                                              |          \t\t     ||");
        printf("\n||\t\t\t\t===============================================================================          \t\t     ||");
        printf("\n||\t\t\t                                                                                                    \t\t     ||");
        printf("\n||\t\t\t                                                                                                    \t\t     ||");
        printf("\n===============================================================================================================================================");
        gotoxy(65, 23);
        scanf(" %[^\n]", u1.industry); // Read until newline
        gotoxy(65, 25);
        scanf(" %[^\n]", u1.employer);
        gotoxy(65, 27);
        scanf(" %[^\n]", u1.education);
        gotoxy(65, 29);
        scanf(" %[^\n]", u1.skills);
        gotoxy(65, 31);
        scanf(" %[^\n]", u1.certifications);
        gotoxy(65, 33);
        scanf(" %[^\n]", u1.volunteerExperience);
        gotoxy(65, 35);
        scanf(" %[^\n]", u1.languages);
        gotoxy(65, 37);
        scanf(" %[^\n]", u1.projects);


        send(clientSocket,&u1,sizeof(u1),0);
        // recv(clientSocket,&resp,sizeof(resp),0);
        if(resp)
        {
            printf("\nRegistration Successful");
        }
        else
        {
            printf("\nRegistration Failed");
        }
        clearScreen();
        createidpass();
        return;
        // adduser(u1);
        // addprofile(u1);
    }
    else
    {
        printf("\nInvalide response!");
        goto h;
    }

    }

    void Logout()
{
    printf("\nYou Logout Successfully!");
    return;
}



void Search(char *name)
{int choice;
    printf("\n===============================================================================================================================================");
    printf("\n|  Linkedin..       ||\t   Home (press 1) \t Profile (press 2) \t Search (press 3) \t Logout (press 4)   ||\t(Welcome Omkar!)      |");
    printf("\n===============================================================================================================================================");
    printf("\n\n\t\t\t\t\t\t\tThis is Search By using Following Options\n\n");
    printf("\n\n-----------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n||\t    1. Search by Name     \t||\t     2. Search by Institute Name      \t||\t      3. Search by Company Name        \t     ||");
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n||\t 4. Search by Projects    \t||\t         5. Search by Skills          \t||\t           6. Back to Menu             \t     ||");
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    send(clientSocket,&choice,sizeof(choice),0);
    switch (choice)
    {
    case 1:
{
    char searchName[MAX_STRING_LEN];
    printf("Enter Full Name to search: ");
    scanf(" %[^\n]", searchName);
    send(clientSocket, searchName, strlen(searchName), 0);
    user u1;
    int o=0;
    int found = 0;
    int eof = 1;
 

        // Check if the received data is valid
        if (recv(clientSocket, &u1, sizeof(u1), 0))
        {
            printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
                   u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.industry,
                   u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
                   u1.projects, u1.username);
            found = 1;
            break;
            o++;
        }
        

        

    if (!found)
    {
        printf("No user found with the specified full name: %s\n", searchName);
    }

    bzero(searchName, MAX_STRING_LEN);
    break;
}

    case 2:
    {
        char searchName[MAX_STRING_LEN];
        printf("Enter Name to search: ");
        scanf(" %[^\n]", searchName);

        FILE *file = fopen("Userdata.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file for reading.\n");
            return;
        }

        user u1;
        int found = 0;

        while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                      &u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline,
                      u1.institute, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience,
                      u1.languages, u1.projects, u1.username) == 15)
        {
            if (strstr(u1.institute, searchName) != NULL)
            {

                printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
                       u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.institute,
                       u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
                       u1.projects, u1.username);

                found = 1;
                break; // Assuming the username is unique, no need to continue searching
            }
        }

        if (!found)
        {
            printf("No matching records found.\n");
        }

        fclose(file);
        break;
    }

    case 3:
    {
        char searchIndustry[MAX_STRING_LEN];
        printf("Enter Industry to search: ");
        scanf(" %[^\n]", searchIndustry);

        FILE *file = fopen("Userdata.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file for reading.\n");
            return;
        }

        user u1;
        int found = 0;

        while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                      &u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline,
                      u1.industry, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience,
                      u1.languages, u1.projects, u1.username) == 15)
        {
            if (strstr(u1.industry, searchIndustry) != NULL)
            {

                printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
                       u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.industry,
                       u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
                       u1.projects, u1.username);

                found = 1;
            }
        }

        if (!found)
        {
            printf("No user found with the specified industry: %s\n", searchIndustry);
        }

        fclose(file);
        break;
    }

    case 4:
    {
        char searchName[MAX_STRING_LEN];
        printf("Enter Project Name to search: ");
        scanf(" %[^\n]", searchName);

        FILE *file = fopen("Userdata.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file for reading.\n");
            return;
        }

        user u1;
        int found = 0;

        while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                      &u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline,
                      u1.industry, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience,
                      u1.languages, u1.projects, u1.username) == 15)
        {
            if (strstr(u1.projects, searchName) != NULL)
            {

                printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
                       u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.industry,
                       u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
                       u1.projects, u1.username);

                found = 1;
            }
        }

        if (!found)
        {
            printf("No user found with the specified project name: %s\n", searchName);
        }

        fclose(file);
        break;
    }

    case 5:
    {
        char searchSkills[MAX_STRING_LEN];
        printf("Enter Skills to search: ");
        scanf(" %[^\n]", searchSkills);

        FILE *file = fopen("Userdata.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file for reading.\n");
            return;
        }

        user u1;
        int found = 0;

        while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                      &u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline,
                      u1.industry, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience,
                      u1.languages, u1.projects, u1.username) == 15)
        {
            if (strstr(u1.skills, searchSkills) != NULL)
            {

                printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
                       u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.industry,
                       u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
                       u1.projects, u1.username);

                found = 1;
            }
        }

        if (!found)
        {
            printf("No user found with the specified skills: %s\n", searchSkills);
        }

        fclose(file);
        break;
    }
    default:
        printf("Invalid choice.\n");
    }
    printf("\n===============================================================================================================================================");
}


void myprofile(char* str) {
    FILE *file = fopen("Userdata.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    user u1;
    int r=1;
    int found = 0;

    // while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
    //               &u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline,
    //               u1.institute, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience,
    //               u1.languages, u1.projects, u1.username) == 15) {
    //     if (strcmp(u1.username, str) == 0) {
            

r=recv(clientSocket,&u1,sizeof(u1),0);
            if(r)
            {
            printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
                   u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.institute,
                   u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
                   u1.projects, u1.username);

            found = 1;
            }
                   
            
            
             // Assuming the username is unique, no need to continue searching
        
    
gotoxy(70,4);
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t            @@@@@@@@@@@@            ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t        @@@@@@@@@@@@@@@@@@@@        ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t      @@@@@@@@@@@@@@@@@@@@@@@@      ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t    @@@@@@@@@@        @@@@@@@@@@    ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t   @@@@@@@@@            @@@@@@@@@   ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t  @@@@@@@@@  @@          @@@@@@@@@  ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t=@@@@@@@@@@ @@@@@@@@@@@@ @@@@@@@@@@=");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t@@@@@@@@@@ @@@@@@@@@@@@@@ @@@@@@@@@@");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t@@@@@@@@@@# @@@@@@@@@@@@ #@@@@@@@@@@");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t@@@@@@@@@@@@ @@@@@@@@@@ @@@@@@@@@@@@");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t.@@@@@@@@@@@@ @@@@@@@@ @@@@@@@@@@@@*");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t @@@@@@@@@@@@@@  @@  @@@@@@@@@@@@@@ ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t   @@@@@     :@@@  @@@:     @@@@@   ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t    @@        @@@  @@@        @@    ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t      @#       @    @       =@      ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t        @@.      @@       @@        ");
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t            @@@@@@@@@@@@            ");    
printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t                                    ");
    if (!found) {
        printf("No matching records found.\n");
    }

    fclose(file);
}




void profilepage(char *name)
{
    printf("\n===============================================================================================================================================");
    printf("\n|  Linkedin..       ||\t   Home (press 1) \t Profile (press 2) \t Search (press 3) \t Logout (press 4)   ||\t(Welcome %s!)      |",name);
    printf("\n===============================================================================================================================================");
    // printf("\nThis is Profile Page");
    myprofile(name);
    printf("\n===============================================================================================================================================");
}

void profiles()
{
    int i=5;
    int n=0;
    int j=1;
    FILE *file = fopen("Userprofile.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    user u1;

    // printf("Roll Number | Name                 | Email                | Industry/Institute | Student/Employee | Education |\n");

    while (fscanf(file, "%s %s %s %s %s %s",u1.username, u1.emailAddress, u1.industry,u1.student,u1.country,u1.education) == 6)
    {
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n\t||\tName\t\t  : %s \n\t||\tEmail\t\t  : %s \n\t||\tLocation/Country  : %s \n\t||\tInstitute/Company : %s \n\t||\tCourse/Job Pose   : %s \n\t||\tEducation\t  : %s \n\n\n ", u1.username, u1.emailAddress, u1.industry,u1.student,u1.country,u1.education);
        printf("\t---------------------------------------------------------------------------------------------------------------------------\n");    
      
      if(j<=2)
      {
        gotoxy(10,5+n);
printf("\n\t||\t\t\t\t\t\t\t\t         @@@@@                  \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t       @@@@@@@@@                \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t      @@@@@@@@@@@               \t\t       ||");                
printf("\n\t||\t\t\t\t\t\t\t\t        @@@@@@@                 \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t         @@@@@                  \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t      @@       @                \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t   @@@@@@ @@@ @@@@@             \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t  @@@@@@@  @  @@@@@@@           \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t  @@@@@@@@@@@@@@@@@@@           \t\t       ||"); 
      }
  if(j>=3)
        {
            break;
        }
        j++;
        n+=10;

    }
    

//                 gotoxy(10,9);
// printf("\n\t||\t\t\t\t\t\t\t\t         @@@@@                  \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t       @@@@@@@@@                \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t      @@@@@@@@@@@               \t\t       ||");                
// printf("\n\t||\t\t\t\t\t\t\t\t        @@@@@@@                 \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t         @@@@@                  \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t      @@       @                \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t   @@@@@@ @@@ @@@@@             \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t  @@@@@@@  @  @@@@@@@           \t\t       ||");     
// printf("\n\t||\t\t\t\t\t\t\t\t  @@@@@@@@@@@@@@@@@@@           \t\t       ||"); 
gotoxy(10,21);
printf("\n\n\n\n\t||\t\t\t\t\t\t\t\t        @@@@@@@                  \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t       @@@@@@@@@                \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t      @@@@@@@@@@@               \t\t       ||");                
printf("\n\t||\t\t\t\t\t\t\t\t        @@@@@@@                 \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t         @@@@@                  \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t      @@       @                \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t   @@@@@@ @@@ @@@@@             \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t  @@@@@@@  @  @@@@@@@           \t\t       ||");     
printf("\n\t||\t\t\t\t\t\t\t\t  @@@@@@@@@@@@@@@@@@@           \t\t       ||"); 



    fclose(file);
    return;
}




























void homepage(char *res)
{
    clearScreen();
    int ch;
    int b=1;
    printf("\n===============================================================================================================================================");
    printf("\n|  Linkedin..       ||\t   Home (press 1) \t Profile (press 2) \t Search (press 3) \t Logout (press 4)   ||\t(Welcome %s!)      |",res);
    printf("\n===============================================================================================================================================\n");
    profiles();
    printf("\n===============================================================================================================================================");
    while(b)
    {
        k:
    scanf("%d",&ch);
    send(clientSocket,&ch,sizeof(ch),0);
    switch(ch)
    {
        case 1:
        clearScreen();
        homepage(res);
        break;

        case 2:
        clearScreen();
        profilepage(res);
        break;

        case 3:
        clearScreen();
        Search(res);
        goto k;
        break;

        case 4:
        clearScreen();
        Logout();
        b=0;
        break;

        default:
        printf("\nInvalide Input!Try Again!");

    }
    }
    return;




}













#define PORT 5500
#define MAX_STRING_LEN 100

int main() {


    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP address
    serverAddr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }


    char *res1;
    int b = 1;
while(1)
{
    while (b)
    {

        // Print LinkedIn header
        printLinkedInHeader();
        // Print "Get Started" button
        printGetStartedButton();
        getchar(); // Wait for Enter key press
        clearScreen();
        l:
        res = displayauthScreen();
        send(clientSocket, &res, sizeof(res), 0);
        switch (res)
        {
        case 1:
            clearScreen();
            res1 = displayLoginScreen();
            if(strcmp(res1,"NuLL"))
            {
                homepage(res1);
                goto l;
                break;
            }
            
            clearScreen();
            printf("\nInvalide UserID & Password");
            break;

        case 2:
            clearScreen();
            displayregScreen();
            clearScreen();
            goto l;
            break;

        case 3:
            clearScreen();
            exit(0);
            goto l;
            break;

        default:
            clearScreen();
            printf("\nInvalide Input! Please Try Again!");
            printf("\nPlease Press Enter to continue.....");
            getchar(); // Wait for Enter key press
            clearScreen();
            printf("\nInvalide Input! Please Try Again!");
            printf("\nPlease Press Enter to continue.....");
            break;
        }
        
        
    }
    // printf("\nWelcome %s\n",res1);
    // break;
    // homepage(res1);
    // b=1;
    close(clientSocket);
}


    // Close the socket
    

    return 0;
}
