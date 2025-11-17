#Mục tiêu
Giới thiệu các thao tác nền tảng nhất với luồng: tạo một luồng thực
thi mới từ luồng chính và chờ đợi luồng đó hoàn thành.

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
+ int pthread_create(pthread_t *thread, pthread_attr_t *attr,
                   void * (*start_routine) (void *arg), void *arg);
    Hàm dùng để khởi tạo 1 thread. Với thread con trỏ lưu lại thread ID, attr thuộc tính của thread (stack size, detached mode…). Để NULL = mặc định,
start_routine: hàm thực thi của thread, arg: thông số truyền vào cho hàm, nếu hàm không có thông số truyền vào thì để NULL. Nếu tạo thành công, pthread_t sẽ trả về giá trị 0, ngược lại là -1.
+ int pthread_join(pthread_t thread, void **retval);
    Dùng để chờ 1 thread để kết thúc. Với thread: ID của thread đó, retval: nhận giá trị trả về từ thread.
+ * Thread kết thúc khi hàm start_routine thực thi hết các lệnh và return NULL
  * Gọi hàm pthread_exit(NULL); để exit
  * pthread_cancel(thread_id) để kết thúc
