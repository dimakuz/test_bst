#!/usr/bin/python
import argparse
import functools
import random
import sys


def tree(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        sys.stdout.write('t')
        return func(*args, **kwargs)
    return wrapper


def list_(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        sys.stdout.write('l')
        return func(*args, **kwargs)
    return wrapper


@tree
def tree_insert(n):
    print 'i%d' % n


@tree
def tree_insert_check(n):
    print 'I%d' % n


@tree
def tree_remove(n):
    print 'r%d' % n


@tree
def tree_remove_check(n):
    print 'R%d' % n


@tree
def tree_reset():
    print '*'


@tree
def tree_find_exact(n):
    print 'F%d' % n


@tree
def tree_find_exact_check(n):
    print 'w%d' % n


@tree
def tree_find(n):
    print 'f%d' % n


@tree
def tree_find_check(n):
    print 'G%d' % n


@tree
def tree_size_check(n):
    print 's%d' % n


@tree
def tree_neighbor_check(n, m):
    print 'n%d %d' % (n, m)


@tree
def tree_no_neighbor_check(n):
    print 'N%d' % n


@tree
def tree_from_list(lst):
    print '#%d %s' % (len(lst), ' '.join(map(lambda x: str(x), lst)))


@tree
def tree_clear():
    print 'c'


@list_
def list_append(n):
    print 'a%d' % n


@list_
def list_size(n):
    print 's%d' % n


@list_
def list_insert(n, m):
    print 'i%d %d' % (n, m)


@list_
def list_insert_check(n):
    print 'I%d' % n


@list_
def list_find(n, m):
    print 'f%d %d' % (n, m)


@list_
def list_find_check(n):
    print 'F%d' % n


@list_
def list_remove(n):
    print 'r%d' % n


@list_
def list_remove_check(n):
    print 'R%d' % n


@list_
def list_clear():
    print 'c'


@list_
def list_split_tail(n, lst):
    print 'S%d %d %s' % (n, len(lst), ' '.join(map(lambda x: str(x), lst)))


def quit():
    print 'q'


def tree_check_sanity(tree_set):
    sorted_tree_list = sorted(list(tree_set))
    for (idx, ele) in enumerate(sorted_tree_list):
        tree_insert_check(ele)
        tree_find_exact(ele)
        if len(tree_set) == 1:
            tree_no_neighbor_check(ele)
        elif ele == sorted_tree_list[0]:
            tree_neighbor_check(ele, sorted_tree_list[1])
        elif ele == sorted_tree_list[-1]:
            tree_neighbor_check(ele, sorted_tree_list[idx - 1])
    subject = 0
    if len(sorted_tree_list) > 0:
        tree_find(sorted_tree_list[-1] + 10)
        tree_find_exact_check(sorted_tree_list[-1] + 100)
        subject = sorted_tree_list[0] - 1
    else:
        tree_remove_check(0)
        tree_no_neighbor_check(0)
        tree_find_exact_check(0)
    tree_find_check(subject)
    tree_find_exact_check(subject)
    tree_size_check(len(tree_set))


def tree_random_order(order):
    in_tree = set()

    def get_rand():
        return random.randint(0 - order, order)

    for _ in xrange(order):
        if len(in_tree) == 0:
            new = get_rand()
            tree_insert(new)
            in_tree.add(new)
        else:
            if random.randint(0, 100) < 60:
                new = get_rand()
                while new in in_tree:
                    new = get_rand()
                in_tree.add(new)
                tree_insert(new)
            else:
                ele = in_tree.pop()
                tree_remove(ele)
                tree_remove_check(ele)
            tree_check_sanity(in_tree)

    while len(in_tree) > 0:
        tree_remove(in_tree.pop())
        tree_check_sanity(in_tree)


def list_check_sanity(lst):
    for (idx, ele) in enumerate(lst):
        list_find(idx, ele)
    list_insert_check(-1)
    list_insert_check(-2)
    list_insert_check(len(lst) + 1)
    list_insert_check(len(lst) + 2)
    list_remove_check(-1)
    list_remove_check(-2)
    list_remove_check(len(lst))
    list_remove_check(len(lst) + 2)
    list_find_check(-1)
    list_find_check(-2)
    list_find_check(len(lst))
    list_find_check(len(lst) + 2)
    list_size(len(lst))


def list_to_tree_conversion(order):
    lst = sorted(random.sample(xrange(order * 2), random.randint(0, order)))
    tree_from_list(lst)
    tree_check_sanity(lst)


def list_random_order(order):
    in_list = []

    def get_rand():
        return random.randint(0 - order, order)

    for _ in xrange(order):
        if len(in_list) == 0:
            in_list.append(get_rand())
            list_append(in_list[0])
            continue

        idx = random.randint(0, len(in_list) - 1)
        case = random.randint(0, 100)
        if case < 75:
            val = get_rand()

            in_list.insert(idx, val)
            list_insert(idx, val)
        elif case < 95:
            in_list.pop(idx)
            list_remove(idx)
        else:
            list_split_tail(idx, in_list[idx:])
            in_list = in_list[:idx]
        list_check_sanity(in_list)

    while len(in_list) > 0:
        idx = random.randint(0, len(in_list) - 1)
        in_list.pop(idx)
        list_remove(idx)
        list_check_sanity(in_list)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--tree-iters', '-t', type=int, dest='tree_iters',
                        help='Iterations of tree tests', default=20,
                        required=False)
    parser.add_argument('--tree-order', '-T', type=int, dest='tree_order',
                        help='Order of tree tests', default=1000,
                        required=False)
    parser.add_argument('--list-iters', '-l', type=int, dest='list_iters',
                        help='Iterations of list tests', default=10,
                        required=False)
    parser.add_argument('--list-order', '-L', type=int, dest='list_order',
                        help='Order of list tests', default=10000,
                        required=False)
    parser.add_argument('--conv-iters', '-c', type=int, dest='conv_iters',
                        help='Iterations of conv tests', default=100,
                        required=False)
    parser.add_argument('--conv-order', '-C', type=int, dest='conv_order',
                        help='Order of conv tests', default=10000,
                        required=False)

    args = parser.parse_args(sys.argv[1:])
    for i in xrange(args.tree_iters):
        sys.stderr.write('tree iter %d/%d\n' % (1 + i, args.tree_iters))
        tree_random_order(args.tree_order)
    for i in xrange(args.list_iters):
        sys.stderr.write('list iter %d/%d\n' % (1 + i, args.list_iters))
        list_random_order(args.list_order)
    for i in xrange(args.conv_iters):
        sys.stderr.write('conv iter %d/%d\n' % (1 + i, args.conv_iters))
        list_to_tree_conversion(args.conv_order)
    quit()

if __name__ == '__main__':
    main()
