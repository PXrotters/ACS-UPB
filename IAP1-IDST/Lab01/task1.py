message = input("Please enter a message: ")


reversed_message_1 = message[::-1]
print("Reversed message:", reversed_message_1)


alternate_case_message = ""
for i, char in enumerate(message):
    if i % 2 == 0:
        alternate_case_message += char.lower()
    else:
        alternate_case_message += char.upper()
print("Alternate case message:", alternate_case_message)


encrypted_message = ""
for char in message:
    if char.isalpha():
        if char.isupper():
            encrypted_message += chr((ord(char) - 65 + 17) % 26 + 65)
        else:
            encrypted_message += chr((ord(char) - 97 + 17) % 26 + 97)
    else:
        encrypted_message += char
print("Encrypted message:", encrypted_message)