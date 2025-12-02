#Mục tiêu
Tạo ra pipe để:

Process con 1 thực thi ls -l và gửi dữ liệu qua pipe.

Process con 2 nhận dữ liệu từ pipe và thực thi wc -l.

Kết quả cuối cùng giống như chạy lệnh trực tiếp trên terminal.

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
ubuntu@ubuntu:~/exersise/07-Pipe$ ./bin/main 
5
ubuntu@ubuntu:~/exersise/07-Pipe$ ls -l | wc -l
5

