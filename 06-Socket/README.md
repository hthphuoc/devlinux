#Mục tiêu
Socket là một trong những cơ chế giao tiếp liên tiến trình (IPC) và mạng máy tính
nền tảng nhất. Nắm vững cách sử dụng các loại socket khác nhau là kỹ năng cốt
lõi của một lập trình viên hệ thống.
Triển khai các cặp chương trình Client-Server đơn giản
cho 4 loại socket phổ biến nhất để hiểu rõ sự khác biệt trong cách thiết lập và
truyền dữ liệu của chúng.
#Cấu trúc thư mục
├── src/
│ └── tcp_server.c
│ └── tcp_client.c
│ └── udp_server.c
│ └── udp_client.c
│ └── unix_stream_server.c
│ └── unix_stream_client.c
│ └── unix_dia_server.c
│ └── unix_dia_client.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make tcp #Biên dịch cho tcp socket
make udp #Biên dịch cho udp socket
make unix_stream #Biên dịch cho unix_stream socket
make unix_dia #Biên dịch cho unix_dia socket
make all #Biên dịch tất cả socket trên
make clean #Xóa tất cả các bin

./bin/tcp_server
./bin/tcp_client
./bin/udp_server
./bin/udp_client
./bin/unix_stream_server
./bin/unix_stream_client
./bin/unix_dia_server
./bin/unix_dia_client


