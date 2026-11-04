all: first-step

first-step:
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o first-step

clean:
	rm -f first-step