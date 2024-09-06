import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class CopyFile {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Usage: java CopyFile <source file> <destination file>");
            return;
        }

        String sourceFile = args[0];
        String destinationFile = args[1];

        try (FileInputStream fis = new FileInputStream(sourceFile);
             FileOutputStream fos = new FileOutputStream(destinationFile)) {

            // Check if the destination file already exists
            java.io.File destFile = new java.io.File(destinationFile);
            if (destFile.exists()) {
                System.out.println("Destination file '" + destinationFile + "' already exists.");
                System.out.print("Overwrite? (y/n): ");
                char response = (char) System.in.read();
                if (response != 'y' && response != 'Y') {
                    System.out.println("Operation aborted.");
                    return;
                }
            }

            byte[] buffer = new byte[1024];
            int bytesRead;

            // Copy the contents of the source file to the destination file
            while ((bytesRead = fis.read(buffer)) != -1) {
                fos.write(buffer, 0, bytesRead);
            }

            System.out.println("File '" + sourceFile + "' copied to '" + destinationFile + "' successfully.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
