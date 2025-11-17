#Mục tiêu
Trong các hệ thống có tần suất đọc dữ liệu cao hơn nhiều so với ghi, sử dụng
Mutex có thể gây tắc nghẽn không cần thiết. Read-Write Lock là một cơ chế khóa
chuyên biệt, cho phép nhiều luồng đọc đồng thời nhưng vẫn đảm bảo tính độc
quyền cho luồng ghi.
#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/main

#Kết quả

[Reader 3] Đọc data = 0
[Reader 4] Đọc data = 0
[Reader 5] Đọc data = 0
[Reader 2] Đọc data = 0
>>> [Writer 2] Ghi data = 1
[Reader 1] Đọc data = 0
>>> [Writer 1] Ghi data = 2
[Reader 3] Đọc data = 2
[Reader 2] Đọc data = 2
[Reader 1] Đọc data = 2
[Reader 4] Đọc data = 2
[Reader 5] Đọc data = 2
>>> [Writer 1] Ghi data = 3
[Reader 3] Đọc data = 3
>>> [Writer 2] Ghi data = 4
[Reader 4] Đọc data = 4
[Reader 2] Đọc data = 4
[Reader 1] Đọc data = 4
[Reader 5] Đọc data = 4
[Reader 3] Đọc data = 4
[Reader 4] Đọc data = 4
[Reader 2] Đọc data = 4
[Reader 1] Đọc data = 4
[Reader 5] Đọc data = 4
>>> [Writer 2] Ghi data = 5
>>> [Writer 1] Ghi data = 6
[Reader 3] Đọc data = 6
[Reader 4] Đọc data = 6
[Reader 2] Đọc data = 6
[Reader 1] Đọc data = 6
[Reader 5] Đọc data = 6
>>> [Writer 2] Ghi data = 7
>>> [Writer 1] Ghi data = 8
>>> [Writer 1] Ghi data = 9
>>> [Writer 2] Ghi data = 10

