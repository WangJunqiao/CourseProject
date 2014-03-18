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

namespace 学生成绩管理系统
{
    public partial class FormUpdatePwd : Form
    {
        private SqlConnection sqlcon;
        private SqlCommand sqlcom;
        private SqlDataReader sqldr;

        public FormUpdatePwd()
        {
            InitializeComponent();
        }

        private void FormUpdatePwd_Load(object sender, EventArgs e)
        {
            sqlcon = new SqlConnection();
            sqlcom = new SqlCommand();
            sqlcon.ConnectionString = 
                "server=localhost;uid=sa;pwd=123456;database=students";
            sqlcom.Connection = sqlcon;

            comboBox1.Focus();
            comboBox1.SelectedIndex = 0;

            statusBar1.Text = "状态栏 无消息";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (comboBox1.Text == "学生")
            {
                sqlcom.CommandText =
                    "select * from students where sno='" + textBox1.Text + "'"
                    + " and spwd='" + textBox2.Text + "'";
                sqlcon.Open();
                sqldr = sqlcom.ExecuteReader(CommandBehavior.CloseConnection);

                if (sqldr.Read())
                {
                    sqlcom.CommandText =
                        "update students set spwd='" + textBox3.Text + "' "
                        + "where sno='" + textBox1.Text + "'";
                    sqlcon.Close();
                    sqlcon.Open();
                    sqlcom.ExecuteNonQuery();

                    statusBar1.Text = "密码更新成功";
                    Thread.Sleep(1000);
                    statusBar1.Text = "状态栏 无消息";
                }
                else
                {
                    MessageBox.Show("登录名或原密码错误,更新失败");
                }

                sqldr.Close();
            }
            else if (comboBox1.Text == "教师")
            {
                sqlcom.CommandText =
                    "select * from Teachers where Tno='" + textBox1.Text + "'"
                    + " and Tpwd='" + textBox2.Text + "'";
                sqlcon.Open();
                sqldr = sqlcom.ExecuteReader(CommandBehavior.CloseConnection);

                if (sqldr.Read())
                {
                    sqlcom.CommandText =
                        "update Teachers set Tpwd='" + textBox3.Text + "' "
                        + "where Tno='" + textBox1.Text + "'";

                    sqlcon.Close();
                    sqlcon.Open();
                    sqlcom.ExecuteNonQuery();

                    statusBar1.Text = "密码更新成功";
                    Thread.Sleep(1000);
                    statusBar1.Text = "状态栏 无消息";
                }
                else
                {
                    MessageBox.Show("登录名或原密码错误,更新失败");
                }

                sqldr.Close();
            }
        }
    }
}
