#include <AVLTree.hpp>
#include <iostream>

class IntParam : public AbstractSearchParameter<int> {
private:
	int m_t;
public:
	IntParam(int t) : m_t(t) { }
	virtual int compare(int v) const;
};

int IntParam::compare(int v) const {
	return this->m_t - v;
}

int main() {
	AVLTree<int> t;
	int i = 0;
	int j;
	int stop = 0;
	char cmd;
	while (!stop) {
		std::cin >> cmd;
		switch (cmd) {
		// Correct insert
		case 'i':
			std::cin >> i;
			t.insert(i);
			t.checkCorrectness();
			break;
		// Incorrect insert
		case 'I':
			std::cin >> i;
			j = 0;
			try {
				t.insert(i);
			} catch (AVLTreeDuplicateElement) {
				j = 1;
			}
			if (!j)
				throw std::exception();
			break;
		// Correct remove
		case 'r':
			std::cin >> i;
			t.remove(i);
			t.checkCorrectness();
			break;
		// Incorrect remove
		case 'R':
			std::cin >> i;
			j = 0;
			try {
				t.remove(i);
			} catch (AVLTreeNoElementFound) {
				j = 1;
			}
			if (!j)
				throw std::exception();
			break;
		// Find exact element
		case 'F':
			std::cin >> i;
			if (i != t.findByParameter(IntParam(i)))
				throw std::exception();
			break;
		// Find less/equal element
		case 'f':
			std::cin >> i;
			if (i < t.findByParameter(IntParam(i)))
				throw std::exception();
			break;
		// Incorrect find
		case 'G':
			std::cin >> i;
			j = 0;
			try {
				t.findByParameter(IntParam(i));
			}
			catch (AVLTreeNoElementFound) {
				j = 1;
			}
			if (!j)
				throw std::exception();
			break;
		// Validate size
		case 's':
			std::cin >> i;
			if (i != t.size())
				throw std::exception();
			break;
		// Get neighbor
		case 'n':
			std::cin >> i >> j;
			if (j != t.getNeighbor(i))
				throw std::exception();
			break;
		// Validate no neighbor
		case 'N':
			std::cin >> i;
			j = 0;
			try {
				t.getNeighbor(i);
			}
			catch (AVLTreeNoElementFound) {
				j = 1;
			}
			if (!j)
				throw std::exception();
			break;
		// Reset tree
		case '*':
			t = AVLTree<int>();
			break;
		// Quit
		case 'q':
			stop = 1;
			break;
		}
	}
	if (t.size() != 0)
		return 1;
	return 0;
}
