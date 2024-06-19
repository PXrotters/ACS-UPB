number = int(input("Please enter a number: "))


reversed_number = int(str(number)[::-1])
print("Reversed number:", reversed_number)


def generate_prime(k):
    from sympy import randprime
    start = 10**(k-1)
    end = 10**k - 1
    return randprime(start, end)


prime_number = generate_prime(15)
print("15-digit prime number:", prime_number)
