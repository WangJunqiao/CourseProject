namespace 学生成绩管理系统
{
    partial class FormAdm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormAdm));
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.skinEngine1 = new Sunisoft.IrisSkin.SkinEngine(((System.ComponentModel.Component)(this)));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.statusBar1 = new System.Windows.Forms.StatusBar();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.学生项ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.显示学生信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.更新学生信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.教师项ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.显示教师信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.更新教师信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.课程项ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.显示所有课程ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.更新课程信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.导入导出ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.导出ExcelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.更新成绩表格ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.查看学生成绩ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.导入导出ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.导出ExcelToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.从ExcelToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.导入到数据库ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.学生表ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.教师表ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.课程表ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.选课表ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.其它ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.注销登录ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.formAdmBindingSource = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.formAdmBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 71);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.Size = new System.Drawing.Size(299, 260);
            this.dataGridView1.TabIndex = 0;
            // 
            // skinEngine1
            // 
            this.skinEngine1.SerialNumber = "";
            this.skinEngine1.SkinFile = "C:\\Documents and Settings\\Administrator\\桌面\\迅雷下载\\VS2005应用程序界面美化\\皮肤\\One\\OneGreen.ss" +
                "k";
            this.skinEngine1.SkinStreamMain = ((System.IO.Stream)(resources.GetObject("skinEngine1.SkinStreamMain")));
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.textBox3);
            this.groupBox1.Controls.Add(this.textBox2);
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Location = new System.Drawing.Point(357, 71);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(225, 206);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "详细信息";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(26, 127);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "label3";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(26, 84);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "label2";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "label1";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(98, 120);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(100, 21);
            this.textBox3.TabIndex = 2;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(98, 75);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(100, 21);
            this.textBox2.TabIndex = 1;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(98, 34);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 0;
            // 
            // statusBar1
            // 
            this.statusBar1.Location = new System.Drawing.Point(0, 371);
            this.statusBar1.Name = "statusBar1";
            this.statusBar1.Size = new System.Drawing.Size(612, 22);
            this.statusBar1.TabIndex = 6;
            this.statusBar1.Text = "状态栏 无消息";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.学生项ToolStripMenuItem,
            this.教师项ToolStripMenuItem,
            this.课程项ToolStripMenuItem,
            this.导入导出ToolStripMenuItem,
            this.导入导出ToolStripMenuItem1,
            this.其它ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(612, 24);
            this.menuStrip1.TabIndex = 7;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 学生项ToolStripMenuItem
            // 
            this.学生项ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.显示学生信息ToolStripMenuItem,
            this.更新学生信息ToolStripMenuItem});
            this.学生项ToolStripMenuItem.Name = "学生项ToolStripMenuItem";
            this.学生项ToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.学生项ToolStripMenuItem.Text = "学生项";
            // 
            // 显示学生信息ToolStripMenuItem
            // 
            this.显示学生信息ToolStripMenuItem.Name = "显示学生信息ToolStripMenuItem";
            this.显示学生信息ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.显示学生信息ToolStripMenuItem.Text = "显示学生信息";
            this.显示学生信息ToolStripMenuItem.Click += new System.EventHandler(this.显示学生信息ToolStripMenuItem_Click);
            // 
            // 更新学生信息ToolStripMenuItem
            // 
            this.更新学生信息ToolStripMenuItem.Name = "更新学生信息ToolStripMenuItem";
            this.更新学生信息ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.更新学生信息ToolStripMenuItem.Text = "更新学生信息";
            this.更新学生信息ToolStripMenuItem.Click += new System.EventHandler(this.更新学生信息ToolStripMenuItem_Click);
            // 
            // 教师项ToolStripMenuItem
            // 
            this.教师项ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.显示教师信息ToolStripMenuItem,
            this.更新教师信息ToolStripMenuItem});
            this.教师项ToolStripMenuItem.Name = "教师项ToolStripMenuItem";
            this.教师项ToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.教师项ToolStripMenuItem.Text = "教师项";
            // 
            // 显示教师信息ToolStripMenuItem
            // 
            this.显示教师信息ToolStripMenuItem.Name = "显示教师信息ToolStripMenuItem";
            this.显示教师信息ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.显示教师信息ToolStripMenuItem.Text = "显示教师信息";
            this.显示教师信息ToolStripMenuItem.Click += new System.EventHandler(this.显示教师信息ToolStripMenuItem_Click);
            // 
            // 更新教师信息ToolStripMenuItem
            // 
            this.更新教师信息ToolStripMenuItem.Name = "更新教师信息ToolStripMenuItem";
            this.更新教师信息ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.更新教师信息ToolStripMenuItem.Text = "更新教师信息";
            this.更新教师信息ToolStripMenuItem.Click += new System.EventHandler(this.更新教师信息ToolStripMenuItem_Click_1);
            // 
            // 课程项ToolStripMenuItem
            // 
            this.课程项ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.显示所有课程ToolStripMenuItem,
            this.更新课程信息ToolStripMenuItem});
            this.课程项ToolStripMenuItem.Name = "课程项ToolStripMenuItem";
            this.课程项ToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.课程项ToolStripMenuItem.Text = "课程项";
            // 
            // 显示所有课程ToolStripMenuItem
            // 
            this.显示所有课程ToolStripMenuItem.Name = "显示所有课程ToolStripMenuItem";
            this.显示所有课程ToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.显示所有课程ToolStripMenuItem.Text = "显示所有课程";
            this.显示所有课程ToolStripMenuItem.Click += new System.EventHandler(this.显示所有课程ToolStripMenuItem_Click);
            // 
            // 更新课程信息ToolStripMenuItem
            // 
            this.更新课程信息ToolStripMenuItem.Name = "更新课程信息ToolStripMenuItem";
            this.更新课程信息ToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.更新课程信息ToolStripMenuItem.Text = "更新课程信息";
            this.更新课程信息ToolStripMenuItem.Click += new System.EventHandler(this.更新课程信息ToolStripMenuItem_Click);
            // 
            // 导入导出ToolStripMenuItem
            // 
            this.导入导出ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.导出ExcelToolStripMenuItem,
            this.更新成绩表格ToolStripMenuItem,
            this.查看学生成绩ToolStripMenuItem});
            this.导入导出ToolStripMenuItem.Name = "导入导出ToolStripMenuItem";
            this.导入导出ToolStripMenuItem.Size = new System.Drawing.Size(77, 20);
            this.导入导出ToolStripMenuItem.Text = "学生成绩表";
            // 
            // 导出ExcelToolStripMenuItem
            // 
            this.导出ExcelToolStripMenuItem.Name = "导出ExcelToolStripMenuItem";
            this.导出ExcelToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.导出ExcelToolStripMenuItem.Text = "显示选课表";
            this.导出ExcelToolStripMenuItem.Click += new System.EventHandler(this.显示选课表ExcelToolStripMenuItem_Click);
            // 
            // 更新成绩表格ToolStripMenuItem
            // 
            this.更新成绩表格ToolStripMenuItem.Name = "更新成绩表格ToolStripMenuItem";
            this.更新成绩表格ToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.更新成绩表格ToolStripMenuItem.Text = "更新选课表";
            this.更新成绩表格ToolStripMenuItem.Click += new System.EventHandler(this.更新选课表ToolStripMenuItem_Click);
            // 
            // 查看学生成绩ToolStripMenuItem
            // 
            this.查看学生成绩ToolStripMenuItem.Name = "查看学生成绩ToolStripMenuItem";
            this.查看学生成绩ToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.查看学生成绩ToolStripMenuItem.Text = "查看学生成绩";
            this.查看学生成绩ToolStripMenuItem.Click += new System.EventHandler(this.查看学生成绩ToolStripMenuItem_Click);
            // 
            // 导入导出ToolStripMenuItem1
            // 
            this.导入导出ToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.导出ExcelToolStripMenuItem1,
            this.从ExcelToolStripMenuItem1,
            this.导入到数据库ToolStripMenuItem});
            this.导入导出ToolStripMenuItem1.Name = "导入导出ToolStripMenuItem1";
            this.导入导出ToolStripMenuItem1.Size = new System.Drawing.Size(65, 20);
            this.导入导出ToolStripMenuItem1.Text = "导入导出";
            // 
            // 导出ExcelToolStripMenuItem1
            // 
            this.导出ExcelToolStripMenuItem1.Name = "导出ExcelToolStripMenuItem1";
            this.导出ExcelToolStripMenuItem1.Size = new System.Drawing.Size(142, 22);
            this.导出ExcelToolStripMenuItem1.Text = "导出Excel";
            this.导出ExcelToolStripMenuItem1.Click += new System.EventHandler(this.导出ExcelToolStripMenuItem1_Click);
            // 
            // 从ExcelToolStripMenuItem1
            // 
            this.从ExcelToolStripMenuItem1.Name = "从ExcelToolStripMenuItem1";
            this.从ExcelToolStripMenuItem1.Size = new System.Drawing.Size(142, 22);
            this.从ExcelToolStripMenuItem1.Text = "从Excel导入";
            this.从ExcelToolStripMenuItem1.Click += new System.EventHandler(this.从ExcelToolStripMenuItem1_Click);
            // 
            // 导入到数据库ToolStripMenuItem
            // 
            this.导入到数据库ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.学生表ToolStripMenuItem,
            this.教师表ToolStripMenuItem,
            this.课程表ToolStripMenuItem,
            this.选课表ToolStripMenuItem});
            this.导入到数据库ToolStripMenuItem.Name = "导入到数据库ToolStripMenuItem";
            this.导入到数据库ToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.导入到数据库ToolStripMenuItem.Text = "导入到数据库";
            // 
            // 学生表ToolStripMenuItem
            // 
            this.学生表ToolStripMenuItem.Name = "学生表ToolStripMenuItem";
            this.学生表ToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.学生表ToolStripMenuItem.Text = "学生表";
            this.学生表ToolStripMenuItem.Click += new System.EventHandler(this.学生表ToolStripMenuItem_Click);
            // 
            // 教师表ToolStripMenuItem
            // 
            this.教师表ToolStripMenuItem.Name = "教师表ToolStripMenuItem";
            this.教师表ToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.教师表ToolStripMenuItem.Text = "教师表";
            this.教师表ToolStripMenuItem.Click += new System.EventHandler(this.教师表ToolStripMenuItem_Click);
            // 
            // 课程表ToolStripMenuItem
            // 
            this.课程表ToolStripMenuItem.Name = "课程表ToolStripMenuItem";
            this.课程表ToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.课程表ToolStripMenuItem.Text = "课程表";
            this.课程表ToolStripMenuItem.Click += new System.EventHandler(this.课程表ToolStripMenuItem_Click);
            // 
            // 选课表ToolStripMenuItem
            // 
            this.选课表ToolStripMenuItem.Name = "选课表ToolStripMenuItem";
            this.选课表ToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.选课表ToolStripMenuItem.Text = "选课表";
            this.选课表ToolStripMenuItem.Click += new System.EventHandler(this.选课表ToolStripMenuItem_Click);
            // 
            // 其它ToolStripMenuItem
            // 
            this.其它ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.注销登录ToolStripMenuItem});
            this.其它ToolStripMenuItem.Name = "其它ToolStripMenuItem";
            this.其它ToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
            this.其它ToolStripMenuItem.Text = "其它";
            // 
            // 注销登录ToolStripMenuItem
            // 
            this.注销登录ToolStripMenuItem.Name = "注销登录ToolStripMenuItem";
            this.注销登录ToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
            this.注销登录ToolStripMenuItem.Text = "注销登录";
            this.注销登录ToolStripMenuItem.Click += new System.EventHandler(this.注销登录ToolStripMenuItem_Click_1);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // formAdmBindingSource
            // 
            this.formAdmBindingSource.DataSource = typeof(学生成绩管理系统.FormAdm);
            // 
            // FormAdm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(612, 393);
            this.Controls.Add(this.statusBar1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormAdm";
            this.Text = "管理员";
            this.Load += new System.EventHandler(this.FormAdm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.formAdmBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private Sunisoft.IrisSkin.SkinEngine skinEngine1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.BindingSource formAdmBindingSource;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.StatusBar statusBar1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 学生项ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 显示学生信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 更新学生信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 教师项ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 课程项ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 显示教师信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 更新教师信息ToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem 导入导出ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 导出ExcelToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ToolStripMenuItem 导入导出ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 导出ExcelToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 从ExcelToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 显示所有课程ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 更新课程信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 更新成绩表格ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 查看学生成绩ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 其它ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 注销登录ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 导入到数据库ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 学生表ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 教师表ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 课程表ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 选课表ToolStripMenuItem;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}