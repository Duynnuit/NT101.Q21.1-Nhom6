import random

def is_prime(n, k=10):
    if n < 2:
        return False
    small_primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    for p in small_primes:
        if n == p:
            return True
        if n % p == 0 and n != p:
            return False
    d = n - 1
    r = 0
    while d % 2 == 0:
        d //= 2
        r += 1

    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue

        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False

    return True

def generate_prime(bits):
    while True:
        n = random.getrandbits(bits)
        n |= (1 << (bits - 1))   
        n |= 1                   
        if is_prime(n):
            return n

def prev_prime(n):
    if n <= 2:
        return None
    candidate = n - 1
    if candidate % 2 == 0:
        candidate -= 1
    while candidate >= 2:
        if is_prime(candidate):
            return candidate
        candidate -= 2
    return None

def ten_largest_primes_below(n):
    result = []
    current = n
    for _ in range(10):
        current = prev_prime(current)
        result.append(current)
    return result

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return abs(a)

def mod_exp(a, x, p):
    result = 1
    a = a % p
    while x > 0:
        if x % 2 == 1:
            result = (result * a) % p
        a = (a * a) % p
        x //= 2
    return result

if __name__ == "__main__":
    random.seed()

    print("1. So nguyen to ngau nhien")
    p8 = generate_prime(8)
    p16 = generate_prime(16)
    p64 = generate_prime(64)

    print("8-bit:", p8)
    print("16-bit:", p16)
    print("64-bit:", p64)

    print("\n2. 10 so nguyen to lon nhat nho hon so nguyen to Mersenne thu 10")
    mersenne_10 = 2**89 - 1
    print("M10 = 2^89 - 1 =", mersenne_10)
    print("Is M10 prime?", is_prime(mersenne_10))

    primes_below = ten_largest_primes_below(mersenne_10)
    for i, val in enumerate(primes_below, 1):
        print(f"{i}: {val}")

    print("\n3. Kiem tra so nguyen tuy y < 2^89 - 1 co phai so nguyen to khong")
    test_num = 123456789101112131
    print(f"{test_num} is prime? {is_prime(test_num)}")

    print("\n4. GCD cua 2 so nguyen lon tuy y")
    a = 1234567891011121314151617181920
    b = 987654321011121314151617181920
    print(f"gcd(a, b) = {gcd(a, b)}")

    print("\n5. Tinh luy thua")
    print("7^40 mod 19 =", mod_exp(7, 40, 19))
