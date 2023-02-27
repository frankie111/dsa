class Bag:
    def __init__(self):
        self.lis = []

    def add(self, e):
        self.lis.append(e)

    def remove(self, e):
        self.lis.remove(e)

    def search(self, e):
        return e in self.lis

    def size(self):
        return len(self.lis)

    def nr_occurrences(self, e):
        self.lis.count(e)

    def destroy(self):
        pass

    def iterator(self, i):
        pass
