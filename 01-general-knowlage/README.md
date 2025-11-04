Thư viện Tiện ích Xử lý Chuỗi (strutils)

Giới thiệu
Thư viện `strutils` là một **thư viện C** cung cấp các hàm tiện ích để xử lý chuỗi, bao gồm:
- `str_reverse`: Đảo ngược chuỗi tại chỗ (in-place).
- `str_trim`: Loại bỏ khoảng trắng ở đầu và cuối chuỗi.
- `str_to_int`: Chuyển đổi chuỗi sang số nguyên một cách an toàn.

Thư viện được xây dựng ở hai dạng:
- **Static library**: `libstrutils.a`
- **Shared library**: `libstrutils.so`

Cấu trúc thư mục:
project/
├── bin/
│ ├── main_static
│ └── main_shared
├── inc/
│ └── strutils.h
├── lib/
│ ├── static/
│ └── shared/
├── obj/
├── src/
│ ├── bstrutils.c
│ └── main.c
└── makefile

Build file thực thi:
make static #build file static lib
make shared #build file share lib
make all #build cả 2 lib
make clean #remove tất cả các file object và binaries

Run file thực thi:
Static lib: ./main_static
Shared lib: LD_LIBRARY_PATH=$(pwd)/lib/shared bin/main_shared