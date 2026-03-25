from Crypto.Cipher import DES

def hamming_distance(b1, b2):
    diff = int.from_bytes(b1, 'big') ^ int.from_bytes(b2, 'big')
    return bin(diff).count('1')

def avalanche_test():
    p1 = b'STAYHOME'
    p2 = b'STAYHOMA'
    
    keys = [b'87654321', b'24520397', b'24520388', b'24521070']
    print(f"{'Key':<12} | {'CT1 (hex)':<18} | {'CT2 (hex)':<18} | {'Hamming Dist':<15} | {'Tỷ lệ %'}")
    print("-" * 80)
    for k in keys:
        cipher1 = DES.new(k, DES.MODE_ECB)
        cipher2 = DES.new(k, DES.MODE_ECB)
        ct1 = cipher1.encrypt(p1)
        ct2 = cipher2.encrypt(p2)
        dist = hamming_distance(ct1, ct2)
        percent = (dist / 64) * 100
        print(f"{k.decode():<12} | {ct1.hex():<18} | {ct2.hex():<18} | {dist:>10}/64 bit | {percent:>6.2f}%")

if __name__ == "__main__":
    avalanche_test()