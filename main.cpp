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
		case 'i':
			std::cin >> i;
			t.insert(i);
			t.checkCorrectness();
			break;
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
		case 'r':
			std::cin >> i;
			t.remove(i);
			t.checkCorrectness();
			break;
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
		case 'F':
			std::cin >> i;
			if (i != t.findByParameter(IntParam(i)))
				throw std::exception();
			break;
		case 'f':
			std::cin >> i;
			if (i < t.findByParameter(IntParam(i)))
				throw std::exception();
			break;
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
		case 's':
			std::cin >> i;
			if (i != t.size())
				throw std::exception();
			break;
		case 'n':
			std::cin >> i >> j;
			if (j != t.getNeighbor(i))
				throw std::exception();
			break;
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
		case '*':
			t = AVLTree<int>();
			break;
		case 'q':
			stop = 1;
			break;
		}
	}
	if (t.size() != 0)
		return 1;
	return 0;
}
