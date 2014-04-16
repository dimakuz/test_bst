#include <AVLTree.hpp>
#include <List.hpp>
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


class IntWalkParam : public AbstractWalkParameter<int> {
private:
	int m_off;
public:
	IntWalkParam(int off) : m_off(off)  { }
	virtual ~IntWalkParam() { }
	virtual void apply(int &v);
};

void IntWalkParam::apply(int &v) {
	v += this->m_off;
}

static int handleTreeCommand(AVLTree<int> &t, List<int> &l) {
	int i, j;
	char cmd;

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
		t.findExactByParameter(IntParam(i));
		break;
	case 'w':
		std::cin >> i;
		j = 0;
		try {
			t.findExactByParameter(IntParam(i));
		} catch (AVLTreeNoElementFound) {
			j++;
		}
		if (!j)
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
	// Rebuild from list
	case '#':
		{
			int k;
			List<int> lst;
			std::cin >> j;
			while (j--) {
				std::cin >> k;
				lst.append(k);
			}
			t.reinitializeFromList(lst);
			lst.clear();
		}
		t.checkCorrectness();
		break;
	case 'W':
		{
			IntWalkParam p(1);
			t.walkNodes(p);
			t.checkCorrectness();
		}
		break;
	case 'c':
		t.clear();
	// Reset tree
	case '*':
		t = AVLTree<int>();
		break;
	}
}

static int handleListCommand(AVLTree<int> &t, List<int> &l) {
	int i, j, k;
	char cmd;
	std::cin >> cmd;
	switch (cmd) {
	// Append to list
	case 'a':
		std::cin >> i;
		l.append(i);
		break;
	// Check size
	case 's':
		std::cin >> i;
		if (i != l.size())
			throw std::exception();
		break;
	// Insert at
	case 'i':
		std::cin >> i >> j;
		l.insertBefore(l.begin().advance(i), j);
		break;
	// Check insert throws:
	case 'I':
		std::cin >> i;
		j = 0;
		try {
			l.insertBefore(l.begin().advance(i), 0);
		} catch (ListException) {
			j++;
		}
		if (!j)
			throw std::exception();
		break;
	// Find at
	case 'f':
		std::cin >> i >> j;
		if (j != *(l.begin().advance(i)))
			throw std::exception();
		break;
	// Check find thatthrows:
	case 'F':
		std::cin >> i;
		j = 0;
		try {
			*l.begin().advance(i);
		} catch (ListException) {
			j++;
		}
		if (!j)
			throw std::exception();
		break;
	// Remove at
	case 'r':
		std::cin >> i;
		l.removeAt(l.begin().advance(i));
		break;
	case 'R':
		std::cin >> i;
		j = 0;
		try {
			l.removeAt(l.begin().advance(i));
		} catch (ListException) {
			j++;
		}
		if (!j)
			throw std::exception();
		break;
	// Split tail
	case 'S':
		{
			List<int> other;
			std::cin >> i;
			l.splitTail(other, l.begin().advance(i));
			std::cin >> j;
			if (j != other.size())
				throw std::exception();
			List<int>::Iterator itr = other.begin();
			while (itr != other.end()) {
				std::cin >> k;
				if (k != *itr)
					throw std::exception();
				itr++;
			}
		}
	break;
	// Clear list
	case 'c':
		l.clear();
		break;

	}
}

int main() {
	AVLTree<int> t;
	List<int> l;
	int i = 0;
	int j;
	int stop = 0;
	char cmd;
	int skip = 0;
	while (!stop) {
		if (!skip)
			std::cout << "";
		std::cin >> cmd;
		switch (cmd){
		case 't':
			handleTreeCommand(t, l);
			skip = 0;
			break;
		case 'l':
			handleListCommand(t, l);
			skip = 0;
			break;
		// Quit
		case 'q':
			stop = 1;
			break;
		default:
			skip = 1;
		}
	}
	if (t.size() != 0)
		return 1;
	return 0;
}
