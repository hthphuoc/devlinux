#Mục tiêu
Tìm hiểu cách một tiến trình có thể thay thế hoàn toàn mã lệnh đang chạy của nó
bằng một chương trình khác và cách truyền thông tin qua biến môi trường.

#Mô tả hoạt động
1. Tiến trình cha:

    + Thiết lập biến môi trường MY_COMMAND.

    + Tạo tiến trình con bằng fork().

    + Dùng wait() để chờ con kết thúc.

2. Tiến trình con:

    + Đọc giá trị của MY_COMMAND bằng getenv().

    + Gọi execlp() để thay thế toàn bộ chương trình hiện tại bằng lệnh được đọc từ biến môi trường.

#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/main

#Giải thích sau khi exec() được gọi thành công
Sau khi exec() được gọi thành công, không gian địa chỉ và mã lệnh của process con bị xóa hết và sau đó nó sẽ thực thi command bởi biến môi trường.