#Mục tiêu
- Tạo tiến trình con bằng `fork()`
- Thực thi tiến trình con và tiến trình cha song song
- Kết thúc tiến trình con bằng `exit()`
- Tiến trình cha chờ tiến trình con hoàn thành bằng `wait()`
- Thu thập mã thoát của tiến trình con bằng `WIFEXITED()` và `WEXITSTATUS()`

#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/main