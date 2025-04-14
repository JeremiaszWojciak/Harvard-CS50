from cs50 import get_float


def main():
    # Prompt the user for change owed
    while True:
        change = get_float("Change owed($): ")
        if change >= 0:
            break

    # Convert dollars to cents
    change = round(change * 100)

    # Calculate how many quarters you should give customer
    quarters = calculate_quarters(change)
    change = change - quarters * 25

    # Calculate how many dimes you should give customer
    dimes = calculate_dimes(change)
    change = change - dimes * 10

    # Calculate how many nickels you should give customer
    nickels = calculate_nickels(change)
    change = change - nickels * 5

    # Calculate how many pennies you should give customer
    pennies = calculate_pennies(change)
    change = change - pennies * 1

    # Sum the number of quarters, dimes, nickels, and pennies used
    sum = quarters + dimes + nickels + pennies
    # Print that sum
    print(sum)


def calculate_quarters(change):
    return change // 25


def calculate_dimes(change):
    return change // 10


def calculate_nickels(change):
    return change // 5


def calculate_pennies(change):
    return change // 1


main()
