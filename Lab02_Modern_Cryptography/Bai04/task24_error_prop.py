"""
Task 2.4 - SEED Lab: Error Propagation in AES modes
Nhóm 06 - NT101.Q21.1
Thực hiện: tạo 1000 byte, mã hóa AES-128, lật 1 bit tại byte 26, giải mã và quan sát.
"""

import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding

BLOCK_SIZE = 16   # AES block = 16 bytes
KEY = bytes.fromhex('000102030405060708090a0b0c0d0e0f')
IV  = bytes.fromhex('101112131415161718191a1b1c1d1e1f')
CORRUPT_BYTE = 25  # index 25 = byte thứ 26 (0-indexed)

def pkcs7_pad(data):
    padder = padding.PKCS7(128).padder()
    return padder.update(data) + padder.finalize()

def pkcs7_unpad(data):
    try:
        unpadder = padding.PKCS7(128).unpadder()
        return unpadder.update(data) + unpadder.finalize()
    except Exception:
        return data

def make_cipher(mode_name):
    if mode_name == 'ECB':
        return Cipher(algorithms.AES(KEY), modes.ECB(), backend=default_backend())
    elif mode_name == 'CBC':
        return Cipher(algorithms.AES(KEY), modes.CBC(IV), backend=default_backend())
    elif mode_name == 'CFB':
        return Cipher(algorithms.AES(KEY), modes.CFB(IV), backend=default_backend())
    elif mode_name == 'OFB':
        return Cipher(algorithms.AES(KEY), modes.OFB(IV), backend=default_backend())

def encrypt_data(plaintext, mode_name):
    if mode_name in ('ECB', 'CBC'):
        padded = pkcs7_pad(plaintext)
    else:
        padded = plaintext
    c = make_cipher(mode_name)
    enc = c.encryptor()
    return enc.update(padded) + enc.finalize()

def decrypt_data(ciphertext, mode_name):
    c = make_cipher(mode_name)
    dec = c.decryptor()
    raw = dec.update(ciphertext) + dec.finalize()
    if mode_name in ('ECB', 'CBC'):
        return pkcs7_unpad(raw)
    return raw

def flip_bit(data, byte_idx):
    """Đảo bit đầu tiên của byte tại byte_idx"""
    ba = bytearray(data)
    ba[byte_idx] ^= 0x80   # flip MSB
    return bytes(ba)

def count_corrupted_blocks(original, recovered):
    """Đếm số block 16-byte bị ảnh hưởng"""
    length = min(len(original), len(recovered))
    corrupted = 0
    for i in range(0, length, BLOCK_SIZE):
        blk_o = original[i:i+BLOCK_SIZE]
        blk_r = recovered[i:i+BLOCK_SIZE]
        if blk_o != blk_r:
            corrupted += 1
    return corrupted

def analyze_corruption(original, recovered):
    """Phân tích chi tiết từng byte bị sai"""
    length = min(len(original), len(recovered))
    diff_bytes = [i for i in range(length) if original[i] != recovered[i]]
    return diff_bytes

# ---- Main ----
print("="*65)
print("  NHIỆM VỤ 2.4 - ERROR PROPAGATION IN AES MODES")
print("="*65)

# Tạo 1000 byte dữ liệu có thể đọc được (dễ quan sát)
plaintext = bytes(range(256)) * 4  # 1024 byte, lấy 1000
plaintext = plaintext[:1000]
print(f"\n[*] Kích thước dữ liệu gốc    : {len(plaintext)} bytes")
print(f"[*] Byte bị lật bit           : byte thứ {CORRUPT_BYTE+1} (index {CORRUPT_BYTE})")
print(f"[*] Vị trí trong ciphertext   : block thứ {CORRUPT_BYTE // BLOCK_SIZE + 1} "
      f"(byte {CORRUPT_BYTE % BLOCK_SIZE + 1} trong block)")

MODES = ['ECB', 'CBC', 'CFB', 'OFB']

for mode in MODES:
    print(f"\n{'─'*65}")
    print(f"  Chế độ: AES-{mode}")
    print(f"{'─'*65}")

    # Bước 1: Mã hóa
    ciphertext = encrypt_data(plaintext, mode)

    # Bước 2: Làm hỏng bản mã
    corrupted_ct = flip_bit(ciphertext, CORRUPT_BYTE)

    # Bước 3: Giải mã bản mã bị lỗi
    recovered = decrypt_data(corrupted_ct, mode)

    # Bước 4: So sánh kết quả
    n_blocks_ct  = len(ciphertext) // BLOCK_SIZE
    n_corrupted  = count_corrupted_blocks(plaintext, recovered)
    diff_bytes   = analyze_corruption(plaintext, recovered)

    corrupt_block_idx = CORRUPT_BYTE // BLOCK_SIZE  # 0-indexed

    print(f"  Tổng số block                      : {n_blocks_ct}")
    print(f"  Số byte bị sai trong bản rõ phục hồi: {len(diff_bytes)}")
    print(f"  Số block bị ảnh hưởng              : {n_corrupted}")

    if len(diff_bytes) > 0:
        first_diff_block = diff_bytes[0] // BLOCK_SIZE
        last_diff_block  = diff_bytes[-1] // BLOCK_SIZE
        print(f"  Block bị ảnh hưởng                 : block {first_diff_block+1} → block {last_diff_block+1}")
    else:
        print(f"  Block bị ảnh hưởng                 : (không có)")

    # Giải thích
    if mode == 'ECB':
        print("""
  Phân tích ECB:
    - Mỗi block mã hóa độc lập → lỗi chỉ ảnh hưởng đúng 1 block chứa
      byte bị lật (block 2, vì byte 26 ∈ [16..31]).
    - Block 1 và các block sau không bị ảnh hưởng.""")

    elif mode == 'CBC':
        print("""
  Phân tích CBC:
    - Block chứa lỗi (block 2) bị hỏng hoàn toàn khi giải mã.
    - Block kế tiếp (block 3) bị hỏng đúng 1 bit tương ứng do XOR
      với ciphertext bị lỗi trong bước giải mã CBC.
    - Từ block 4 trở đi: bình thường. → Tổng 2 block bị ảnh hưởng.""")

    elif mode == 'CFB':
        print("""
  Phân tích CFB:
    - CFB xử lý từng segment (thường 16 byte = 1 block AES mặc định).
    - Block chứa lỗi bị sai hoàn toàn; block kế tiếp cũng bị ảnh hưởng
      do feedback chain. → Tương tự CBC: ~2 block bị ảnh hưởng.""")

    elif mode == 'OFB':
        print("""
  Phân tích OFB:
    - OFB tạo keystream độc lập với ciphertext → lỗi không lan truyền.
    - Chỉ byte đúng tại vị trí bị lật (byte 26) của bản rõ phục hồi
      bị sai, các byte và block khác hoàn toàn không bị ảnh hưởng.""")

print(f"\n{'='*65}")
print("  TỔNG KẾT SO SÁNH")
print(f"{'='*65}")
print(f"  {'Mode':<8} {'Số block ảnh hưởng':<25} {'Đặc điểm lan truyền lỗi'}")
print(f"  {'─'*60}")
summary = {
    'ECB': ('1 block (block chứa lỗi)',        'Không lan truyền'),
    'CBC': ('2 block (block lỗi + kế tiếp)',   'Lan truyền 1 block'),
    'CFB': ('2 block (block lỗi + kế tiếp)',   'Lan truyền 1 block'),
    'OFB': ('1 byte (chỉ byte bị lật)',        'Không lan truyền'),
}
for m, (blocks, prop) in summary.items():
    print(f"  {m:<8} {blocks:<25} {prop}")

print("""
NHẬN XÉT CHUNG:
  - ECB và OFB: lỗi KHÔNG lan truyền ra ngoài vùng bị lỗi.
  - CBC và CFB: lỗi LAN TRUYỀN sang block tiếp theo.
  - OFB an toàn nhất cho kênh truyền nhiễu vì lỗi chỉ ảnh hưởng đúng
    bit/byte tương ứng.
  - Trong thực tế, CBC được dùng rộng rãi nhưng cần integrity check
    (MAC/HMAC) để phát hiện giả mạo.
""")
