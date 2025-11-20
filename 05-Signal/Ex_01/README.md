#Mục tiêu
Bắt tín hiệu SIGINT (được gửi khi nhấn Ctrl+C) và in ra thông báo khi nhận được tín hiệu này

#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/main

#Giải thích
+ Nhấn Ctrl+C sẽ không dừng chương trình. Tiến trình sẽ tiếp tục chạy như không có gì xảy ra. Chỉ khi gửi tín hiệu khác như SIGTERM hoặc kill -9 thì mới dừng.