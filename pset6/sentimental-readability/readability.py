from cs50 import get_string


def main():
    # Prompt the user for input text
    text = get_string("Text: ")

    # Count the number of letters, words, and sentences in the text
    num_letters = count_letters(text)
    num_words = count_words(text)
    num_sentences = count_sentences(text)

    # Compute the Coleman-Liau index
    L = (num_letters / num_words) * 100
    S = (num_sentences / num_words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print the grade level
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    num_letters = 0
    for c in text:
        if c.isalpha():
            num_letters += 1
    return num_letters


def count_words(text):
    num_words = 0
    for c in text:
        if c.isspace():
            num_words += 1
    num_words += 1
    return num_words


def count_sentences(text):
    num_sentences = 0
    for c in text:
        if c == "." or c == "!" or c == "?":
            num_sentences += 1
    return num_sentences


main()
