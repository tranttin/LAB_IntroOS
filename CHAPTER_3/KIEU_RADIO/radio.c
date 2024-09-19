#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#define SHM_NAME "/shm_radio"
#define SHM_SIZE 256

void generate_random_delay() {
    int delay = rand() % 5 + 1;  // Delay từ 1 đến 5 giây
    sleep(delay);
}

int main() {
    srand(time(NULL));

    // Tạo bộ nhớ chia sẻ
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHM_SIZE);
    char *shared_memory = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    const char *messages[] = {
    "Những là đắp nhớ, đổi sầu,\nTuyết sương nhuốm nửa mái đầu hoa râm.",
    "Mấy người bạc ác tinh ma,\nMình làm mình chịu kêu mà ai thương.",
    "Một nhà phúc lộc gồm hai,\nNghàn năm dằng dặc quan giai lần lần",
    "Người quốc sắc, kẻ thiên tài,\nTình trong như đã, mặt ngoài còn e.",
    "Phong lưu rất mực hồng quần,\nXuân xanh xấp xỉ tới tuần cập kê.",
    "Bấy chầy dãi nguyệt dầu hoa,\nMười phần xuân có gầy ba bốn phần.",
    "Thấy nàng mặt phấn tươi son,\nMừng thầm được mối bán buôn có lời",
    "Ví dù giải kết đến điều,\nThì đem vàng đá mà liều với thân!",
    "Cảnh nào cảnh chẳng đeo sầu,\nNgười buồn, cảnh có vui đâu bao giờ!",
    "Trai anh hùng, gái thuyền quyên,\nPhỉ nguyền sánh phượng đẹp duyên cưỡi rồng.",
    "Tình nhân lại gặp tình nhân,\nHoa xưa ong cũ mấy phân chung tình.", 
    "Trăm năm tính cuộc vuông tròn,\nPhải dò cho đến ngọn nguồn lạch sông.",
    "Vầng trăng vằng vặc giữa trời,\nĐinh ninh hai mặt một lời song song.",
    "Rằng: Tôi chút phận đàn bà,\nNước non lìa cửa, lìa nhà, đến đây.",
    "Sóng tình dường đã xiêu xiêu,\nXem trong âu yếm có chiều lả lơi.",
    "Từ rằng: Tâm phúc tương tri,\nSao chưa thoát khỏi nữ nhi thường tình?",
    };
    int message_count = 15;
    int message_index = 0;

    while (1) {
        // Ghi thông điệp vào bộ nhớ chia sẻ
        snprintf(shared_memory, SHM_SIZE, "%s", messages[message_index]);
        message_index = (message_index + 1) % message_count;

        // In ra thông báo phát đi
        printf("[Radio] %s\n", shared_memory);

        // Đợi một khoảng thời gian ngẫu nhiên từ 1 đến 5 giây
        generate_random_delay();
    }

    // Hủy ánh xạ vùng nhớ chia sẻ
    munmap(shared_memory, SHM_SIZE);
    shm_unlink(SHM_NAME);

    return 0;
}
