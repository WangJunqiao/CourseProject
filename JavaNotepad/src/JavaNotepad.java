import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.util.*;
import javax.swing.event.*;
import java.awt.event.*;

public class JavaNotepad extends JFrame {
	JTextArea jTextArea;
	File selF;
	JLabel jLabel;
	JMenuBar jMenuBar;
	JMenu JMenuFile, JMenuEdit, JMenuAbout;
	JMenuItem JMIOpen, JMISave, JMISaveAs, JMIClose, JMICopy, JMICut, JMIPaste,
			JMIAbout;
	JPopupMenu JPM;

	public JavaNotepad() { // JFrame 默认的是BorderLayout
		super("新建文本文档");
		this.setSize(500, 500);
		initUI();
		initListener();
	}

	private void initUI() {
		//取得系统支持的字体
		GraphicsEnvironment e = GraphicsEnvironment
				.getLocalGraphicsEnvironment();
		Font[] f = e.getAllFonts();
		//for (Font s : f) {
		//	System.out.println(s.getFontName());
		//}
		JMenuFile = new JMenu("文件");
		JMenuEdit = new JMenu("编辑");
		JMenuAbout = new JMenu("关于");
		JMIOpen = new JMenuItem("打开"); // 下面设置快捷键
		JMIOpen.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O,
				InputEvent.CTRL_MASK));
		JMISave = new JMenuItem("保存");
		JMISave.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
				InputEvent.CTRL_MASK));
		JMISaveAs = new JMenuItem("另存为");
		JMIClose = new JMenuItem("关闭");
		JMIClose.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q,
				InputEvent.CTRL_MASK));
		JMICut = new JMenuItem("剪切");
		JMICut.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_X,
				InputEvent.CTRL_MASK));
		JMICopy = new JMenuItem("复制");
		JMICopy.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C,
				InputEvent.CTRL_MASK));
		JMIPaste = new JMenuItem("粘贴");
		JMIPaste.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_V,
				InputEvent.CTRL_MASK));
		JMIAbout = new JMenuItem("关于daodao记事本");

		JMenuFile.add(JMIOpen);

		JMenuFile.add(JMISave);
		JMenuFile.add(JMISaveAs);
		JMenuFile.add(JMIClose);
		JMenuEdit.add(JMICut);
		JMenuEdit.add(JMICopy);
		JMenuEdit.add(JMIPaste);
		JMenuAbout.add(JMIAbout);
		jMenuBar = new JMenuBar();
		jMenuBar.add(JMenuFile);
		jMenuBar.add(JMenuEdit);
		jMenuBar.add(JMenuAbout);
		
		JPM = JMenuEdit.getPopupMenu(); // 取得与菜单关联的弹出式菜单
		this.add(jMenuBar, BorderLayout.NORTH); // 添加的时候需要同时制定布局管理器中的方位
		jTextArea = new JTextArea(); //
		jTextArea.setFont(new Font("微软雅黑", Font.BOLD | Font.PLAIN, 24));
		jTextArea.setForeground(Color.RED);
		jTextArea.setLineWrap(true); // 自动换行
		JScrollPane jsp = new JScrollPane(jTextArea); // 会产生滚动条的面板
		this.add(jsp, BorderLayout.CENTER);

		jLabel = new JLabel("未修改");
		this.add(jLabel, BorderLayout.SOUTH);

		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
	}

	private void initListener() { // 注册监听器
		JMIOpen.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				openFile();
			}
		});
		JMISave.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Save();
			}
		});
		JMISaveAs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SaveAs();
			}
		});
		JMIClose.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (jLabel.getText().compareTo("已修改") == 0) {
					int result = JOptionPane.showConfirmDialog(null,
							"文件已修改,要保存吗?");
					if (result == JOptionPane.OK_OPTION) {
						SaveAs();
					} else if (result == JOptionPane.OK_CANCEL_OPTION) {
						return;
					}
				}
				System.exit(0);
			}
		});
		JMICut.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				jTextArea.cut();
			}
		});
		JMICopy.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				jTextArea.copy();
			}
		});
		JMIPaste.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				jTextArea.paste();
			}
		});
		/*JMenuEdit.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				System.out.println("xixi");
				JPM.show(null, JMenuEdit.getX(), JMenuEdit.getY()); 
			}
		});*/
		// 显示一些确认信息等的对话框可以用 JOptionPane,很好用
		JMIAbout.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane
						.showMessageDialog(null,
								"^_^叨叨最新作品\n开发日期: 2010.12.17\n作者zjut_DD\nAll Right Reserved");
			}
		});
		// 鼠标左键叫click,右键叫press,release******o(╯□╰)o**
		jTextArea.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) { // 两个一起重写才有用*****
				if (e.isPopupTrigger()) {
					JPM.show(jTextArea, e.getX(), e.getY()); // 父窗体一定要设置为jTextArea才好用
				}
			}

			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					JPM.show(jTextArea, e.getX(), e.getY());
				}
			}
		});
		jTextArea.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.isControlDown() && e.getKeyChar() == KeyEvent.VK_S) { // 判断是不是ctrl+s的组合键
					Save();
					jLabel.setText("未修改");
				} else {
					jLabel.setText("已修改");
				}
			}
		});
	}

	private void SaveAs() { // 文件另存为
		JFileChooser jFileChooser = new JFileChooser();
		jFileChooser.showSaveDialog(null);
		selF=jFileChooser.getSelectedFile();
		this.setTitle(selF.getName());
		try {
			FileWriter fWriter = new FileWriter(jFileChooser.getSelectedFile());
			jTextArea.write(fWriter);
		} catch (Exception e) {

		}
	}

	private void Save() { // 保存文件
		if (selF == null) {
			SaveAs();
			jLabel.setText("未修改");
		}
		try {
			FileWriter fWriter = new FileWriter(selF);
			jTextArea.write(fWriter);
			jLabel.setText("未修改");
		} catch (Exception e) {

		}
	}

	private void openFile() { // 打开一个文本文件
		JFileChooser jFileChooser = new JFileChooser();
		jFileChooser.showOpenDialog(null);
		selF = jFileChooser.getSelectedFile();
		this.setTitle(selF.getName());
		try {
			jTextArea.setText("");
			Scanner reader = new Scanner(selF);
			String line;
			while (reader.hasNext()) {
				line = reader.nextLine();
				jTextArea.append(line);
				jTextArea.append("\n");
			}
			jLabel.setText("未修改");
		} catch (Exception e) {

		}
	}

	public static void main(String[] args) {
		JavaNotepad javatext = new JavaNotepad();
	}
}
