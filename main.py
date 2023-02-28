from Bag import Bag
from Iterator import Iterator


def bag_test():
    bag = Bag()

    assert bag.bag == []

    bag.add(1)

    assert bag.bag == [1]

    assert bag.search(1) is True

    assert bag.size() == 1

    bag.add(1)

    assert bag.nr_occurrences(1) == 2

    bag.remove(1)
    bag.remove(1)

    assert bag.bag == []


def iterator_test():
    bag = Bag()
    bag.bag = [1, 1, 2, 3]
    it = Iterator(bag)

    assert it.i == 0 and it.bag == bag

    assert it.first() == bag.bag[0]

    assert it.next() == bag.bag[1]

    assert it.get_current() == bag.bag[1]


bag_test()
iterator_test()
