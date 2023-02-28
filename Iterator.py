from Bag import Bag


class InvalidIteratorException(Exception):
    pass


class Iterator:
    def __init__(self, bag: Bag):
        self.bag = bag
        self.i = 0

    def valid(self, i=None):
        return self.i in range(len(self.bag.bag))

    def first(self):
        return self.bag.bag[0] if self.valid() else False

    def next(self):
        if self.valid(self.i + 1):
            self.i += 1
            return self.bag.bag[self.i]

        raise InvalidIteratorException

    def get_current(self):
        if self.valid():
            return self.bag.bag[self.i]

        raise InvalidIteratorException
