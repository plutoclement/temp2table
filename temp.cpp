#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "/usr/include/mysql/mysql.h"
#include "../RPI_Oregan/RCSwitch.h"
#include "../RPI_Oregan/RcOok.h"
#include "../RPI_Oregan/Sensor.h"
int loggingok;	

int main(int argc, char *argv[])
{
	int RXPIN = 2;
	int TXPIN = 0;
	time_t ltime;
    	struct tm * curtime;
	FILE *fp;	 // Global var file handle 
	char buffer[80];
	char query[256];
	char sensor_ID[2];
	
	if(argc==2) {
	  loggingok=1;
	} else {
	  loggingok=0;
	}
	
	
	


	if(wiringPiSetup() == -1)
		{
			return 0;
			printf("failed wiring pi\n");
		}	

	RCSwitch *rc = new RCSwitch(RXPIN,TXPIN);
	
	
    //printf("datetime,temperature,humidity,channel\n");
	while (1)
 		{
			if ( rc->OokAvailable() )
				{
					char message[100];
					time( &ltime );
					curtime = localtime( &ltime );
					strftime(buffer,80,"%F %T", curtime);

 
					
					
					rc->getOokCode(message);
					/* printf(" %s\n ",message); */

					Sensor *s = Sensor::getRightSensor(message);
					if ( s != NULL )
						{
						
sensor_ID[0]=message[11];
sensor_ID[1]=message[12];
							/*printf("%s,%f,%s\n",
							buffer,
							s->getTemperature(),
							//s->getHumidity(),
							sensor_ID);*/

MYSQL *connect;
connect=mysql_init(NULL);

if(!connect)
{
printf("Mysql initialization failed");
//return 1;
}

connect=mysql_real_connect(connect,"localhost","root","12850216","temperature_table",0,NULL,0);

if (connect)
{
//printf("connection to the database succeeded\n");
//sprintf(query,"insert into temp (date,hour,sensor_ID,temperature) values (\"14-01-2016\",\"22:55:31\",\"3\",0);");
//sprintf(query,"insert into temp (date_reception,sensor_ID,temperature) values (\"%s\",\"%d\",%f);",buffer,message,s->getTemperature());

//printf("%s,%f,%d\n",buffer,s->getTemperature(),//s->getHumidity(),s->getChannel());


sprintf(query,"insert into temp (date_reception,sensor_ID,temperature) values (\"%s\",\"%s\",%f);",buffer,sensor_ID,s->getTemperature());


mysql_query(connect,query);

}
else
{
printf("connection to the database failed\n");
}

mysql_close(connect);
						
//return 1;					
					
						

							if(loggingok) {
								fp = fopen(argv[1], "w");
    	 						
    	 						if (fp == NULL) {
	      							perror("Failed to open log file!"); // Exit if file open fails
	      							exit(EXIT_FAILURE);
								}
								
								fprintf(fp," {\"datetime\": \"%s\", \"temperature\": \"%f\", \"humidity\": \"%f\", \"channel\": \"%d\" } \n",
								buffer,
								s->getTemperature(),
								s->getHumidity(),
								s->getChannel());		
								fflush(fp);
								fclose(fp);
  							}
							
						}
					delete s;
				}
			delay(1000);
 		}
 	
}

