from cs50 import get_string
import re

# Prompt for user
text = get_string("Text: ").lower()

# Length of letters, words and sentences
letters = 0
for i in text:
    if i.isalpha():
        letters += 1
        
words = len(text.split())
sentences = len(re.findall(r'[\.\!\?]', text))

# Calculate Coleman-Liau formula
index = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8

# Print grade level
grade = round(index)
if grade <= 0:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")