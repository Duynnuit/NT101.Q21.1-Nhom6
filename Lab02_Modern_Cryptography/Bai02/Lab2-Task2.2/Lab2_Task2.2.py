from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

def split_blocks(data, block_size=16):
    return [data[i:i+block_size] for i in range(0, len(data), block_size)]

key = b'1234567890123456'
iv = b'0000000000000000'   
plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_"

print("Plaintext length:", len(plaintext))
print("Plaintext blocks:")
for i, block in enumerate(split_blocks(plaintext), 1):
    print(f"  Block {i}: {block} | hex = {block.hex()}")

cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)

cipher_cbc = AES.new(key, AES.MODE_CBC, iv)
ct_cbc = cipher_cbc.encrypt(plaintext)

print("AES-ECB:")
print("Ciphertext (hex):", ct_ecb.hex())
for i, block in enumerate(split_blocks(ct_ecb), 1):
    print(f"  Block {i}: {block.hex()}")

print("AES-CBC:")
print("Ciphertext (hex):", ct_cbc.hex())
for i, block in enumerate(split_blocks(ct_cbc), 1):
    print(f"  Block {i}: {block.hex()}")

ecb_blocks = split_blocks(ct_ecb)
cbc_blocks = split_blocks(ct_cbc)

print("Comparison:")
print("ECB block1 == block2 ?", ecb_blocks[0] == ecb_blocks[1])
print("CBC block1 == block2 ?", cbc_blocks[0] == cbc_blocks[1])
