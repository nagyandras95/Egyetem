import geom.*;
import java.io.*;
import java.util.*;

class C {
public int i = 5;
public String content = "alma";
}

public class Main {
    public static void main(String[] args) {
        Object p = new Pont();
        Object p2 = new Pont();
        System.out.println(p.equals(p2));

        File file = new File("input.txt");
        Scanner scanner = null;
        FileInputStream fis = null; 
        int[] t = null;
    
try {

        scanner = new Scanner(file);
        int size = scanner.nextInt();
        t = new int[size];
        int i = 0;
        while (scanner.hasNextInt()) {
            int nextI = scanner.nextInt();
            t[i++] = nextI;
            System.out.println(nextI);
        }
} catch(IOException e) {
    System.out.println("Nem talalhato fajl..");
} finally {
    scanner.close();
}



Arrays.sort(t);

		FileOutputStream fop = null;
try {

			file = new File("newfile");
			fop = new FileOutputStream(file);

			// if file doesnt exists, then create it
			if (!file.exists()) {
				file.createNewFile();
			}

            for(int i : t) {
			    fop.write(i);
            }

			fop.flush();
			fop.close();

			System.out.println("Done");

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fop != null) {
					fop.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		FileWriter fw = null;
try {

			file = new File("newfile_text.txt");
			fw = new FileWriter(file);

			// if file doesnt exists, then create it
			if (!file.exists()) {
				file.createNewFile();
			}

            for(int i : t) {
			    fw.write(new Integer(i).toString());
            }

			fw.flush();
			fw.close();

			System.out.println("Done");

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fw != null) {
					fw.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}


		try {
			file = new File("newfile");
			fis = new FileInputStream(file);

			System.out.println("Total file size to read (in bytes) : "
					+ fis.available());

			int content;
			while ((content = fis.read()) != -1) {
				// convert to char and display it
				System.out.println(content);
			}

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fis != null)
					fis.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}


    }
 
}
