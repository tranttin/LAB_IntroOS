import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

// Lớp Producer (Nhà sản xuất)
class Producer implements Runnable {
    private BlockingQueue<Integer> queue;

    public Producer(BlockingQueue<Integer> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i <= 10; i++) {
                System.out.println("Producer sản xuất: " + i);
                queue.put(i); // Đặt sản phẩm vào hàng đợi
                Thread.sleep(500); // Giả lập thời gian sản xuất
            }
            queue.put(-1); // Tín hiệu kết thúc cho consumer
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

// Lớp Consumer (Người tiêu dùng)
class Consumer implements Runnable {
    private BlockingQueue<Integer> queue;

    public Consumer(BlockingQueue<Integer> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            while (true) {
                Integer item = queue.take(); // Lấy sản phẩm từ hàng đợi
                if (item == -1) {
                    System.out.println("Consumer nhận tín hiệu kết thúc.");
                    break; // Kết thúc khi nhận được tín hiệu
                }
                System.out.println("Consumer tiêu thụ: " + item);
                Thread.sleep(1000); // Giả lập thời gian tiêu thụ
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

// Lớp chính
public class ProducerConsumerDemo {
    public static void main(String[] args) {
        // Tạo BlockingQueue với kích thước cố định là 5
        BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(5);

        // Tạo thread cho Producer và Consumer
        Thread producerThread = new Thread(new Producer(queue));
        Thread consumerThread = new Thread(new Consumer(queue));

        // Khởi chạy các thread
        producerThread.start();
        consumerThread.start();

        try {
            // Chờ các thread kết thúc
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("Chương trình kết thúc.");
    }
}
