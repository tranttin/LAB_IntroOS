import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomTextFileGenerator {
    private static final String CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 "; // Bộ ký tự sinh ngẫu nhiên

    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Cách dùng: java RandomTextFileGenerator <file-path> <độ-dài-N>");
            return;
        }

        String filePath = args[0];
        int N = Integer.parseInt(args[1]); // Độ dài của file văn bản

        try {
            generateFile(filePath, N);
            System.out.println("Tạo file thành công!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void generateFile(String filePath, int N) throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(filePath));
        Random random = new Random();

        // Sinh các ký tự ngẫu nhiên và ghi vào file
        for (int i = 0; i < N; i++) {
            char randomChar = CHARACTERS.charAt(random.nextInt(CHARACTERS.length()));
            writer.write(randomChar);
        }

        writer.close();
    }
}
