# temp2table

C++ routine writing the temperature received from 433 Mhz (with RPI_Oregan) in a mysql table

#Before first use, pleas do :

mysql -u root -p
(write your password)

create database temperature_table;
use temperature_table;

create table temp (date_reception datetime,sensor_ID varchar(255),temperature double);
quit


#Need RPI_oregan to work

git clone https://github.com/daveblackuk/RPI_Oregan.git

#Then do :

git clone https://github.com/plutoclement/temp2table.git
