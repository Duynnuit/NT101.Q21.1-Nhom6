from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad

BLOCK_SIZE = 16
KEY = bytes.fromhex('000102030405060708090a0b0c0d0e0f')
IV  = bytes.fromhex('101112131415161718191a1b1c1d1e1f')
CORRUPT_BYTE = 25

def encrypt_data(plaintext, mode_name):
    if mode_name == 'ECB':
        cipher = AES.new(KEY, AES.MODE_ECB)
        return cipher.encrypt(pad(plaintext, BLOCK_SIZE))
    elif mode_name == 'CBC':
        cipher = AES.new(KEY, AES.MODE_CBC, IV)
        return cipher.encrypt(pad(plaintext, BLOCK_SIZE))
    elif mode_name == 'CFB':
        cipher = AES.new(KEY, AES.MODE_CFB, IV)
        return cipher.encrypt(plaintext)
    elif mode_name == 'OFB':
        cipher = AES.new(KEY, AES.MODE_OFB, IV)
        return cipher.encrypt(plaintext)

def decrypt_data(ciphertext, mode_name):
    try:
        if mode_name == 'ECB':
            cipher = AES.new(KEY, AES.MODE_ECB)
            return unpad(cipher.decrypt(ciphertext), BLOCK_SIZE)
        elif mode_name == 'CBC':
            cipher = AES.new(KEY, AES.MODE_CBC, IV)
            return unpad(cipher.decrypt(ciphertext), BLOCK_SIZE)
        elif mode_name == 'CFB':
            cipher = AES.new(KEY, AES.MODE_CFB, IV)
            return cipher.decrypt(ciphertext)
        elif mode_name == 'OFB':
            cipher = AES.new(KEY, AES.MODE_OFB, IV)
            return cipher.decrypt(ciphertext)
    except Exception:
        return b''

def flip_bit(data, byte_idx):
    ba = bytearray(data)
    ba[byte_idx] ^= 0x80
    return bytes(ba)

def count_corrupted_blocks(original, recovered):
    length = min(len(original), len(recovered))
    corrupted = 0
    for i in range(0, length, BLOCK_SIZE):
        if original[i:i+BLOCK_SIZE] != recovered[i:i+BLOCK_SIZE]:
            corrupted += 1
    return corrupted

plaintext = (bytes(range(256)) * 4)[:1000]

print(f"Dữ liệu gốc     : {len(plaintext)} bytes")
print(f"Byte bị lật bit  : byte thứ {CORRUPT_BYTE+1} (index {CORRUPT_BYTE}, block {CORRUPT_BYTE//BLOCK_SIZE + 1})")
print("-" * 60)
print(f"{'Mode':<6} | {'Bytes sai':>9} | {'Blocks bị ảnh hưởng':>20} | {'Block nào'}")
print("-" * 60)

for mode in ['ECB', 'CBC', 'CFB', 'OFB']:
    ciphertext   = encrypt_data(plaintext, mode)
    corrupted_ct = flip_bit(ciphertext, CORRUPT_BYTE)
    recovered    = decrypt_data(corrupted_ct, mode)

    diff_bytes = [i for i in range(min(len(plaintext), len(recovered)))
                  if plaintext[i] != recovered[i]]
    n_corrupted = count_corrupted_blocks(plaintext, recovered)

    if diff_bytes:
        block_range = f"block {diff_bytes[0]//BLOCK_SIZE+1} -> block {diff_bytes[-1]//BLOCK_SIZE+1}"
    else:
        block_range = "(không có)"

    print(f"{mode:<6} | {len(diff_bytes):>9} | {n_corrupted:>20} | {block_range}")