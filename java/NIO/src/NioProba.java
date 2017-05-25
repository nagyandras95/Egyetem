import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;

public class NioProba {
	public static void main(String[] args) throws Exception {
		file("text.txt");
		watch("watchdir");
	}

	private static void file(String filename) throws IOException {
		SeekableByteChannel chan = FileChannel.open(Paths.get(filename),
				StandardOpenOption.READ, StandardOpenOption.WRITE);
		ByteBuffer buf = ByteBuffer.allocate(1);
		
		chan.position(2);
		chan.read(buf);
		byte b = buf.get(0);
		buf.rewind();

		System.out.println("read " + b);

		chan.position(4);
		chan.read(buf);
		byte b2 = buf.get(0);
		buf.rewind();

		System.out.println("read " + b2);
	}

	private static void watch(String dirname) throws IOException, InterruptedException {
		Path path = Paths.get(dirname);
		WatchService ws = path.getFileSystem().newWatchService();

		path.register(ws, StandardWatchEventKinds.ENTRY_CREATE,
											StandardWatchEventKinds.ENTRY_DELETE,
											StandardWatchEventKinds.ENTRY_MODIFY);
		
		while (true) {
			WatchKey key = ws.take();
			for (WatchEvent<?> evt : key.pollEvents()) {
				Object context = evt.context();
				System.out.println(context + " " + evt.kind());
			}
			key.reset();
		}
	}
}
