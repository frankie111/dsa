from Bag import Bag


class Iterator:
    def __init__(self, bag: Bag):
        self.bag = bag
        self.i = 0

    def valid(self):
        return self.i in range(len(self.bag.lis))

    def first(self):
        return self.bag.lis[0] if self.valid() else False

    def next(self):
        if self.valid():
            self.i

    def get_current(self):
        pass
