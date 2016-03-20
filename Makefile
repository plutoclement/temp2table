all: temp

temp: RCSwitch.o RcOok.o Sensor.o temp.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi -lmysqlclient

clean:
	$(RM) *.o sensor
