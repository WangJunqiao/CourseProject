using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

//自己加的
using System.Data.SqlClient;
using System.Threading;
using Microsoft.Office.Core;
using Microsoft.Office.Interop.Excel;
using Excel = Microsoft.Office.Interop.Excel;
using System.Reflection; //使用Missing类
using System.Data.OleDb; //使用Excel数据库

namespace 学生成绩管理系统
{
    public partial class FormAdm : Form
    {
        private SqlCommand sqlcom;
        private SqlCommandBuilder sqlcomb;//定义应该紧跟在sqlda的selectcommand设置之后
        private SqlConnection sqlcon;
        private SqlDataAdapter sqlda;
        private DataSet ds;
        private DataView dv;

        private BindingManagerBase BMB;

        public Form father;
        
        private void MyInitialize()
        {
            this.FormClosed += new FormClosedEventHandler(FormAdm_Closed);
        }

        public FormAdm()
        {
            InitializeComponent();
            MyInitialize();
        }
        public FormAdm(Form father)
            : base()
        {
            this.father = father;
        }
        private void statusBarShow(string message)
        {
            statusBar1.Text = message;
            Thread.Sleep(1000);
            statusBar1.Text = "状态栏 无消息";
        }

        private void FormAdm_Load(object sender, EventArgs e)
        {
            sqlcom = new SqlCommand();
            sqlcon = new SqlConnection();
            sqlda = new SqlDataAdapter();
            ds = new DataSet();

            sqlcon.ConnectionString = 
                "server=localhost;uid=sa;pwd=123456;database=students";
            sqlcom.Connection = sqlcon;

            label1.Text = "第一列";
            label2.Text = "第二列";
            label3.Text = "第三列";

            this.更新学生信息ToolStripMenuItem.Enabled = false;
            this.更新教师信息ToolStripMenuItem.Enabled = false;
            this.更新课程信息ToolStripMenuItem.Enabled = false;
            this.更新成绩表格ToolStripMenuItem.Enabled = false;
        }
        private void FormAdm_Closed(object sender, EventArgs e)
        {
            father.Close();
        }
        private void 显示学生信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ds.Reset();
            sqlcom.CommandText = "select sno 学号,sname 姓名,spwd 密码 from students";
            sqlda.SelectCommand = sqlcom;
            sqlcomb = new SqlCommandBuilder(sqlda);
            sqlcon.Open();
            sqlda.Fill(ds, "students");
            sqlcon.Close();
            dv = ds.Tables["students"].DefaultView;
            dataGridView1.DataSource = dv;

            //数据绑定,先取消之前的绑定
            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "学号"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "姓名"));
            textBox3.DataBindings.Clear();
            textBox3.DataBindings.Add(new Binding("Text", dv, "密码"));

            this.更新学生信息ToolStripMenuItem.Enabled = true;
            this.更新教师信息ToolStripMenuItem.Enabled = false;
            this.更新课程信息ToolStripMenuItem.Enabled = false;
            this.更新成绩表格ToolStripMenuItem.Enabled = false;
        }

        private void 更新学生信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sqlda.Update(ds,"students" );
            statusBarShow("学生信息更新成功");
        }

        private void 显示教师信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            

            ds.Reset();
            sqlcom.CommandText = "select Tno 教师号,Tname 姓名,Tpwd 密码 from Teachers";
            sqlda.SelectCommand = sqlcom;
            sqlcomb = new SqlCommandBuilder(sqlda);
            sqlcon.Open();
            sqlda.Fill(ds, "Teachers");
            sqlcon.Close();
            dv = ds.Tables["Teachers"].DefaultView;

            dataGridView1.DataSource = dv;//数据源绑定

            //数据绑定,先取消之前的绑定
            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "教师号"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "姓名"));
            textBox3.DataBindings.Clear();
            textBox3.DataBindings.Add(new Binding("Text", dv, "密码"));

            this.更新学生信息ToolStripMenuItem.Enabled = false;
            this.更新教师信息ToolStripMenuItem.Enabled = true;
            this.更新课程信息ToolStripMenuItem.Enabled = false;
            this.更新成绩表格ToolStripMenuItem.Enabled = false;
        }

        private void 更新教师信息ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            sqlda.Update(ds, "Teachers");
            statusBarShow("教师信息更新成功");
        }

        private void 注销登录ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            father.Show();
            this.Dispose();//这个不会触发FormClosed事件,但是close会
        }
        //将数据集中的数据写入电子表格
        private void DsToWsheet(DataSet ds, Worksheet wsheet)
        {
            int C = 0, R = 1;
            foreach (DataColumn dc in ds.Tables[0].Columns)
            {
                wsheet.Cells[1, ++C] = dc.ColumnName;
            }
            foreach (DataRow dr in ds.Tables[0].Rows)
            {
                ++R;
                for (int i = 1; i <= C; i++)
                {
                    wsheet.Cells[R, i] = dr[i - 1];
                }
            }
        }

        private void 导出ExcelToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            string fileName;
            saveFileDialog1.Filter = "Excel 2003 *.xls|*.xls|Excel 2007 *.xlsx|*.xlsx";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                fileName = saveFileDialog1.FileName;
                Excel.Application app =
                    new Microsoft.Office.Interop.Excel.Application();
                app.Visible = false;

                Workbook wBook = app.Workbooks.Add(true);
                Worksheet wSheet = wBook.Worksheets[1] as Worksheet;

                DsToWsheet(ds, wSheet);
                //设置禁止弹出保存和覆盖的询问提示框   
                app.DisplayAlerts = false;
                app.AlertBeforeOverwriting = false;

                wBook.SaveAs(fileName, Missing.Value, Missing.Value, Missing.Value,
                    Missing.Value, Missing.Value, XlSaveAsAccessMode.xlExclusive, Missing.Value,
                    Missing.Value, Missing.Value, Missing.Value, Missing.Value);

                app.Quit();
                app = null;
            }
        }

        private void 从ExcelToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            

            string fileName;
            openFileDialog1.Filter = "Excel 2003 *.xls|*.xls|Excel 2007 *.xlsx|*.xlsx"; 
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                fileName = openFileDialog1.FileName;
                OleDbConnection OleDbcon = new OleDbConnection();
                OleDbCommand OleDbcom = new OleDbCommand();

                OleDbcon.ConnectionString =
                    "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" +
                    fileName + ";Extended Properties=\"Excel 12.0 Xml;HDR=YES\"";
                OleDbcom.Connection = OleDbcon;
                OleDbcom.CommandText = "select * from [sheet1$]";
                OleDbDataAdapter OleDbda = new OleDbDataAdapter(OleDbcom);
                OleDbCommandBuilder OleDbcomb = new OleDbCommandBuilder(OleDbda);

                OleDbcon.Open();
                ds.Reset();
                OleDbda.Fill(ds, "[sheet1$]");
                
                dv = ds.Tables[0].DefaultView;

                dataGridView1.DataSource = dv;
            }

            this.更新学生信息ToolStripMenuItem.Enabled = false;
            this.更新教师信息ToolStripMenuItem.Enabled = false;
            this.更新课程信息ToolStripMenuItem.Enabled = false;
            this.更新成绩表格ToolStripMenuItem.Enabled = false;
        }

        private void 显示所有课程ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ds.Reset();//使用clear是不行的,它只删除所有行,但不删除列
           // ds.Clear(); xxx
            sqlcom.CommandText = 
                "select cno 课程号,cname 课程名 from courses";
            sqlda.SelectCommand = sqlcom;
            sqlcomb = new SqlCommandBuilder(sqlda);
            sqlcon.Open();
            sqlda.Fill(ds,"courses");
            sqlcon.Close();

            dv = ds.Tables[0].DefaultView;
            dataGridView1.DataSource = dv;

            //数据绑定,先取消之前的绑定
            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "课程号"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "课程名"));
            textBox3.DataBindings.Clear();
            //textBox3.DataBindings.Add(new Binding("Text", dv, "任课教师号"));

            this.更新学生信息ToolStripMenuItem.Enabled = false;
            this.更新教师信息ToolStripMenuItem.Enabled = false;
            this.更新课程信息ToolStripMenuItem.Enabled = true;
            this.更新成绩表格ToolStripMenuItem.Enabled = false;
        }

        private void 更新课程信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //dt = ds.Tables[0];
            sqlda.Update(ds,"courses");
            statusBarShow("课程信息更新成功");
        }

        private void 显示选课表ExcelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            

            //dataGridView1.ReadOnly = true;
            ds.Reset();
            sqlcom.CommandText = "select sno 学号,cno 课程号 from reports";
            sqlda.SelectCommand = sqlcom;
            sqlcomb = new SqlCommandBuilder(sqlda);
            sqlcon.Open();
            sqlda.Fill(ds);
            sqlcon.Close();
            dv = ds.Tables[0].DefaultView;
            
            dataGridView1.DataSource = dv;

            //数据绑定,先取消之前的绑定
            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "学号"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "课程号"));
            textBox3.DataBindings.Clear();
            //textBox3.DataBindings.Add(new Binding("Text", dv, "成绩"));

            this.更新学生信息ToolStripMenuItem.Enabled = false;
            this.更新教师信息ToolStripMenuItem.Enabled = false;
            this.更新课程信息ToolStripMenuItem.Enabled = false;
            this.更新成绩表格ToolStripMenuItem.Enabled = true;
        }

        private void 更新选课表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sqlda.Update(ds);
            statusBarShow("选课信息更新成功");
        }

        private void 查看学生成绩ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            

            ds.Reset();
            sqlcom.CommandText = "select sname 学生,cname 课程,score 成绩 from students,courses,reports where students.sno=reports.sno and courses.cno=reports.cno";
            sqlda.SelectCommand = sqlcom;
            //sqlcomb = new SqlCommandBuilder(sqlda);
            sqlcon.Open();
            sqlda.Fill(ds);
            sqlcon.Close();
            dv = ds.Tables[0].DefaultView;
            dataGridView1.DataSource = dv;
            
            //数据绑定,先取消之前的绑定
            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "学生"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "课程"));
            textBox3.DataBindings.Clear();
            textBox3.DataBindings.Add(new Binding("Text", dv, "成绩"));

            this.更新学生信息ToolStripMenuItem.Enabled = false;
            this.更新教师信息ToolStripMenuItem.Enabled = false;
            this.更新课程信息ToolStripMenuItem.Enabled = false;
            this.更新成绩表格ToolStripMenuItem.Enabled = false;
        }

        private void 注销登录ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            father.Show();
            this.Dispose();
        }

        private void 学生表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sqlcon.Open();
            foreach(DataRow dr in ds.Tables[0].Rows)
            {
                string sno = dr[0].ToString();
                string sname = dr[1].ToString();
                string spwd = dr[2].ToString();

                
                try
                {
                    sqlcom.CommandText = 
                        "insert into students values ('"+sno
                        +"','"+sname+"','"+spwd+"')";
                    sqlcom.ExecuteNonQuery();
                }
                catch
                {

                }
                
            }
            sqlcon.Close();
            statusBarShow("导入数据库学生表成功");
        }

        private void 教师表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sqlcon.Open();
            foreach (DataRow dr in ds.Tables[0].Rows)
            {
                string Tno = dr[0].ToString();
                string Tname = dr[1].ToString();
                string Tpwd = dr[2].ToString();
                try
                {
                    sqlcom.CommandText =
                        "insert into teachers values ('" + Tno
                        + "','" + Tname + "','" + Tpwd + "')";
                    sqlcom.ExecuteNonQuery();
                }
                catch
                {

                }
                
            }
            sqlcon.Close();
            statusBarShow("导入数据库教师表成功");
        }

        private void 课程表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sqlcon.Open();
            foreach (DataRow dr in ds.Tables[0].Rows)
            {
                string cno = dr[0].ToString();
                string cname = dr[1].ToString();
                
                try
                {
                    sqlcom.CommandText =
                        "insert into courses values ('" + cno
                        + "','" + cname + "')";
                    
                    sqlcom.ExecuteNonQuery(); 
                }
                catch
                {

                }
                
            }
            sqlcon.Close();
            statusBarShow("导入数据库课程表成功");
        }

        private void 选课表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            sqlcon.Open();
            foreach (DataRow dr in ds.Tables[0].Rows)
            {
                string sno = dr[0].ToString();
                string cno = dr[1].ToString();
                try
                {
                    sqlcom.CommandText =
                        "insert into reports (sno,cno) values ('" + sno
                        + "','" + cno + "')";
                    sqlcom.ExecuteNonQuery();
                }
                catch
                {

                }
            }
            sqlcon.Close();
            statusBarShow("导入数据库选课表成功");
        }
    }
}
