#Mục tiêu
Mô phỏng hoạt động của một nhà hàng bằng cách sử dụng các kỹ thuật giao tiếp liên tiến trình (IPC). Kịch bản này dựa trên bài toán Nhiều nhà sản xuất - Nhiều người tiêu dùng (Multiple-Producer Multiple- Consumer), một phiên bản mở rộng của bài toán kinh điển Producer-Consumer. Trong đó, các "Đầu bếp" (nhà sản xuất) sẽ liên tục nấu món ăn và đặt lên các "Mâm thức ăn" (bounded buffer - bộ đệm giới hạn). Cùng lúc đó, các "Khách hàng" (người tiêu dùng) sẽ lấy món ăn từ những mâm này. Bạn phải sử dụng bộ nhớ chia sẻ để trao đổi dữ liệu và dùng semaphore để đảm bảo không có xung đột xảy ra. Bài tập 1: Viết một chương trình C mô phỏng kịch bản trên bằng cách tạo ra các tiến trình con (fork()) giao tiếp với nhau qua bộ nhớ chia sẻ (mmap()) và được đồng bộ hóa bằng POSIX Semaphores.

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
ubuntu@ubuntu:~/exersise/10-semaphore$ ./bin/main 
Starting restaurant simulation...
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 1/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 0/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 1/10
[Customer Veg (pid 2299)] Took VEG dish (code 1). Tray vegan now: 0/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 1/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 0/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 1/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 0/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 1/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 1/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 2/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 2/10
[Parent] Items in non-vegan tray: 2/10, Items in vegan tray: 2/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 3/10
[Customer Veg (pid 2299)] Took VEG dish (code 1). Tray vegan now: 1/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 2/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 0/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 1/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 1/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 2/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 3/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 2/10
[Parent] Items in non-vegan tray: 3/10, Items in vegan tray: 2/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 4/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 3/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 3/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 4/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 4/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 5/10
[Customer Veg (pid 2299)] Took VEG dish (code 1). Tray vegan now: 4/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 3/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 3/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 4/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 4/10
[Parent] Items in non-vegan tray: 4/10, Items in vegan tray: 4/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 5/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 5/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 6/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 6/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 5/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 5/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 6/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 7/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 4/10
[Parent] Items in non-vegan tray: 4/10, Items in vegan tray: 7/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 5/10
[Customer Veg (pid 2299)] Took VEG dish (code 1). Tray vegan now: 6/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 6/10
[Chef Donatello (pid 2296)] Placed non-veg: Garlic Sirloin Steak. Tray non-veg now: 7/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 7/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 8/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 8/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 9/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 8/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 8/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 9/10
[Parent] Items in non-vegan tray: 8/10, Items in vegan tray: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 9/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 8/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 10/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 9/10
[Customer Veg (pid 2299)] Took VEG dish (code 1). Tray vegan now: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 10/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 10/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 9/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 9/10
[Parent] Items in non-vegan tray: 9/10, Items in vegan tray: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 10/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 10/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 10/10
[Customer Veg (pid 2299)] Took VEG dish (code 1). Tray vegan now: 9/10
[Chef Portecelli (pid 2297)] Placed vegan: Pistachio Pesto Pasta. Tray vegan now: 10/10
[Parent] Items in non-vegan tray: 10/10, Items in vegan tray: 10/10
[Customer NonVeg (pid 2298)] Took NON-VEG dish (code 2). Tray non-veg now: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 10/10
[Customer Hybrid (pid 2300)] Took VEG dish (code 1). Tray vegan now: 9/10
[Customer Hybrid (pid 2300)] Took NON-VEG dish (code 2). Tray non-veg now: 9/10
[Chef Donatello (pid 2296)] Placed non-veg: Fettuccine Chicken Alfredo. Tray non-veg now: 10/10
[Chef Portecelli (pid 2297)] Placed vegan: Avocado Fruit Salad. Tray vegan now: 10/10
^C

[Parent] SIGINT received. Cleaning up: killing children and releasing resources...
[Parent] SIGINT received. Cleaning up: killing children and releasing resources...
[Parent] Cleanup done. Exiting.
[Parent] Cleanup done. Exiting.

[Parent] SIGINT received. Cleaning up: killing children and releasing resources...
[Parent] Cleanup done. Exiting.
ubuntu@ubuntu:~/exersise/10-semaphore$ 

