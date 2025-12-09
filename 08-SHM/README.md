#Mục tiêu
Mô phỏng việc một tiến trình "sản xuất" (producer) tạo ra thông tin về một sản
phẩm và đặt nó vào bộ nhớ chia sẻ. Một tiến trình "tiêu thụ" (consumer) khác sẽ đọc thông
tin này để hiển thị.

#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/producer
./bin/consumer 

#Kết quả
ubuntu@ubuntu:~/exersise/08-SHM$ ./bin/producer 
Producer: Written product info to shared memory
Producer is done.

buntu@ubuntu:~/exersise/08-SHM$ ./bin/consumer 
Consumer: Product info:
  ID: 1
  Name: C program book
  Price: 200.00

