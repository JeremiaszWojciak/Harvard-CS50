class Jar:
    def __init__(self, capacity=12):
        if capacity >= 0:
            self._capacity = capacity
        else:
            raise ValueError("Capacity must be non-negative.")
        self._cookies = 0

    def __str__(self):
        return self._cookies * "🍪"

    def deposit(self, n):
        if self._cookies + n <= self._capacity:
            self._cookies += n
        else:
            raise ValueError("Jar's capacity exceeded.")

    def withdraw(self, n):
        if self._cookies - n >= 0:
            self._cookies -= n
        else:
            raise ValueError("Not enough cookies in the jar.")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._cookies


def main():
    # Create an instance of Jar
    jar = Jar()

    # Print capacity
    print(str(jar.capacity))
    # Print jar
    print(str(jar))

    # Deposit 2 cookies
    jar.deposit(2)
    print(str(jar))

    # Withdraw 1 cookie
    jar.withdraw(1)
    print(str(jar))


main()
