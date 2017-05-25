package fileprocessor;

import static org.junit.Assert.*;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;

import fileprocessor.parser.ArithOperator;

@RunWith(Parameterized.class)
public class TestProcessor {
	private static String TEST_DIR = "testDir";
	
	private String fileName;
	private Integer max;
	private Integer initValue;
	List<Number> log;

	public TestProcessor(String fileName, Integer max, Integer initValue, List<Number> log) {
		this.fileName = fileName;
		this.max = max;
		this.initValue = initValue;
		this.log = log;
	}

	@Parameterized.Parameters
	public static Collection<Object[]> data() {
		return Arrays.asList(new Object[][] { { "test1.txt", 1000, 0, Arrays.asList(1001, 1002, 1003, 1004, 1005) },
				{ "test2.txt", 1234, 13, Arrays.asList(2028, 10153, 50778, 253903, 1269528, 1983703) },
				{ "test2hibakkal.txt", 1234, 13, Arrays.asList(2028, 10153, 50778, 253903, 1269528, 1983703) } });
	}

	@Test
	public void test() throws IOException, InterruptedException {
		File theDir = new File("testDir");
		
		// if the directory does not exist, create it
		if (!theDir.exists()) {
			theDir.mkdir();
		}
		theDir.setReadable(true);
		List<Number> result = new ArrayList<>();
		FileProcessor<Integer,ArithOperator> fileProcessor = new FileProcessor<Integer,ArithOperator>(max,result);
		fileProcessor.processDir(initValue, TEST_DIR, ArithOperator.DEF);
		
		Thread.sleep(200);
		
		Files.copy(Paths.get("original" + File.separator + fileName),
				Paths.get(TEST_DIR + File.separator + fileName),
				StandardCopyOption.REPLACE_EXISTING);
		
		
		Thread.sleep(200);
		fileProcessor.stopProcessing();
		
		assertEquals(result.size(), log.size());
		assertTrue(result.stream().allMatch( e -> log.contains(e) ));
		
		theDir.delete();

	}

}
