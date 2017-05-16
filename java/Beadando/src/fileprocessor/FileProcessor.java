package fileprocessor;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import fileprocessor.parser.Parseable;

public class FileProcessor<T extends Comparable<T>, Parser extends Parseable<T>> implements Runnable {

	private T max;
	private List<? super T> log;
	private Set<Thread> threads;

	private Path path;
	private WatchService ws;
	private T initValue;
	private T prevValue;
	private Parser parser;

	private AtomicBoolean keepProcessing;

	public FileProcessor(T elem, List<? super T> elemetns) {

		threads = new HashSet<Thread>();
		this.max = elem;
		this.log = elemetns;
		keepProcessing = new AtomicBoolean(false);
	}

	void processDir(T initValue, String libraryName, Parser parser) throws IOException {
		this.initValue = initValue;
		this.parser = parser;

		path = Paths.get(libraryName);
		ws = path.getFileSystem().newWatchService();

		path.register(ws, StandardWatchEventKinds.ENTRY_MODIFY, StandardWatchEventKinds.ENTRY_CREATE);

		keepProcessing.set(true);
		Thread thread = new Thread(this);
		threads.add(thread);
		thread.start();
	}

	@Override
	public void run() {
		

			while (keepProcessing != null && keepProcessing.get()) {
			try {
				WatchKey key;
				key = ws.poll(20, TimeUnit.MILLISECONDS);
				
				if (key == null) {
					continue;
				}
				
				Thread.sleep(10);
				for (WatchEvent<?> evt : key.pollEvents()) {
					
					Stream<String> lines = Files.lines(path.resolve((Path)evt.context()));
					prevValue = initValue;
					lines.map(s -> parseLine(s)).reduce(x -> x, (f, g) -> composeFunctions(f, g));
					lines.close();
				}
				key.reset();

			
		} catch (Exception e) {
			System.out.println(e);
		}
		}

	}

	public synchronized void stopProcessing() throws InterruptedException {

		keepProcessing.set(false);
		for (Thread thread : threads) {
			thread.join();			
		}
	}

	private Function<T, T> parseLine(String line) {

		String[] values = line.split(" ");
		List<Function<T, T>> functions = new LinkedList<Function<T, T>>();
		for (String value : values) {
			functions.add(parser.parse(value));
		}

		return parser.combineParsers(functions);
	}

	private Function<T, T> composeFunctions(Function<T, T> f, Function<T, T> g) {
		T result = g.apply(prevValue);
		if (result.compareTo(max) > 0) {
			max = result;
			log.add(max);
			System.out.println(max);
		}

		prevValue = result;

		return g;
	}
}
