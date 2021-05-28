#include "libHuffman.h"

void ShowCoding(Element* element, std::string currentString)
{
	if (element == nullptr)
		return;
	currentString += element->value;
	if (element->firstElement != nullptr)
		ShowCoding(element->firstElement, currentString);

	if (element->secondElement != nullptr)
		ShowCoding(element->secondElement, currentString);

	if (element->letter.length() == 1)
		std::cout << element->letter << " = " << currentString << "\n";
}

bool operator>(const Element& a, const Element& b) {
	return a.freq > b.freq;
}

void ShowPQ(std::priority_queue <Element, std::vector<Element>, std::greater<Element>> originalQ)
{
	std::priority_queue <Element, std::vector<Element>, std::greater<Element>> tempQ = originalQ;
	while (!tempQ.empty())
	{
		std::cout << " " << tempQ.top().freq;
		tempQ.pop();
	}

}

void FillQ(std::priority_queue <Element, std::vector<Element>, std::greater<Element>>& queue, std::ifstream& readFromFile, Element* huffman, int size) {
	std::string line{};
	std::string value{};
	float f;
	char s;
	for (int i = 0; i < size; i++) {
		std::getline(readFromFile, line);
		if (line == "")
			std::getline(readFromFile, line);

		std::istringstream iss(line);
		while (iss.peek() != EOF) {
			iss >> value;
			if (value.length() > 1)
				throw MyRuntimeExceptions::InputDataException();
			s = value[0];
			iss >> value;
			if (isNumber(value) == false)
				throw MyRuntimeExceptions::InputDataException();
			f = stof(value);
			huffman[i].letter = s;
			huffman[i].freq = f;
		}
	}
	for (int i = 0; i < size; i++)
		queue.push(huffman[i]);

}

bool isNumber(std::string value)
{
	//check if all chars in srting are numbers
	for (int i = 0; i < value.length(); i++) {
		if (isdigit(value[i]) == false and value[i] != '.')
			return false;
	}
	return true;
}

void CreateCoding(std::priority_queue <Element, std::vector<Element>, std::greater<Element>>& queue) {
	Element temp1;
	Element temp2;

	//Take two lowest priority elements, merge it to one and add to queue
	while (queue.size() >= 2) {
		Element* temp = new Element;

		temp1 = queue.top();
		queue.pop();
		temp1.value = '0';
		Element* wsk1 = new Element(temp1);
		temp2 = queue.top();
		queue.pop();
		temp2.value = '1';
		Element* wsk2 = new Element(temp2);

		temp->freq = temp1.freq + temp2.freq;
		temp->letter = temp1.letter + temp2.letter;
		//point to child nodes
		temp->firstElement = wsk1;
		temp->secondElement = wsk2;

		queue.push(*temp);


		std::cout << "\nKeys in queue: "; ShowPQ(queue);
	}
}