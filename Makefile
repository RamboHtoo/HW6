all: first-step

first-step:
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o first-step

rbt-tests:
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

clean:
	rm -f first-step rbt-tests