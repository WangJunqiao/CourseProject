using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Data.SqlClient;

using System.Diagnostics;

namespace 学生成绩管理系统
{
    public partial class FormLogin : Form
    {
        SqlCommand sqlcom;
        SqlConnection sqlcon;
        SqlDataReader sqldr;

        public FormLogin()
        {
            InitializeComponent();
        }

        private void FormLogin_Load(object sender, EventArgs e)
        {
            sqlcom = new SqlCommand();
            sqlcon = new SqlConnection();
            sqlcon.ConnectionString =
                "server=localhost;uid=sa;pwd=123456;database=students";
            sqlcom.Connection = sqlcon;
            //sqlcon.Open();

            comboBox1.Focus();
            comboBox1.SelectedIndex = 0;
            
        }

        /// <summary>
        /// 针对不同的角色检查登录名和密码,并作出应答
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonLogin_Click(object sender, EventArgs e)
        {
            if (comboBox1.Text == "学生")
            {
                sqlcom.CommandText = "select * from students where sno='" +
                textBox1.Text + "' and spwd='" + textBox2.Text+"'";
                sqlcon.Open();
                sqldr = sqlcom.ExecuteReader(CommandBehavior.CloseConnection);

                if (sqldr.Read())//datareader中有记录说明
                {
                    //MessageBox.Show("login successfully");
                    FormStu FS = new FormStu();
                    FS.father = this;
                    FS.sno = sqldr[0].ToString(); FS.sname = sqldr[1].ToString();
                    FS.Show();
                    this.Visible = false;
                }
                else
                {
                    MessageBox.Show("用户名或密码不对");
                }
                sqldr.Close();
            }
            else if (comboBox1.Text == "教师")
            {
                sqlcom.CommandText = "select * from Teachers where Tno='" +
                textBox1.Text + "' and Tpwd='" + textBox2.Text+"'";
                sqlcon.Open();
                sqldr = sqlcom.ExecuteReader(CommandBehavior.CloseConnection);

                if (sqldr.Read())//datareader中有记录说明
                {
                    //MessageBox.Show("login successfully");
                    FormTea FT = new FormTea();
                    FT.father = this;
                    FT.Tno = sqldr[0].ToString();
                    FT.Tname = sqldr[1].ToString();
                    FT.Show();
                    this.Visible = false;
                }
                else
                {
                    MessageBox.Show("用户名或密码不对");
                }
                sqlcon.Close();
            }
            else
            {
                if (textBox1.Text=="Admin" && textBox2.Text=="123456")
                {
                    //MessageBox.Show("login successfully");
                    FormAdm FA = new FormAdm();
                    FA.father = this; FA.Show();
                    this.Visible = false;
                }
                else
                {
                    MessageBox.Show("登录失败");
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("帮助文档.txt");
        }
    }
}
