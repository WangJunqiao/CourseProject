using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Data.SqlClient;
using System.Threading;
using System.Data.OleDb;
using Microsoft.Office.Core;
using Microsoft.Office.Interop.Excel;
using Excel = Microsoft.Office.Interop.Excel;
using System.Reflection;

namespace 学生成绩管理系统
{
    public partial class FormTea : Form
    {
        public string Tno;
        public string Tname;
        public Form father;

        private SqlCommand sqlcom;
        private SqlConnection sqlcon;
        private SqlDataAdapter sqlda;
        private DataSet ds;
        private DataView dv;

        private BindingManagerBase BMB;//数据导航,在成绩更新的时候定位用的

        private void MyInitialize()
        {
            this.FormClosed += new FormClosedEventHandler(FormTea_closed);
        }
        public FormTea()
        {
            InitializeComponent();
            MyInitialize();
        }
        public FormTea(Form father,string Tno,string Tname)
            : base()
        {
            this.father = father;
            this.Tno = Tno;
            this.Tname = Tname;
        }

        private void FormTea_Load(object sender, EventArgs e)
        {
            sqlcom = new SqlCommand();
            sqlcon = new SqlConnection();
            sqlda = new SqlDataAdapter();
            ds = new DataSet();
            sqlcon.ConnectionString =
                "server=localhost;uid=sa;pwd=123456;database=students";
            sqlcom.Connection = sqlcon;

            label1.Text = "教师号";
            label2.Text = "姓名";
            label3.Text = Tno;
            label4.Text = Tname;
            label5.Text = "学生";
            label6.Text = "课程";
            label7.Text = "成绩";

            statusBar1.Text = "状态栏 无消息";
        }
        private void FormTea_closed(object sender, EventArgs e)
        {
            father.Close();
        }

        private void statusBarShow(string message)
        {
            statusBar1.Text = message;
            Thread.Sleep(1000);
            statusBar1.Text = "状态栏 无消息";
        }

        private void 显示选课表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ds.Reset();
            sqlcom.CommandText =
                "select sname 学生,cname 课程,score 成绩 from students,courses,reports where students.sno=reports.sno and courses.cno=reports.cno";

            sqlda.SelectCommand = sqlcom;
            sqlcon.Open();
            sqlda.Fill(ds);
            sqlcon.Close();

            dv = ds.Tables[0].DefaultView;
            dataGridView1.DataSource = dv;

            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "学生"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "课程"));
            textBox3.DataBindings.Clear();
            textBox3.DataBindings.Add(new Binding("Text", dv, "成绩"));

            statusBarShow("已显示");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string Command = sqlcom.CommandText;

            sqlcom.CommandText = "update reports set score=" + textBox3.Text +
                " where sno in ( select sno from students where sname='" +
                textBox1.Text + "') and cno in ( " + "select cno from courses where cname='"
                + textBox2.Text + "')";

            sqlcon.Open();
            sqlcom.ExecuteNonQuery();
            sqlcon.Close();

            /////////////////////////////////
            BMB = this.BindingContext[dv];
            int index = BMB.Position;

            ////////////////////////////////
            ds.Reset();
            sqlcom.CommandText = Command;
            sqlda.SelectCommand = sqlcom;
            sqlcon.Open();
            sqlda.Fill(ds);
            sqlcon.Close();

            string filter = dv.RowFilter;
            dv = ds.Tables[0].DefaultView;
            dv.RowFilter = filter;
            dataGridView1.DataSource = dv;
            //////////////////////////////////

            BMB = this.BindingContext[dv];
            BMB.Position = index;
            ///////////////////////////////

            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dv, "学生"));
            textBox2.DataBindings.Clear();
            textBox2.DataBindings.Add(new Binding("Text", dv, "课程"));
            textBox3.DataBindings.Clear();
            textBox3.DataBindings.Add(new Binding("Text", dv, "成绩"));

            statusBar1.Text = "成绩更新成功";
            Thread.Sleep(1000);
            statusBar1.Text = "状态栏 无消息";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (button2.Text == "筛选")
            {
                button2.Text = "显示";
                textBox1.Focus();

                textBox1.DataBindings.Clear();
                textBox2.DataBindings.Clear();
                textBox3.DataBindings.Clear();
            }
            else
            {
                button2.Text = "筛选";

                ds.Reset();
                sqlcom.CommandText =
                    "select sname 学生,cname 课程,score 成绩 from students,courses,reports where students.sno=reports.sno and courses.cno=reports.cno";

                sqlda.SelectCommand = sqlcom;
                sqlcon.Open();
                sqlda.Fill(ds);
                sqlcon.Close();

                dv = ds.Tables[0].DefaultView;

                string filter = "";
                bool flag = false;
                if (textBox1.Text != "")
                {
                    filter += "学生='" + textBox1.Text + "'";
                    flag = true;
                }
                if (textBox2.Text != "")
                {
                    if (flag)
                        filter += " and 课程='" + textBox2.Text + "'";
                    else
                        filter += "课程='" + textBox2.Text + "'";
                    flag = true;
                }
                if (textBox3.Text != "")
                {
                    if (flag)
                        filter += " and 成绩=" + textBox3.Text;
                    else
                        filter += "成绩=" + textBox3.Text;
                }

                dv.RowFilter = filter;

                dataGridView1.DataSource = dv;

                textBox1.DataBindings.Add(new Binding("Text", dv, "学生"));
                textBox2.DataBindings.Add(new Binding("Text", dv, "课程"));
                textBox3.DataBindings.Add(new Binding("Text", dv, "成绩"));
            }
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
        private void 导出为ExcelToolStripMenuItem_Click(object sender, EventArgs e)
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

                statusBarShow("已成功导出到" + fileName);
            }
        }

        private void 从ExcelToolStripMenuItem_Click(object sender, EventArgs e)
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

                statusBarShow("成功从" + fileName + "导入");
            }
        }

        private void 修改密码ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Thread pwdUpdate = new Thread(new ThreadStart(PwdUpdateThread));
            pwdUpdate.Start();
        }
        private void PwdUpdateThread()
        {
            FormUpdatePwd FUP = new FormUpdatePwd();
            FUP.ShowDialog();//必须是showdialog 否则窗体一闪而过
            FUP.Focus();
        }

        private void 注销登录ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            father.Show();
            this.Dispose();
        }

        private void 导入导出ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
