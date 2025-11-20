#Mục tiêu
Tạo một bộ đếm thời gian bằng cách sử dụng tín hiệu SIGALRM
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
+ Bộ đếm sẽ chỉ hoạt động đúng 1 lần. Không có tín hiệu SIGALRM nào tiếp theo. Timer không bao giờ đạt 10 giây.
