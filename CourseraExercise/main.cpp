#include <iostream>
#include "Cube.h"
#include <stdlib.h>
#include <time.h>
#include <random>
#include "NamespaceTest.cpp"
#include <math.h>
#include "Game.h"

using namespace std;

void testCube() {
	Cube* c1 = new Cube();
	Cube* c2 = c1;
	cout << c2 << endl;
	c2->setLength(10);
	Cube &cube = *c2;
	cout << c2 << endl;
	c2->setLength(20);
	double* length_Reference = c2->getLengthReference();
	*length_Reference = 30;

	delete c2;
	cout << c2 << endl;
	cube.setLength(40);
}

void testReference() {
	int* x = new int;
	int &y = *x;
	*x = 4;

	cout << "*x = " << *x << endl;
	cout << "y = " << y << endl;
	y = 10;
	cout << "*x = " << *x << endl;
	cout << "y = " << y << endl;
}

void testArray() {
	const int size = 3;
	int* x = new int[size];
	int* x_array[size];
	int x_values[size];

	for (int i = 0; i < size; i++) {
		x_array[i] = x + i;
	}

	for (int i = 0; i < size; i++) {
		x[i] = i + 10;
		x_values[i] = *(x + i);
	}

	cout << "x = " << x << endl;
	cout << "(x + 1) = " << *(x + 1) << endl;

	delete[] x;
	x = nullptr;
}

void testDestructor() {
	Cube c;
	Cube* p = new Cube();
	delete p;
}

class A {};

class B {
public:
	// conversion from A (constructor):
	B(const A& x) {}
	// conversion from A (assignment):
	B& operator= (const A& x) { return *this; }
	// conversion to A (type-cast operator)
	operator A() { return A(); }
};

void complex_casting_example()
{
	A foo;
	B bar = foo;    // calls constructor
	bar = foo;      // calls assignment
	foo = bar;      // calls type-cast operator
}

//
//string randomColour() {
//	char colours[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
//	
//	std::random_device rd;
//	std::default_random_engine eng(rd());
//	std::uniform_int_distribution<int> distr(0, 15);
//	
//	//string colour = (string)colours[distr(eng)]
//}

int* allocate_an_integer() {
	int i = 0;
	return &i;
}

double newtons_method() {
	double x = 200;
	
	// (sin(x))^2 - 5 = 0
	// log(x)^2 - 5 = 0

	for (int i = 0; i < 1000; i++) {
		x -= (log(x) * log(x) - 5) / (2 * log(x) / x);
	}

	return x;
}

class Pair {
	public:
	int* pa, * pb;
	Pair(int a, int b) {
		pa = new int(a);
		pb = new int(b);
		cout << "Custom constructor\n";
	}

	Pair(const Pair& other) {
		pa = new int(*other.pa);
		pb = new int(*other.pb);
		cout << "Copy constructor\n";
	}

	~Pair() {
		cout << "Destructor\n";
	}
	
};

void week3Challenge() {
	Pair p(15, 16);
	Pair q(p);
	Pair* hp = new Pair(23, 42);
	delete hp;

	std::cout << "If this message is printed,"
		<< " at least the program hasn't crashed yet!\n"
		<< "But you may want to print other diagnostic messages too." << std::endl;
}


int main() {
	//complex_casting_example();
	//testCube();
	//testReference();
	//testArray();
	//testDestructor();
	//system("color 2c");
	
	/*int i = 0;
	int* j = &i;

	cout << NSP1::square_(5) << endl << NSP2::multiply_(4, 5) << endl;*/
	//cout << newtons_method() << "\n" << "hello there";

	//week3Challenge();
	Game game = Game(3, 0, 2, 2);
	game.initialiseCubes();

	return 0;
}