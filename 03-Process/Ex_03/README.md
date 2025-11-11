#Mục tiêu
Quan sát và phân tích hai trạng thái đặc biệt thường gặp trong quản lý tiến trình
là Zombie và Orphan.

#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/main Zombie
./bin/main Orphan

#Giải thích
+ Tiến trình con đã kết thúc (exit(0)), nhưng tiến trình cha chưa gọi wait(). Kernel giữ lại entry trong process table để lưu mã thoát của con. Dẫn đến tiến trình con trở thành Zombie. Zombie không tiêu tốn CPU, nhưng nếu cha không thu dọn, bảng tiến trình sẽ đầy.
+ Khi cha kết thúc sớm, tiến trình con mất cha và trở thành Orphan. Kernel tự động gán tiến trình con cho init (PID=1) hoặc systemd, để đảm bảo nó được thu dọn khi kết thúc.