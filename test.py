#!/usr/bin/python
import random
import sys


def insert(n):
    print 'i%d' % n


def insert_check(n):
    print 'I%d' % n


def remove(n):
    print 'r%d' % n


def remove_check(n):
    print 'R%d' % n


def reset():
    print '*'


def quit():
    print 'q'


def find_exact(n):
    print 'F%d' % n


def find(n):
    print 'f%d' % n


def find_check(n):
    print 'G%d' % n


def size_check(n):
    print 's%d' % n


def neighbor_check(n, m):
    print 'n%d %d' % (n, m)


def no_neighbor_check(n):
    print 'N%d' % n


def check_sanity(tree_set):
    sorted_tree_list = sorted(list(tree_set))
    for (idx, ele) in enumerate(sorted_tree_list):
        insert_check(ele)
        find_exact(ele)
        if len(tree_set) == 1:
            no_neighbor_check(ele)
        elif ele == sorted_tree_list[0]:
            neighbor_check(ele, sorted_tree_list[1])
        elif ele == sorted_tree_list[-1]:
            neighbor_check(ele, sorted_tree_list[idx - 1])
    subject = 0
    if len(sorted_tree_list) > 0:
        find(sorted_tree_list[-1] + 10)
        subject = sorted_tree_list[0] - 1
    find_check(subject)
    size_check(len(tree_set))


def random_order():
    in_tree = set()
    ORDER = int(sys.argv[1])

    def get_rand():
        return random.randint(0 - ORDER, ORDER)

    for _ in xrange(ORDER):
        if len(in_tree) == 0:
            new = get_rand()
            insert(new)
            in_tree.add(new)
        else:
            if random.randint(0, 100) < 60:
                new = get_rand()
                while new in in_tree:
                    new = get_rand()
                in_tree.add(new)
                insert(new)
            else:
                ele = in_tree.pop()
                remove(ele)
                remove_check(ele)
            check_sanity(in_tree)

    while len(in_tree) > 0:
        remove(in_tree.pop())
        check_sanity(in_tree)


def main():
    random_order()
    quit()

if __name__ == '__main__':
    main()
