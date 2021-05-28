#ifndef LIBHUFFMAN_H
#define LIBHUFFMAN_H
#include <queue>
#include "libFiles.h"

//one sign in Huffman coding 
class Element {
public:
	//sign occurance frequency
	float freq{};
	//sign or concatenation of signs
	std::string letter{};
	//0 or 1 depends on position in tree 
	char value{};
	//pointer to left child of a node
	Element* firstElement = nullptr;
	//pointer to right child of a node
	Element* secondElement = nullptr;

	void setLetter(std::string l) { letter = l; }

	Element() {
		freq = 0;
		letter = "";
		value = ' ';
	}

	Element(const Element& a) {
		freq = a.freq;
		letter = a.letter;
		value = a.value;
		firstElement = a.firstElement;
		secondElement = a.secondElement;
	}
};

//> operator overload needed for priority queue to work Element object
bool operator>(const Element& a, const Element& b);
/*
Show how all signs are coded
@param element root of huffman coding tree
@param currentString concatenation of values from root
*/
void ShowCoding(Element* element, std::string currentString = "");

/*
Show all elements in queue
@param originalQ queue to show
*/
void ShowPQ(std::priority_queue <Element, std::vector<Element>, std::greater<Element>> originalQ);

/*
Read items from file and add them to queue
@param queue add items to this queue
@param readFromFile read from this file
@param huffman add items to this array
@param size number of sings to code
*/
void FillQ(std::priority_queue <Element, std::vector<Element>, std::greater<Element>>& queue, std::ifstream& readFromFile, Element* huffman, int size);

/*
Create huffman coding for given set
@param queue operate on this queue to make coding
*/
void CreateCoding(std::priority_queue <Element, std::vector<Element>, std::greater<Element>>& queue);

/*
Check if string is a number
@param value string to check
*/
bool isNumber(std::string value);
#endif LIBHUFFMAN_H
