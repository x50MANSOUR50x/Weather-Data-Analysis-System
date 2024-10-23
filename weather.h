#ifndef _WEATHER_H_
#define _WEATHER_H_
void start(void); 
void input_temperatures(void);
void calculate_average_temp(unsigned char value);
void find_hottest_day(void);
void find_coldest_day(void);
void find_hotest_day_per_city(void);
void find_coldest_day_per_city(void);
void calculate_temp_difference(void);
void temperature_alert(void);
void transpose_temps(void);
unsigned int is_empty(void);
void clear_temps_indices(void);
unsigned char number_length(int temp);
#endif 