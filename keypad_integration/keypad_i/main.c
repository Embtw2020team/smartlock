#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define C_S system("clear")
#define T_D sleep(1)
#define path /sys/class/gpio/gpio28/

static inline void blink_deny()
{
//    int gpio_status = 1;
//    gpio_status = access("/sys/class/gpio/gpio68/value", F_OK );
//
//    if (gpio_status == -1) 
//    {
//        printf("GPIO_68 file doesn't exist.\n");
//        exit(1);
//    }
    system("echo out > path + direction"); 
    sleep(1);
    for(int i = 0; i < 3; i++)
    {
         printf("LED -> ON\n");
         system("echo 1 > path + value");
         printf("LED -> OFF\n");
         system("echo 0 > path + value");
    }
    return;
}

static inline void blink_grant()
{
//    int gpio_status = 1;
//    gpio_status = access("/sys/class/gpio/gpio68/value", F_OK );
//
//    if (gpio_status == -1) 
//    {
//        printf("GPIO_68 file doesn't exist.\n");
//        exit(1);
//    }
    system("echo out > path + direction"); 
    T_D;
    printf("LED -> ON\n");
    system("echo 1 > path + value");
    T_D;
    printf("LED -> OFF\n");
    system("echo 0 > path + value");

    return;
}

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
    blink_grant();
//    T_D;
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
            blink_deny();
            T_D;
            C_S;
        }
        
    }
    return 0;
}
