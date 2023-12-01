// Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>


int res;
char buffer[1024];
// register contents
#define MAX_STRING_LEN 100
int serverSocket, clientSocket;
struct sockaddr_in serverAddr, clientAddr;

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

} user;

typedef struct
{
    char userid[MAX_STRING_LEN];
    char password[MAX_STRING_LEN];
} credentials;

#define PORT 5500
int authenticate(const char *username3)
{

    FILE *file = fopen("user.txt", "r");

    if (file == NULL)
    {
        return 0; // File doesn't exist, so authentication fails
    }
    char storedUsername[MAX_STRING_LEN];
    // char storedPassword[MAX_STRING_LEN];

    // Loop through the file to find the matching username and password
    while (fscanf(file, "%s", storedUsername) == 1)
    {
        if (strcmp(username3, storedUsername) == 0)
        {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication fails
}


void searchbyname()
{
            char searchName[MAX_STRING_LEN];
    recv(clientSocket,searchName,sizeof(searchName),0);

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
            if (strstr(u1.fullName, searchName) != NULL)
            {
                send(clientSocket,&u1,sizeof(u1),0);

                found = 1;
                break; // Assuming the username is unique, no need to continue searching
            }
        }

        if (!found)
        {
            printf("No matching records found.\n");
        }

        fclose(file);
}

void logout()
{
    printf("\nClient Logout!");
    return;
}
void Search(char *str)
{
    int chh;
    printf("\nEnter in Searching....");
    recv(clientSocket, &chh, sizeof(chh), 0);
    switch (chh)
    {
    case 1:
    
        printf("\nSearching By Name....");
        searchbyname();
        break;
    
    case 2:
        printf("\nSearching by Institute Name...");
        break;
    case 3:
        printf("\nSearching by Company Name...");
        break;
    case 4:
        printf("Searching by Projects...");
        break;
    case 5:
        printf("\nSearching by Skills...");
        break;
    case 6:
        printf("\nBack to Menu");
        break;
    default:
        printf("\nInvalide!");
    }
    return;
}

void myprofile(const char *str1)
{

    FILE *file = fopen("Userdata.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    user u1;
    int found = 0;
    printf("\n%s", str1);

    while (fscanf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s",
                  &u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline,
                  u1.institute, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience,
                  u1.languages, u1.projects, u1.username) == 15)
    {
        if (strcmp(u1.username, str1) == 0)
        {

            // printf("\n\n\n\t||\tSerial Number\t     : %d \n\t||\tName\t\t     : %s \n\t||\tEmail\t\t     : %s \n\t||\tDateOfBirth\t     : %s \n\t||\tCountry\t\t     : %s \n\t||\tHeadline\t     : %s \n\t||\tInstitute/Industries : %s \n\t||\tStudent/Employee     : %s \n\t||\tEducation\t     : %s \n\t||\tSkills\t\t     : %s \n\t||\tCertifications\t     : %s \n\t||\tVolunteer\t     : %s \n\t||\tLanguage\t     : %s \n\t||\tProject\t\t     : %s \n\t||\tUserName\t     : %s \n\t||\n\n\n\n ",
            //        u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.institute,
            //        u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages,
            //        u1.projects, u1.username);
            send(clientSocket, &u1, sizeof(u1), 0);

            found = 1;
            break; // Assuming the username is unique, no need to continue searching
        }
    }
    fclose(file);
}

void homepage(char *name)
{
    printf("\nHomepage Open!");
    printf("\nclient : %s", name);
    int ch;
    int b = 1;
    while (b)
    {
    p:
        recv(clientSocket, &ch, sizeof(ch), 0);
        printf("\n%d ", ch);
        switch (ch)
        {
        case 1:
            // profiles();
            break;

        case 2:
            myprofile(name);
            break;

        case 3:
            Search(name);
            goto p;
            break;

        case 4:
            logout();
            return;
            break;

        default:
            printf("\nInvalide!");
        }
    }
}

void adduser(user u1)
{
    FILE *file = fopen("Userdata.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    if (!strcmp(u1.profession, "1"))
    {
        fprintf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s ", u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.institute, u1.student, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages, u1.projects);
    }

    else if (!strcmp(u1.profession, "2"))
    {
        fprintf(file, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s ", u1.serialnum, u1.fullName, u1.emailAddress, u1.dateOfBirth, u1.country, u1.headline, u1.industry, u1.employer, u1.education, u1.skills, u1.certifications, u1.volunteerExperience, u1.languages, u1.projects);
    }

    else
    {
        fclose(file);
        printf("\nThe Select Profession is selected incorrectly!");
        return;
    }

    printf("User added successfully!\n");

    fclose(file);
}

void addprofile(user u1)
{
    FILE *file = fopen("Userprofile.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    if (!strcmp(u1.profession, "1"))
    {
        fprintf(file, "%s %s %s %s %s %s\n", u1.fullName, u1.emailAddress, u1.country, u1.institute, u1.student, u1.education);
    }

    else if (!strcmp(u1.profession, "2"))
    {
        fprintf(file, "%s %s %s %s %s %s\n", u1.fullName, u1.emailAddress, u1.country, u1.industry, u1.employer, u1.education);
    }

    else
    {
        fclose(file);
        printf("\nThe Select Profession is selected incorrectly!");
        return;
    }
    fclose(file);
}

int getCurrentSerialNumber()
{
    FILE *file = fopen("Userdata.txt", "r");

    if (file == NULL)
    {
        // Error opening the file
        printf("Error opening file for reading.\n");
        return -1;
    }

    int currentSerialNumber = 0;
    int rollNumber;

    // Loop through the file to find the highest roll number
    while (fscanf(file, "%d", &rollNumber) == 1)
    {
        if (rollNumber > currentSerialNumber)
        {
            currentSerialNumber = rollNumber;
        }
    }

    fclose(file);

    // Increment the highest roll number to get the current serial number
    return currentSerialNumber + 1;
}

// store credential
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

// store username
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

int main()
{
    int ch;
    int b = 1;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1)
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        socklen_t clientLen = sizeof(clientAddr);

        b = 1;
        // Accept a connection from a client
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
        if (clientSocket == -1)
        {
            perror("Error accepting connection");
            exit(EXIT_FAILURE);
        }

        char username[MAX_STRING_LEN];
        char password[MAX_STRING_LEN];

        while (b)
        {
        l:
            char str[MAX_STRING_LEN];
            recv(clientSocket, &ch, sizeof(ch), 0);
            printf("\n%d", ch);
            switch (ch)
            {
            case 1:
                // Receive username and password from the client

                bzero(username, MAX_STRING_LEN);
                bzero(password, MAX_STRING_LEN);
                recv(clientSocket, username, sizeof(username), 0);
                strcpy(str, username);
                recv(clientSocket, password, sizeof(password), 0);
                // printf("\n%s", username);
                // printf("\n%s",password);
                strcat(username, password);
                printf("\n%s", username);

                // Authenticate the client
                int authenticatedUsername = authenticate(username);
                send(clientSocket, &authenticatedUsername, sizeof(authenticatedUsername), 0);

                if (authenticatedUsername != 0)
                {
                    printf("Authentication successful\n");

                    homepage(str);
                    // Send a welcome message to the client

                    // Clean up
                    // free(authenticatedUsername);
                }
                else
                {
                    printf("Authentication failed.\n");
                }

                break;

            case 2:
                int j = 0;
                int p = 0;
                int resp;
                user u1;
                char username1[MAX_STRING_LEN];
                char password1[MAX_STRING_LEN];
                char password[MAX_STRING_LEN];

                printf("\nRegistration Process started......");
                recv(clientSocket, &u1, sizeof(u1), 0);
                int i = getCurrentSerialNumber();
                u1.serialnum = i;
                i++;
                adduser(u1);
                addprofile(u1);
                memset(&u1,'\0',sizeof(u1));
                // Receive username and password from the client
                // Receive username and password from the client

                recv(clientSocket,username1,strlen(username1),0);
                recv(clientSocket,password1,strlen(password1),0);


                // Print the received values for debugging
                puts(username1);
                puts(password1);
                // printf("\n%s", password1);
                // storeusername(username1);
                // Store credentials and username in files
                // printf("%s", password1);
                // storeCredentials(password1);

                // Clear username and password arrays again

                bzero(&ch, sizeof(ch));

                break;

            case 3:
                printf("\nClient Exiting.....");
                b = 0;
                break;
            }
        }

        close(clientSocket);
    }

    return 0;
}