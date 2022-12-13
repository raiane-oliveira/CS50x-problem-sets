import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    with open(sys.argv[1], "r") as data:
        database = csv.DictReader(data)

        # Initialize variables
        STR_database = {}
        STRs_name = []
        tmp_list = []

        # Store database STRs in a list as dictionary values
        for person in database:
            for STR, values in person.items():
                if STR != "name":
                    tmp_list.append(int(values))
            STR_database[person["name"]] = tmp_list 
            tmp_list = []

        for STR in person:
            STRs_name.append(STR)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna:
        sequence = dna.read()

    # Find longest match of each STR in DNA sequence
    STR_sequence = []
    for i in range(1, len(STRs_name)):
        STR_sequence.append(longest_match(sequence, STRs_name[i]))

    # Check database for matching profiles
    for name, values in STR_database.items():
        if values == STR_sequence:
            print(name)
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()