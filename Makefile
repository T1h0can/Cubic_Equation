CC = g++ $(CFLAGS)
CFLAGS = -O0 -g

#complexTst: Complex.h Complex.cpp complexTst.cpp
#	$(CC) -o complexTst complexTst.cpp Complex.cpp

CubicEquation: Complex.h Complex.cpp CubicEquation.cpp
	$(CC) -o CubicEquation CubicEquation.cpp Complex.cpp -lm

clean:
	rm CubicEquation
	#rm -f complexTst