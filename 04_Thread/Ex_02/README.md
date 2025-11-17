#Mục tiêu
Minh họa vấn đề "race condition" – một lỗi kinh điển trong lập trình đa luồng– và giới thiệu Mutex (Mutual Exclusion) như một giải pháp cơ bản để đảm bảo sự an toàn khi truy cập tài nguyên chia sẻ.
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
+ Tại sao cần phải sử dụng mutex trong bài toán này? Tại vì cả 3 thread đều sử dụng chung 1 tài nguyên là biến toàn cục counter
+ Điều gì sẽ xảy ra nếu chúng ta bỏ qua việc sử dụng mutex? Giá trị của biến counter sẽ không như mong đợi bằng 1000000. Bởi vì khi không có lock, các thread sẽ truy cập biến counter tùy ý và tăng giá trị của nó. Ví dụ counter đang là 1, cùng lúc đó cả 3 đều truy cập vào và lấp giá trị ra là 1, sau đó cả 3 cũng tăng lên 1 đơn vị => counter = 2 nhưng giá trị mong đội khi 3 thread tăng counter là 4.
