Chương trình **`filestat`** mô phỏng chức năng của lệnh `stat` trên Linux.  
Nó cho phép người dùng xem **thông tin chi tiết (metadata)** của một tệp hoặc thư mục, bao gồm loại, kích thước, và thời gian chỉnh sửa cuối cùng.

#Cấu trúc thư mục:
├── src/
│ └── filestat.c
├── makefile
└── README.md

#Mục tiêu

1. Đọc siêu dữ liệu (metadata) của một tệp bằng `lstat()`.
2. Xác định loại tệp (Regular file, Directory, Symbolic link).
3. Hiển thị kích thước và thời gian chỉnh sửa cuối cùng của tệp.
4. Thực hành sử dụng đối số dòng lệnh (`argc`, `argv`).

#Cách biên dịch và chạy
make clean all

./bin/filestat <đường_dẫn_tệp>