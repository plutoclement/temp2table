all: temp

temp: ../RPI_Oregan/RCSwitch.o ../RPI_Oregan/RcOok.o ../RPI_Oregan/Sensor.o temp.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lmysqlclient

clean:
	$(RM) *.o sensor
