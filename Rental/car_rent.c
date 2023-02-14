#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include <ctype.h>

#define LONG_STRING 100
#define SHORT_STRING  20
#define MAX_ARRAY_SIZE 50
#define CURRENT_YEAR 2022

const char owner_filename[] = "owners";
const char car_filename[] = "vehicles";


int AdminMenu();
int SalesMenu();
void admin_Reg();
void sales_Reg();
int sales_login();
int admin_login();
int admin();
int salesrep();
void display();
int date(int y1,int y2,int m1,int m2,int d1,int d2);
void delay(int );
void car_rent();
void car_return();
void add_car();
int Admin();
int Sales();

struct owner{
    long owner_ID;
    char name[MAX_ARRAY_SIZE];
};

struct cars{
    long car_ID;
    int year; /*Manufacturing year*/
    int n_owners; /*Current number of owners*/
    char colour[MAX_ARRAY_SIZE];
    int owners_ID[5]; /*A car can only have 5 max owners*/
    char car_Name[LONG_STRING];
    char car_Model[LONG_STRING];
    char car_Speed[LONG_STRING];
    char car_Seat[LONG_STRING];
    char car_Rent[LONG_STRING];
};

//Login Structure
struct Login
{
  char fname[LONG_STRING];
  char lname[LONG_STRING];
  char username[SHORT_STRING];
  char password[SHORT_STRING];
};

struct car
{
    char customername[50];
    char customerId[13];
    char carrented[20];
    int n,rent,days;
    int dr,mr,yr,dret,mret,yret;
};
char carbrand[10][20]={"HYUNDAI","SUZUKI","HONDA","TOYOTA","FORD","TATA","MERCEDES","AUDI","ISUZU"};
char carmodel[10][20]={"Veloster","Celerio","Civic","Avalon","Explorer","Safari","E-Class","Q3","D-MAX"};
char color [10][20]={"Red","black","yellow","Blue","Red","Brown","Silver","Black","grey"};
char maxs_peed [10][20]={"100 Km/h ","150 Km/h","150 Km/h","170 Km/h","130 Km/h","140 Km/h","130 Km/h","120 Km/h","150 Km/h"};
int carseat[10]={4,4,4,8,4,4,4,8,8,0};
int carrentperday[10]={250,250,250,250,250,250,250,250,250,0};
int carrentpermontly[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int z=0,u=0;
struct car c,ca[10],cr[10],cn={0};

//Definitions for Log in
enum { LOGGED_OUT, LOGGED_IN, EXIT };

//Main function
int main(){
    int choice;
  while ( 1 )
  {
    printf("\nWelcome To User Section!!!\n");
    printf("\n");
    printf("1 : Administrator\n");
    printf("2 : Sales Representative\n");
    printf("3 : Quit\n");
    printf("Enter your choice : \n");

    if ( scanf("%d", &choice) == 1)
    {
      switch ( choice)
      {
      case 1:
        Admin();
        break;
      case 2:
        Sales();
        break;
      case 3:
        printf("Thanks!! \n");
        return EXIT;
      default:
        printf("Invalid choice, please insert a valid number\n");
        break;
      }
    }
  }
}
//Sales Main Function
int Sales() {
	int user_state = LOGGED_OUT;		
	
	srand(time(NULL));
	while (user_state!=EXIT)
	{
		if (user_state==LOGGED_OUT)
		{
			//User is not logged in Handle main menu
			user_state=salesrep();
		}
		else
		{// user is logged in, handle sub menu
			user_state=SalesMenu();
		}
	}
		
	return 0;
}

//Admin Main Function
int Admin() {
	int user_state = LOGGED_OUT;		
	
	srand(time(NULL));
	while (user_state!=EXIT)
	{
		if (user_state==LOGGED_OUT)
		{
			//User is not logged in Handle main menu
			user_state=admin();
		}
		else
		{// user is logged in, handle sub menu
			user_state=AdminMenu();
		}
	}
		
	return 0;
}


//Admin Menu
int admin()
{
  int choice;
  while ( 1 )
  {
    printf("Welcome to the Admin section!!!\n");
    printf("\n");
    printf("\n1 : Register!!!\n");
    printf("2 : Login!!!\n");
    printf("3 : Quit\n");
    printf("Enter your choice : \n");

    if ( scanf("%d", &choice) == 1)
    {
      switch ( choice)
      {
      case 1:
        admin_Reg();
        break;
      case 2:
        if ( admin_login())
          return LOGGED_IN;
        break;
      case 3:
        printf("Thank you working with us!! \n");
        return EXIT;
      default:
        printf("Invalid choice, please insert a valid number\n");
        break;
      }
    }
  }
}

//Sales Menu
int salesrep()
{
  int choice;
  while ( 1 )
  {
    printf("\n\nWelcome to the Sales Representative section!!!\n");
    printf("\n");
    printf("\n1 : Register!!!\n");
    printf("2 : Login!!!\n");
    printf("3 : Quit\n");
    printf("Enter your choice : \n");

    if ( scanf("%d", &choice) == 1)
    {
      switch ( choice)
      {
      case 1:
        sales_Reg();
        break;
      case 2:
        if ( sales_login())
          return LOGGED_IN;
        break;
      case 3:
        printf("Thank you for working with us!! \n");
        return EXIT;
      default:
        printf("Invalid choice, please insert a valid number\n");
        break;
      }
    }
  }
}

//Sub Menu
int AdminMenu()
{
  int choice;

  while ( 1 )
  {
    printf("\nAdmin Functionalities\n");

    printf("1 : Car Stats\n");
    printf("2 : Add new car\n");
    printf("3 : Sign Out\n");
    printf("Enter your choice : \n");
    if (scanf("%d", &choice)==1)
    {
      switch (choice)
      {
      case 1:
        display();
        break;
      case 2:
        add_car();
        break;
      case 3:
        printf("Good Bye!! \n");
        return EXIT;
      default:
        printf("Please enter a valid choice!!");
        break;
      }
    }
  }
}

//Sub Menu
int SalesMenu()
{
  int choice;

  while ( 1 )
  {
    printf("\nSalesMenu Functionalities\n");

    printf("1 : Car Rent\n");
    printf("2 : Car Return\n");
    printf("3 : Sign Out\n");
    printf("Enter your choice : \n");
    if (scanf("%d", &choice)==1)
    {
      switch (choice)
      {
      case 1:
        car_rent();
        break;
      case 2:
        car_return();
        break;
      case 3:
        printf("Thank you!!\n");
        return EXIT;
      default:
        printf("Please enter a valid choice!!");
        break;
      }
    }
  }
}


//admin Registration
void admin_Reg()
{
  FILE *log = fopen("admin_login.txt", "a+");
  struct Login l;
  printf("\nEnter first name : ");
  scanf("%s", (l.fname));
  printf("\nEnter last name : ");
  scanf("%s", l.lname);
  printf("\nEnter your Username : ");
  scanf("%s", l.username);
  printf("\nEnter your password : ");
  scanf("%s", l.password);
  fwrite(&l, sizeof(l), 1, log);
  fclose(log);
  printf("\nYou are successfully registered!!");
  printf("\nYour UserId is %s and your password is %s", l.username, l.password);
  printf("\nNow login with your username and password!!");
  printf("\nPress any key to continue ...");
  getchar();
}

//admin Registration
void sales_Reg()
{
  FILE *log = fopen("sales_login.txt", "a+");
  struct Login l;
  printf("\nEnter first name : ");
  scanf("%s", (l.fname));
  printf("\nEnter last name : ");
  scanf("%s", l.lname);
  printf("\nEnter your Username : ");
  scanf("%s", l.username);
  printf("\nEnter your password : ");
  scanf("%s", l.password);
  fwrite(&l, sizeof(l), 1, log);
  fclose(log);
  printf("\nYou are successfully registered!!");
  printf("\nYour UserId is %s and your password is %s", l.username, l.password);
  printf("\nNow login with your username and password!!");
  printf("\nPress any key to continue ...");
  getchar();
}

//admin Login
int admin_login()
{
  FILE *log;
  struct Login linput, lfile;
  log = fopen("admin_login.txt", "r");
  if (log == NULL)
  {
    printf("FILE NOT FOUND!!!\n");
    return 0; // login failed
  }
  printf("\nUserID : ");
  scanf("%s", linput.username);
  printf("\nPassword : ");
  scanf("%s", linput.password);
  while ( fread(&lfile, sizeof(lfile), 1, log)  )
  {
    if (strcmp(linput.username, lfile.username) == 0
      && strcmp(linput.password, lfile.password)==0)
    {
      printf("\nYou are successfully logged in !!\n");
      fclose(log);
      return 1; // login succeeded
    }
  }
  printf("\nYour UserID or password is incorrect !!\n");
  printf("Press any key to continue ...\n");
  getchar();
  fclose(log);
  return 0; // login failed
}

//admin Login
int sales_login()
{
  FILE *log;
  struct Login linput, lfile;
  log = fopen("sales_login.txt", "r");
  if (log == NULL)
  {
    printf("FILE NOT FOUND!!!\n");
    return 0; // login failed
  }
  printf("\nUserID : ");
  scanf("%s", linput.username);
  printf("\nPassword : ");
  scanf("%s", linput.password);
  while ( fread(&lfile, sizeof(lfile), 1, log)  )
  {
    if (strcmp(linput.username, lfile.username) == 0
      && strcmp(linput.password, lfile.password)==0)
    {
      printf("\nYou are successfully logged in !!\n");
      fclose(log);
      return 1; // login succeeded
    }
  }
  printf("\nYour UserID or password is incorrect !!\n");
  printf("Press any key to continue ...\n");
  getchar();
  fclose(log);
  return 0; // login failed
}

//Car rent
void car_rent()
{
    int i,f;
    int t,days1=0,days2=0,days3=0;
    char ch;
    int j,x;
    printf("\nWELCOME DEAR CUSTOMER!!! \n");
    display();
    printf("\nENTER THE BRAND OF CAR YOU WANT TO RENT: \n");
    scanf("%s",c.carrented);
    printf("\nENTER DATE ON WHICH YOU WILL TAKE THE CAR(dd-mm-yyyy): \n");
    scanf("%d%d%d",&c.dr,&c.mr,&c.yr);
    printf("\nENTER THE DATE ON WHICH YOU WILL RETURN THE CAR(dd-mm-yyyy): \n");
    scanf("%d%d%d",&c.dret,&c.mret,&c.yret);
    printf("\nCHECKING CAR AVAILABILITY...\n");
    delay(5000);
    //FILE *ptr;
    //ptr=fopen("Car_rent.txt","r");
    //fread(ca,sizeof(ca),1,ptr);
       for(i=0;i<10;i++)
       {
        if(strcmp(ca[i].carrented,c.carrented)==0)
        {
            for(t=0;t<=ca[i].mr;t++)
                days1+=carrentpermontly[t];
            for(t=0;t<=ca[i].mret;t++)
                days2+=carrentpermontly[t];
            for(t=0;t<=c.mr;t++)
                days3+=carrentpermontly[t];
            days1+=ca[i].dr;
            days2+=ca[i].dret;
            days3+=c.dr;
            if((days3-days1)*(days2-days3)>=0)
                f=1;
            else
            f=0;
               if(f==1)
               {
                 printf("Car not available.Are you interested in trying another car?\nIf yes enter Y else enter N\n");
                 getchar();
                 scanf("%c",&ch);
                 //fclose(ptr);
                 if(ch=='y'||ch=='Y')
                    car_rent();
                 else
                 {
                     printf("THANKS FOR COMING!!PLEASE VISIT AGAIN \n\n\n");
                     //fclose(ptr);
                     break;
                 }
               }
        }
        else if(strcmp(ca[i].carrented,c.carrented)!=0 ||f==0)
        {
            printf("CAR AVAILABLE!! \n");
            delay(5000);
            FILE *fp;
            fp=fopen("Car_rent","a");
            strcpy(ca[u].carrented,c.carrented);
            ca[u].dr=c.dr;
            ca[u].mr=c.mr;
            ca[u].yr=c.yr;
            ca[u].dret=c.dret;
            ca[u].mret=c.mret;
            ca[u].yret=c.yret;
            //u++;
            fwrite(&ca,sizeof(ca),1,fp);
            fclose(fp);
            printf("ENTER YOUR NAME: \n");
            scanf("%s",c.customername);
            printf("ENTER YOUR ID NUMBER: \n");
            scanf("%s",c.customerId);
            c.n=date(c.yr,c.yret,c.mr,c.mret,c.dr,c.dret);
            for(j=0;j<10;j++)
            {
                x=strcmp(c.carrented,carbrand[j]);
                if(x==0)
                    break;
            }
            c.rent=c.n*carrentperday[j];
            printf("\n\n#########################################################################\n");
            printf("WARNING: If any damage is done to the car then you are entirely responsible. \nThe car has to be returned in its initial condition.\n");
            printf("Details:\n");
            printf("NAME:\t%s\nID:\t%s\nCAR RENTED:\t%s\nNUMBER OF DAYS:\t%d\nRENT:\t%d\n",c.customername,c.customerId,c.carrented,c.n,c.rent);
            printf("\n###########################################################################\n");
            delay(5000);
            //fclose(ptr);
            strcpy(cr[z].customername,c.customername);
            strcpy(cr[z].customerId,c.customerId);
            strcpy(cr[z].carrented,c.carrented);
            cr[z].n=c.n;
            cr[z].rent=c.rent;
            //z++;
            FILE *fptr;
            fptr=fopen("Car_rent.txt","a+");
            fwrite(&cr,sizeof(cr),1,fptr);
            fclose(fptr);
            break;
        }
    }
}

// Adding a new car
void add_car(){
    FILE *binary_file;

    if((binary_file = fopen(car_filename, "a+b")) == NULL){
        perror(car_filename);
        exit(EXIT_FAILURE);
    }

    struct cars new_car;
    new_car.n_owners = 0;

    puts("Enter the car's ID");

    if(1 != scanf("%li", &new_car.car_ID)){
        fprintf(stderr, "Unable to read number");
        exit(EXIT_FAILURE);
    }

    while(new_car.car_ID <= 0){
        puts("The ID cannot be 0 or less. Please enter a new ID");
        if(1 != scanf("%li", &new_car.car_ID)){
            fprintf(stderr, "Unable to read number");
            exit(EXIT_FAILURE);
        }
  
    }

    puts("Enter the year of the making");

    if(1 != scanf("%i", &new_car.year)){
        fprintf(stderr, "Unable to read number");
        exit(EXIT_FAILURE);
    }

    while((new_car.year < 1885) || (new_car.year > CURRENT_YEAR)){
        puts("The year of the making can only be between 1885 and the current year");
        if(1 != scanf("%i", &new_car.year)){
            fprintf(stderr, "Unable to read number");
            exit(EXIT_FAILURE);
        }
  
    }

    puts("Enter the Brand of the car");
    scanf("%s", (new_car.car_Name));

    puts("Enter the Model of the car");
    scanf("%s", (new_car.car_Model));

    puts("Enter the colour of the car");
    scanf("%s", (new_car.colour));

    puts("Enter the Speed of the car");
    scanf("%s", (new_car.car_Speed));

    puts("Enter the Seat of the car");
    scanf("%s", (new_car.car_Seat));

    puts("Enter the Rent per Day of the car");
    scanf("%s", (new_car.car_Rent));
    struct cars temp;

    while((fread(&temp, sizeof(temp), 1, binary_file)) != 0){
        if(new_car.car_ID == temp.car_ID){
            puts("Car already exists");
            return;
        }
    }

    fwrite(&new_car, sizeof(new_car), 1, binary_file);
    fclose(binary_file);
    puts("Added new car successfully");
}

//Car return
void car_return()
{
    //FILE *fptr,*nptr;
    char id[13];
    int dd,mm,yy,d,m,y,flag=0,i,j;
    printf("\nWelcome back dear customer \n");
    printf("Please enter your id\n");
    scanf("%s",id);
    //fptr=fopen("Car_rent","r");
    //fread(cr,sizeof(struct car),1,fptr);
    for(i=0;i<10;i++)
    {
        if(strcmp(cr[i].customerId,id)==0)
        {
            flag=1;
            printf("\n\nHELLO %s\n",cr[i].customername);
            printf("For confirmation please enter the date on which you took the car and the date on which you are returning the date in(dd mm yyyy)format.\n");
            scanf("%d%d%d",&dd,&mm,&yy);
            scanf("%d%d%d",&d,&m,&y);
            cr[i].days=date(yy,y,mm,m,dd,d);
            if(cr[i].days>cr[i].n)
            {
                    cr[i].rent+=50*(cr[i].days-cr[i].n);
            }
            printf("FINAL AMOUNT:%d \n",cr[i].rent);
            printf("\n\n");
            break;
        }
    }
    if(flag==0)
           {
             printf("\nCustomer not found\n");
            //fclose(fptr);
           }
        else
        {
            //nptr=fopen("Car_rent","w+");
            //fread(cr,sizeof(cr),1,nptr);
            for(j=0;j<10;j++)
            {
                if(j==i)
                    memset(&cr[j].carrented[0],0,sizeof(cr[j].carrented[0]));
            }
            //fclose(fptr);
            //remove("Car_rent");
            //rename("Car_temp","Car_rent");
           // fclose(nptr);
        }
}

//Car details
void display()
{
    printf("############################################################################# \n");
    printf("#    CAR BRAND   #  MODEL  #  COLOR  # SPEED    # CARSEAT  RENT PER DAY(Php)# \n");  
    printf("############################################################################# \n");
    printf("#     HYUNDAI    # Veloster #    Red    100 Km/h    4       250             # \n");
    printf("#     SUZUKI     #  Celerio #    Black  150 Km/h    4       250             # \n");
    printf("#      HONDA     #  Civic   #    Yellow 150 Km/h    4       250             # \n");
    printf("#     TOYOTA     #  Avalon  #    Blue   170 Km/h    8       250             # \n");
    printf("#      FORD      # Explorer #    Red    130 Km/h    4       250             # \n");
    printf("#      TATA      #  Safari  #    Brown  140 Km/h    4       250             # \n");
    printf("#    MERCEDES    #  E-Class #    Silver 130 Km/h    4       250             # \n");
    printf("#      AUDI      #  Q3      #    Black  120 Km/h    8       250             # \n");
    printf("#     ISUZU      #  D-MAX   #    Grey   150 Km/h    8       250             # \n");
    printf("############################################################################# \n");
}

int date(int y1,int y2,int m1,int m2,int d1,int d2)
{
    int i,days1=0,days2=0,days3=0 ;
        for(i=0;i<=m1;i++)
            days1+=carrentpermontly[i];
        for(i=0;i<=m2;i++)
            days2+=carrentpermontly[i];
        days1+=d1;
        days2+=d2;
        return(days2-days1);
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}