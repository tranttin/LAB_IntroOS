import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

// Lớp Task để đếm số ký tự xuất hiện trong đoạn văn bản
class CharCountTask implements Callable<Integer> {
    private String textPart;
    private char charToCount;

    public CharCountTask(String textPart, char charToCount) {
        this.textPart = textPart;
        this.charToCount = charToCount;
    }

    @Override
    public Integer call() {
        int count = 0;
        for (char c : textPart.toCharArray()) {
            if (c == charToCount) {
                count++;
            }
        }
        return count;
    }
}

// Lớp chính để quản lý ExecutorService và các thread
public class CharacterCountInFile {
    private static final int CHUNK_SIZE = 1024; // Kích thước mỗi phần chia nhỏ của file

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Cách dùng: java CharacterCountInFile <file-path> <ký-tự-cần-đếm>");
            return;
        }

        String filePath = args[0];
        char charToCount = args[1].charAt(0);

        ExecutorService executor = Executors.newFixedThreadPool(4); // Tạo pool với 4 thread
        List<Future<Integer>> futures = new ArrayList<>(); // Danh sách lưu kết quả từ mỗi thread

        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            StringBuilder chunk = new StringBuilder();
            int c;
            while ((c = reader.read()) != -1) {
                chunk.append((char) c);

                // Khi đủ kích thước CHUNK_SIZE thì giao công việc cho thread
                if (chunk.length() >= CHUNK_SIZE) {
                    futures.add(executor.submit(new CharCountTask(chunk.toString(), charToCount)));
                    chunk = new StringBuilder(); // Bắt đầu một phần mới
                }
            }

            // Giao phần còn lại nếu file kết thúc mà phần cuối chưa đủ CHUNK_SIZE
            if (chunk.length() > 0) {
                futures.add(executor.submit(new CharCountTask(chunk.toString(), charToCount)));
            }

            // Đợi và tổng hợp kết quả từ các thread
            int totalCount = 0;
            for (Future<Integer> future : futures) {
                totalCount += future.get();
            }

            System.out.println("Số lần xuất hiện của ký tự '" + charToCount + "': " + totalCount);

        } catch (IOException | InterruptedException | ExecutionException e) {
            e.printStackTrace();
        } finally {
            executor.shutdown(); // Đảm bảo tắt ExecutorService sau khi hoàn thành
        }
    }
}
