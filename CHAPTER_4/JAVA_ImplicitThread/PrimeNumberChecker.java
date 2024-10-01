import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class PrimeChecker implements Runnable {
    private final int number;

    public PrimeChecker(int number) {
        this.number = number;
    }

    @Override
    public void run() {
        if (isPrime(number)) {
            System.out.println(number + " là số nguyên tố.");
        } else {
            System.out.println(number + " không phải là số nguyên tố.");
        }
    }

    private boolean isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i <= Math.sqrt(num); i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }
}

public class PrimeNumberChecker {
    public static void main(String[] args) {
        ExecutorService executorService = Executors.newFixedThreadPool(4); // Tạo pool với 4 thread

        // Kiểm tra các số từ 2 đến 500
        for (int i = 2; i <= 500; i++) {
            executorService.submit(new PrimeChecker(i));
        }

        executorService.shutdown(); // Ngừng nhận thêm task
    }
}
