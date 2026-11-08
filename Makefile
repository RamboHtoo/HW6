all: rbt-tests

rbt-tests:
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTests.cpp -o rbt-tests

first-step:
	g++ -Wall -g RedBlackTree.cpp RedBlackTreeTestsFirstStep.cpp -o first-step

clean:
	rm -f first-step rbt-tests