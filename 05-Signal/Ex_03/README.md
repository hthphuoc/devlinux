#Mục tiêu
Giải quyết bài toán "Nhà sản xuất - Người tiêu dùng" (Producer-Consumer) kinh điển. Nó giới thiệu cách sử dụng Condition Variables để một luồng có thể chờ đợi một điều kiện cụ thể xảy ra một cách hiệu quả, thay vì phải liên tục kiểm tra (busy-waiting).
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
+ Dùng kill() vì nó cho phép process cha gửi tín hiệu trực tiếp đến process con thông qua PID. Các hàm như raise() hoặc alarm() không phù hợp. Bởi vì chúng chỉ sử dụng cho chính process được gọi.
