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
using Microsoft.Office.Core;
using Microsoft.Office.Interop.Excel;
using System.Reflection;
using Excel = Microsoft.Office.Interop.Excel;

namespace 学生成绩管理系统
{
    public partial class FormStu : Form
    {
        public string sno;
        public string sname;
        public Form father;//谁引出了它

        private SqlCommand sqlcom;
        private SqlConnection sqlcon;
        private SqlDataAdapter sqlda;
        private DataSet ds;
        private DataView dv;
        /// <summary>
        /// 我自己添加的一些初始化
        /// </summary>
        private void MyInitialize()
        {
            this.FormClosed += new FormClosedEventHandler(FormStu_closed); 
        }
        public FormStu()
        {
            InitializeComponent();
            MyInitialize();
        }
        public FormStu(Form father, string sno, string sname)
            : base()
        {
            this.father = father;
            this.sno = sno;
            this.sname = sname;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            sqlcom = new SqlCommand();
            sqlcon = new SqlConnection();
            sqlda = new SqlDataAdapter();
            ds = new DataSet();

            sqlcon.ConnectionString =
                "server=localhost;uid=sa;pwd=123456;database=students";
            sqlcom.Connection = sqlcon;

            label1.Text = sno;
            label2.Text = sname;

            label5.Text = "学生";
            label6.Text = "课程";
            label7.Text = "成绩";

            statusBar1.Text = "状态栏 无消息";
        }
        private void FormStu_closed(object sender, EventArgs e)
        {
            father.Close();
        }
        //防止假死,用线程引出窗体
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

        private void statusBarShow(string message)
        {
            statusBar1.Text = message;
            Thread.Sleep(1000);
            statusBar1.Text = "状态栏 无消息";
        }

        private void 注销登录ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            father.Show();
            this.Dispose();
        }

        private void 显示所有ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ds.Reset();
            sqlcom.CommandText =
                "select sname 学生,cname 课程,score 成绩 from students,courses,reports where students.sno=reports.sno and courses.cno=reports.cno and students.sno='"+sno+"'";

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

                textBox1.DataBindings.Clear();
                textBox2.DataBindings.Clear();
                textBox3.DataBindings.Clear();
                textBox1.DataBindings.Add(new Binding("Text", dv, "学生"));
                textBox2.DataBindings.Add(new Binding("Text", dv, "课程"));
                textBox3.DataBindings.Add(new Binding("Text", dv, "成绩"));
            }
        }
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
        private void 导出到ExcelToolStripMenuItem_Click(object sender, EventArgs e)
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

        private void 导入导出ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
