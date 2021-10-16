CC = g++ $(CFLAGS)
CFLAGS = -O0 -g

CubicEquation: Complex.h Complex.cpp CubicEquation.cpp
	$(CC) -o CubicEquation CubicEquation.cpp Complex.cpp -lm

clean:
	rm CubicEquation