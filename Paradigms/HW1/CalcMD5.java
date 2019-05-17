import java.io.*;
import java.nio.file.*;
import java.security.*;
import java.util.*;

public class CalcMD5 {
    public static void main(String args[]) {
        if (args.length != 1) {
            System.out.println("Enter one argument");
            return;
        }
        try (Scanner in = new Scanner(new File(args[0]), "utf-8")) {
            while (in.hasNextLine()) {
                File file = new File(in.nextLine());
                byte[] fileBytes = Files.readAllBytes(file.toPath());
                MessageDigest md = MessageDigest.getInstance("MD5");
                md.update(fileBytes);
                StringBuilder sb = new StringBuilder();
                byte[] mdbytes = md.digest();
                Formatter formatter = new Formatter();
                for (byte b : mdbytes) {
					formatter.format("%02x", b);
                }
				System.out.println(formatter.toString());
            }
        } catch (FileNotFoundException e) {
            System.err.println("File not found");
        } catch (NoSuchAlgorithmException e) {
            System.err.println("No such algorithm");
        } catch (IOException e) {
            e.getMessage();
        }
    }
}
