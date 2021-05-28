#include "libs/libHuffman.h"
#include "libs/libArrays.h"

int main() {
	//number of signs to code
	int size{};
	//read from this file
	std::ifstream readFromFile;

	try {
		//open file
		OpenFile(readFromFile);
		readFromFile >> size;

		if (size < 1)
			throw MyRuntimeExceptions::NegativeNumberException();

		Element* huffman = CreateArray<Element>(size);
		std::priority_queue <Element, std::vector<Element>, std::greater<Element>> queue;

		//fill queue
		FillQ(queue, readFromFile, huffman, size);
		//show elements in queue
		std::cout << "Keys in queue: "; ShowPQ(queue);

		//create huffman coding
		CreateCoding(queue);

		//get root of the huffman coding tree
		Element root = queue.top();
		std::cout << std::endl;
		//show coding of signs
		ShowCoding(&root);
		DeleteArray(huffman);
	}
	catch (std::exception& err) {
		std::cerr << err.what();
	}

	return 0;
}

