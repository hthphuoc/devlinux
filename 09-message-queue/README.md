#Mục tiêu
Xây dựng một hệ thống gồm một tiến trình "giao việc" (dispatcher)
và một tiến trình "thực thi" (worker), trong đó worker sẽ luôn chọn việc quan trọng nhất để
làm trước.

#Cấu trúc thư mục
├── src/
│ └── main.c
├── bin/
├── Makefile
└── README.md

#Biên dịch và chạy chương trình
make clean all

./bin/worker
./bin/dispatcher 

#Kết quả
ubuntu@ubuntu:~/exersise/09-message-queue$ ./bin/dispatcher 10 "Update weekly report"; ./bin/dispatcher 30 "CRITICAL: Restart web server";  ./bin/dispatcher 20 "Backup user database"
Dispatched task with priority 10: Update weekly report
Dispatched task with priority 30: CRITICAL: Restart web server
Dispatched task with priority 20: Backup user database
ubuntu@ubuntu:~/exersise/09-message-queue$


ubuntu@ubuntu:~/exersise/09-message-queue$ ./bin/worker 
task_worker is running...
Listening for tasks from queue: /my_task_queue
Processing task (Priority: 30): CRITICAL: Restart web server
Processing task (Priority: 20): Backup user database
Processing task (Priority: 10): Update weekly report
