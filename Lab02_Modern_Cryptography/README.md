# Lab 02: Mật mã học hiện đại 

## Lớp: NT101.Q21.1

## Danh sách thành viên Nhóm 6
| MSSV     | Họ và tên        |

| 24520397 | Trần Anh Duy     |

| 24520388 | Nguyễn Nhật Duy  |

| 24521070 | Nguyễn Nhật Minh |

## Mục tiêu bài thực hành

Bài thực hành giúp sinh viên làm quen và triển khai các khái niệm cốt lõi trong mật mã học hiện đại, bao gồm hệ mật mã khối (DES, AES), các chế độ hoạt động (Modes of Operation), phân tích tính chất của bản mã (Avalanche effect, Error propagation), và các phép toán lý thuyết số cơ sở cho hệ mật mã khóa công khai (RSA).

## Nội dung chính bài lab 2:

1. **Cấu trúc Feistel và Sự lan truyền thay đổi**: Triển khai thuật toán Feistel đơn giản và quan sát hiệu ứng lan truyền khi thay đổi 1 bit đầu vào.
2. **Mode of Operation (Chế độ hoạt động)**: Lập trình mã hóa văn bản lặp bằng thuật toán AES với chế độ ECB và CBC để so sánh mức độ che giấu cấu trúc dữ liệu.
3. **Avalanche Effect (Hiệu ứng thác đổ)**: Mã hóa 2 chuỗi bằng DES-ECB, đo khoảng cách Hamming (Hamming Distance) để chứng minh sự thay đổi ~50% số bit ở bản mã khi bản rõ thay đổi 1 bit
4. **Error Propagation (Lan truyền lỗi)**: Đánh giá mức độ ảnh hưởng của việc lật 1 bit bản mã (tại byte thứ 26) đối với quá trình giải mã trong các chế độ ECB, CBC, CFB, và OFB
5. **Lý thuyết Mật mã khối**: Tìm hiểu, phân tích ưu nhược điểm và so sánh các chuẩn DES, 3DES, và AES
6. **Mersenne Prime (Số nguyên tố lớn)**: Cài đặt thuật toán Miller-Rabin để sinh và kiểm tra số nguyên tố lớn, tính GCD (Euclid) và thuật toán tính lũy thừa theo modulo


