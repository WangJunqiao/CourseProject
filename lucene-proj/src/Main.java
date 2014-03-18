import java.io.File;
import java.io.FileWriter;
import java.io.StringWriter;
import java.util.*;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.Term;
import org.apache.lucene.search.BooleanClause.Occur;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.PhraseQuery;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;


public class Main {
	final static String indexPath="iii";
	final static String filePath="ddd";
	final static int fileNumber=20;
	final static Random R=new Random();
	public static String createContent()throws Exception{
		StringWriter w=new StringWriter();
		int t=R.nextInt(10)+1;
		for(int i=1;i<=t;i++){
			w.write(R.nextInt(20)+"\r\n");
		}
		w.close();
		return w.toString();
	}
	public static void createFile() throws Exception{
		for(int i=1;i<=fileNumber;i++){
			File f=new File(filePath+"\\"+i+".txt");
			String s=createContent();
			FileWriter fw=new FileWriter(f);
			fw.append(s);
			fw.close();
		}
	}
	public static void main(String[] args) throws Exception {
		createFile();
		
		Analyzer analyzer = new StandardAnalyzer(Version.LUCENE_30);
		
		Directory directory = FSDirectory.open(new File(indexPath));
		IndexWriter iwriter = new IndexWriter(directory, analyzer, true,
				new IndexWriter.MaxFieldLength(Integer.MAX_VALUE));

		Document doc;
		
		File srcDir=new File(filePath);
		File[] allfiles=srcDir.listFiles();
		for(int i=0;i<allfiles.length;i++){
			String path=allfiles[i].getAbsolutePath();
			doc = File2Document.file2Document(path);
			iwriter.addDocument(doc);
			System.out.println(doc.get("name")+" has been indexed!");
		}
		/*
		for(int i=1;i<=fileNumber;i++){
			String path=filePath+"\\"+i+".txt";
			doc = File2Document.file2Document(path);
			iwriter.addDocument(doc);
			System.out.println(doc.get("name")+" has been indexed!");
		}
		*/
		
		
		iwriter.close();
		System.out.println("index process ended!");
		
		
		System.out.println("please input your query. input quit to stop!");
		Scanner reader=new Scanner(System.in);
		
		IndexSearcher searcher =new IndexSearcher(directory,true);
		while( reader.hasNext() ){
			String cmd=reader.nextLine();
			if( cmd.equals("quit") ) break;
			BooleanQuery bquery=new BooleanQuery();
			
			if( cmd.contains("or") ){	
				Scanner sinput=new Scanner(cmd);
				while( sinput.hasNext() ){
					String s=sinput.next();
					if( s.equals("or") ) continue;
					PhraseQuery query=new PhraseQuery();
					query.add(new Term("content",s));
					bquery.add(query, Occur.SHOULD);
				}
			}else{
				Scanner sinput=new Scanner(cmd);
				while( sinput.hasNext() ){
					String s=sinput.next();
					if( s.equals("and") ) continue;
					PhraseQuery query=new PhraseQuery();
					query.add(new Term("content",s));
					bquery.add(query, Occur.MUST);
				}
			}
			
			TopDocs top=searcher.search(bquery,10000);
			if( top.totalHits ==0 ){
				System.out.println("No match!");
			}
			for(int i=0;i<top.totalHits;i++){
				Document res=searcher.doc(top.scoreDocs[i].doc);
				System.out.println(res.get("name"));
			}
		}
	}
}
