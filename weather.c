#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "weather.h"

#define CITIES 5
#define DAYS 7

//         city      days of the week
//         rows      columns
int temps [CITIES]  [DAYS];
unsigned char temps_indices [CITIES * DAYS][2];
float avg_temp_per_city[CITIES]; // 1D array to store the weekly average temperature for each city

unsigned char operation;
unsigned char program_on=1;

void start(void)
{
    system("cls");
    printf("Welcome to Weather Data Analysis System Program\n");
    Sleep(1000);
    system("cls");
    while(program_on)
    {
        printf("\n1 -> Input Temperature Data\n2 -> Calculate Average Weekly Temperature for Each City\n3 -> Find the City with the Hottest Day\n4 -> Find the City with the Coldest Day\n5 -> Determine hotest Day in Each City\n6 -> Determine Coldest Day in Each City\n7 -> Calculate City-to-City Temperature Difference\n8 -> Transpose the Temperature Data\n9 -> Exit\n");
        scanf("%i", &operation);
        printf("\n");

        switch (operation)
        {
            case 1:
                input_temperatures();
                temperature_alert();
                break;
            case 2:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                calculate_average_temp(0);
                break;
            case 3:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                clear_temps_indices();
                find_hottest_day();
                break;
            case 4:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                clear_temps_indices();
                find_coldest_day();
                break;
            case 5:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                find_hotest_day_per_city();
                break;
            case 6:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                find_coldest_day_per_city();
                break;
            case 7:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                calculate_average_temp(1);
                calculate_temp_difference();
                break;
            case 8:
                if(is_empty() == (CITIES * DAYS))
                    {
                        printf("You didn't input the data for the cities, Enter the data and try again.\n");
                        continue;
                    }
                    transpose_temps();
                break;
            case 9:
                program_on = 0;
                continue;
            default:
                printf("Enter a valid operation.\n");
                continue;
        }
    }
    system("cls");
    printf("Thank you for using Weather Data Analysis System Program\n");
    Sleep(1000);
    system("cls");
}


// The highest temperature ever recorded on Earth was  (58 Celsius) in the Libyan desert. 
// The coldest temperature ever measured was -126 Fahrenheit (-88 Celsius) at Vostok Station in Antarctica.
void input_temperatures(void)
{
    unsigned char rows=0;

    while(rows < CITIES)
    {
        unsigned char columns=0;

        printf("city %i:\n", rows+1);

        while(columns < DAYS)
        {
            printf("day %i -> ", columns+1);
            scanf("%i", &temps[rows][columns]);
            while(temps[rows][columns] < -88 || temps[rows][columns] > 58)
            {
                printf("Enter a valid temperature Between -88c to 58c -> ");
                scanf("%i", &temps[rows][columns]);
            }
            columns++;
        }

        rows++;
    }
}

void calculate_average_temp(unsigned char value)
{
    unsigned char rows=0;

    while(rows < CITIES)
    {
        unsigned char columns=0;
        float days_sum=0;

        while(columns < DAYS)
        {
            days_sum += temps[rows][columns];
            columns++;
        }

        avg_temp_per_city[rows] = (float)(days_sum/DAYS);
        if(value != 1)
        {
        printf("weekly average temperature for city %i -> %.3fc\n", rows+1, avg_temp_per_city[rows]);
        }

        rows++;
    }
}

 void find_hottest_day(void)
 {
    unsigned char city;
    unsigned char day;
    int temp;
    unsigned char rows=0;
    int max=0;

    while(rows < CITIES)
    {
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = (*((*(temps+rows))+columns));

            if(temp > max)
            {
                max = temp;
                city = rows;
                day = columns;
            }
            columns++;
        }
        rows++;
    }

    printf("The hotest day was on day %i in city %i -> %ic\n", day+1, city+1, temps[city][day]);

    rows = 0;
    while(rows < CITIES)
    {
        unsigned char index=0;
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = (*((*(temps+rows))+columns));

            if(temp == max)
            {
                temps_indices[index][1] = rows;
                temps_indices[index][2] = columns;
                if(!(city == temps_indices[index][1] && day == temps_indices[index][2]))
                {
                    printf("The same temp was also on day %i in city %i -> %ic\n", temps_indices[index][2]+1, temps_indices[index][1]+1, temps[temps_indices[index][1]][temps_indices[index][2]]);
                    index++;
                }                
            }
            columns++;
        }
        rows++;
    }
 }

 void find_coldest_day(void)
 {
    unsigned char city;
    unsigned char day;
    int temp;
    unsigned char rows=0;
    int min=100;

    while(rows < CITIES)
    {
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = (*((*(temps+rows))+columns));

            if(temp < min)
            {
                min = temp;
                city = rows;
                day = columns;
            }
            columns++;
        }
        rows++;
    }

    printf("The coldest day was on day %i in city %i -> %ic\n", day+1, city+1, temps[city][day]);

    rows = 0;
    while(rows < CITIES)
    {
        unsigned char index=0;
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = (*((*(temps+rows))+columns));

            if(temp == min)
            {
                temps_indices[index][1] = rows;
                temps_indices[index][2] = columns;
                
                if(!(city == temps_indices[index][1] && day == temps_indices[index][2]))
                {
                    printf("The same temp was also on day %i in city %i -> %ic\n", temps_indices[index][2]+1, temps_indices[index][1]+1, temps[temps_indices[index][1]][temps_indices[index][2]]);
                }
                index++;
            }
            columns++;
        }
        rows++;
    }
 }

 void find_hotest_day_per_city(void)
{
    unsigned char city;
    unsigned char day;
    unsigned char rows=0;
    int temp;
    int max=0;

    while(rows < CITIES)
    {
        max = 0;
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = temps[rows][columns];
            if(temp > max)
            {
                max = temp;
                city = rows;
                day = columns;
            }
            columns++;
        }
        
        printf("The hotest day in city %i was on day %i -> %ic\n", city+1, day+1, temps[city][day]);
        
        while(1)
        {
            columns=0;
            while(columns < DAYS)
            {
                if(max == temps[rows][columns] && columns != day)
                {
                    printf("The temp -> %ic in city %i was also on day %i\n", temps[city][columns], city+1, columns+1);
                }
                columns++;
            }
            break;
        }
        rows++;
    }
}

void find_coldest_day_per_city(void)
{
    unsigned char city;
    unsigned char day;
    unsigned char rows=0;
    int temp;
    int min=100;

    while(rows < CITIES)
    {
        min = 100;
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = temps[rows][columns];
            if(temp < min)
            {
                min = temp;
                city = rows;
                day = columns;
            }
            columns++;
        }
        
        printf("The coldest day in city %i was on day %i -> %ic\n", city+1, day+1, temps[city][day]);
        
        while(1)
        {
            columns=0;
            while(columns < DAYS)
            {
                if(min == temps[rows][columns] && columns != day)
                {
                    printf("The temp -> %ic in city %i was also on day %i\n", temps[city][columns], city+1, columns+1);
                }
                columns++;
            }
            break;
        }
        rows++;
    }
}

void calculate_temp_difference(void)
{
    unsigned char counter=0;
    int city_1;
    int city_2;
    float temp_difference=0;

    printf("Enter the first city's index\n");
    printf("Cities available:\n");
    while(counter < CITIES)
    {
        printf("city %i -> %i\n", counter+1, counter);
        counter++;
    }
    scanf("%i", &city_1);
    while(city_1 < 0 || city_1 > (CITIES-1))
    {
        printf("Enter an available city index: \n");
        scanf("%i", &city_1);
    }

    counter = 0;
    printf("Enter the second city's index\n");
    printf("Cities available:\n");
    while(counter < CITIES)
    {
        if(counter != city_1)
        {
        printf("city %i -> %i\n", counter+1, counter);
        }
        counter++;
    }
    scanf("%i", &city_2);
    while(city_2 < 0 || city_2 > (CITIES-1) || city_2 == city_1)
    {
        printf("Enter an available city index: \n");
        scanf("%i", &city_2);
    }

    // printf("%i\n", city_1);
    // printf("%i\n", city_2);
    // printf("%f\n", avg_temp_per_city[city_1]);
    // printf("%f\n", avg_temp_per_city[city_2]);

    temp_difference = avg_temp_per_city[city_1] - avg_temp_per_city[city_2];
    if(temp_difference < 0)
    {
        temp_difference *= -1;
    }

    // printf("%f\n", temp_difference);

    printf("The absolute temperature difference between city %i and city %i is: %.3f degrees.\n", city_1+1, city_2+1, temp_difference);

}

void temperature_alert(void)
{
    unsigned char rows=0;
    int temp;

    while(rows < CITIES)
    {
        unsigned char columns=0;
        while(columns < DAYS)
        {
            temp = temps[rows][columns];
            if(temp < 0)
            {
                printf("\nAlert !!!\nOn day %i in city %i The temp was extremely cold -> %ic\n", columns+1, rows+1, temp);
            }
            columns++;
        }
        rows++;
    }

}

void transpose_temps(void)
{
    printf("Temperature Matrix (Cities x Days):\n");
    printf("            ");
    for(int days=0; days < DAYS; days++)
    {
        printf("day %i   ", days+1);
    }
    printf("\n");
    for(unsigned char rows=0; rows < CITIES; rows++)
    {
        printf("city %i ->   ", rows+1);
            for(unsigned char columns=0; columns < DAYS; columns++)
            {
                printf("%i", temps[rows][columns]);
                unsigned char spaces = 8 - number_length(temps[rows][columns]);
                for(int space=0; space < spaces; space++)
                {
                  printf(" ");
                }
            }
        printf("\n");
    }

    int transpose_temps[DAYS][CITIES];

    for(unsigned char rows=0; rows < CITIES; rows++)
    {
        for(unsigned char columns=0; columns < DAYS; columns++)
        {
            transpose_temps[columns][rows] = temps[rows][columns];
        }
    }

    printf("==============================================\n");

    printf("Transposed Temperature Matrix (Days x Cities):\n");
    printf("            ");
    for(int cities=0; cities < CITIES; cities++)
    {
        printf("city %i   ", cities+1);
    }
    printf("\n");
    for(unsigned char rows=0; rows < DAYS; rows++)
    {
        printf("day %i ->    ", rows+1);
        for(unsigned char columns=0; columns < CITIES; columns++)
        {
            printf("%i", transpose_temps[rows][columns]);
            unsigned char spaces = 9 - number_length(transpose_temps[rows][columns]);
            for(int space=0; space < spaces; space++)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

unsigned int is_empty(void)
 {
    unsigned int empty_days=0;
    unsigned char rows=0;
                    
    while(rows < CITIES)
        {
            unsigned char columns=0;
            while(columns < DAYS)
                {
                    if(temps[rows][columns] == 0)
                    {
                        empty_days++;
                    }

                    columns++;
                }
                rows++;
        }
        return empty_days;
 }

 void clear_temps_indices(void)
 {
    unsigned int index = 0;
    // while(index < (CITIES*DAYS))
    // {
    //     printf("%i %i\n", temps_indices[index][1], temps_indices[index][2]);
    //     index++;
    // }
    // index = 0;
    while(index < (CITIES*DAYS))
    {
        temps_indices[index][1] = 0;
        temps_indices[index][2] = 0;
        index++;
    }    
    // printf("===================\n");
    // index = 0;
    // while(index < (CITIES*DAYS))
    // {
    //     printf("%i %i\n", temps_indices[index][1], temps_indices[index][2]);
    //     index++;
    // }
 }

 unsigned char number_length(int temp)
 {
    if(temp < 0)
    {
        temp *= -1;
    }

    unsigned char counter=0;
    while(temp > 0)
    {
        temp /= 10;
        counter++;
    }
    return counter;
 }