

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;

import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.Field.Index;
import org.apache.lucene.document.Field.Store;

public class File2Document {

	// 文件：name, content, size, path
	public static Document file2Document(String path) {
		File file = new File(path);

		Document doc = new Document();
		doc.add(new Field("name", file.getName(), Store.YES, Index.ANALYZED));
		doc.add(new Field("content", readFileContent(file), Store.YES, Index.ANALYZED));
		doc.add(new Field("size", Long.toString(file.length()), Store.YES, Index.NOT_ANALYZED));
		doc.add(new Field("path", file.getAbsolutePath(), Store.YES, Index.NOT_ANALYZED));
		return doc;
	}
	/**
	 * 读取文件内容
	 */
	public static String readFileContent(File file) {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(file)));
			StringBuffer content = new StringBuffer();

			for (String line = null; (line = reader.readLine()) != null;) {
				content.append(line).append("\n");
			}

			return content.toString();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public static void printDocumentInfo(Document doc) {
		System.out.println("------------------------------");
		System.out.println("name     = " + doc.get("name"));
		System.out.println("content  = " + doc.get("content"));
		System.out.println("size     = " + Long.parseLong(doc.get("size")));
		System.out.println("path     = " + doc.get("path"));
	}
}
