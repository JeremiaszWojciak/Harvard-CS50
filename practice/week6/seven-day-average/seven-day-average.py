import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state in previous_cases:
            new_value = cases - previous_cases[state]

            if state not in new_cases:
                new_cases[state] = []
            new_cases[state].append(new_value)

            if len(new_cases[state]) > 14:
                new_cases[state].pop(0)

        previous_cases[state] = cases

    return new_cases


# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        if len(new_cases[state]) < 14:
            print(f"Not enough data for {state}.")
            continue

        last_week = new_cases[state][:7]
        this_week = new_cases[state][7:]
        last_week_avg = sum(last_week) / 7
        this_week_avg = sum(this_week) / 7

        try:
            percentage = ((this_week_avg - last_week_avg) / last_week_avg) * 100
        except ZeroDivisionError:
            percentage = 0

        direction = "an increase" if percentage >= 0 else "a decrease"
        print(f"{state} had a 7-day average of {round(this_week_avg)} and {direction} of {round(abs(percentage))}%.")


main()
