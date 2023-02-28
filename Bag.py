class Bag:
    def __init__(self):
        self.bag = []

    def add(self, e):
        self.bag.append(e)

    def remove(self, e):
        self.bag.remove(e)

    def search(self, e):
        return e in self.bag

    def size(self):
        return len(self.bag)

    def nr_occurrences(self, e):
        return self.bag.count(e)

    def destroy(self):
        pass

    def iterator(self, i):
        pass
