#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define C_S system("clear")
#define T_D usleep(1000000)

void get_password(char* ppassword)
{
    printf("Enter the password\n");
    scanf("%s", ppassword);
    return;
}

void check_password(int* ppresult,char* ppassword)
{
    char* temp[50];
    FILE* fp = fopen("database", "r");
    if(0 == fp)
    {
        printf("Failed to open the file\n");//System error message to be sent during implementation
//        return 0;
    }
    *ppresult = -1;
    while(!feof(fp) && (*ppresult != 0)) 
    {
        fscanf(fp, "%12s", temp);
        *ppresult = strcmp(temp, ppassword);
    }
}

void door_open()
{
    //control to gpio etc. 
    printf("Door open\n");//during implementation only a beep sound
    T_D;
    C_S;
    return;
}

int main(int argc, char **argv)
{
    char *password;
    int result = 1;
    password = (char*) malloc(16 * sizeof(char));
    while(1)
    {
        get_password(password);
        check_password(& result, password);
        if(result == 0)
            door_open();
        else
        {   
            printf("Wrong password; please retry\n");//during implementation only continuous beep sound
            T_D;
            C_S;
        }
        
    }
    return 0;
}