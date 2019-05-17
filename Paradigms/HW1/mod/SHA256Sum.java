import java.util.*;
import java.io.*;
import java.security.*;
import javax.xml.bind.DatatypeConverter;

public class SHA256Sum {
    public static void main(String[] args) {
        List<String> files = new ArrayList<>(Arrays.asList(args));
        boolean useStdin = files.isEmpty();
        if (useStdin) {
            files.add("-");
        }
        for (String filePath : files) {
            try {
                MessageDigest md = MessageDigest.getInstance("SHA-256");
                DigestInputStream dis = new DigestInputStream(useStdin ? System.in : new FileInputStream(filePath), md);
                byte[] buf = new byte[4 * 1024];
                while (dis.read(buf) > -1);
                dis.close();
                byte[] hash = md.digest();
                System.out.println(DatatypeConverter.printHexBinary(hash) + " *" + filePath);
            } catch (NoSuchAlgorithmException e) {
                System.err.println("SHA-256 is not supported");
            } catch (FileNotFoundException e) {
                System.err.println("File " + filePath + " does not exist or cannot be opened");
            } catch (IOException e) {
                System.err.println("Read failure for " + filePath + ": " + e.getMessage());
            }
        }
    }
}
