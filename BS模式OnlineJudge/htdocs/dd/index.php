<html>

<!-- 这是一个注释! head是浏览器的标签标题,不会在网页版面上显示 -->
<head>
<title>ZJUT ACM</title>

<style type="text/css">
	h1 {color:red}
	p {color:blue}
</style>

</head>

<body>
<center>
<h1>ZJUT ACM OnlineJudge <sub>tm</sub> <sup> top</sup></h1>
</center>

<hr align="center" width="80%" color="red"> <!-- 一条横线 -->

<a href="mysqlTest.php">mysqlTest</a> <br>
<a href="javascriptTest.php">javascriptTest</a> <br>

<center>
<form action="login.php" method="post">
	<input type="text" name="username" value="dd">
	<input type="password" name="userpass" value="123456">
	<input type="submit" value="login">
</form>  </center>

<a href="frameTest.php">frameTest</a>


<pre>   预设格式标记pre,    哈哈
                 换行了之后还是可以的哦,威力无穷!!
</pre>

<?php
/*
	$pipe=fopen("\\\\.\\pipe\\samplenamedpipe", "w");
	if( !$pipe ){
		die("die");
	}
	fwrite($pipe, "hello kitty!!");
	fclose($pipe);
	*/
	$pipe=fopen("\\\\.\\pipe\\samplenamedpipe", "r");
	if( !$pipe ){
		die("die");
	}
	fgets($pipe,$response);
	echo $response."<br>";
	fclose($pipe);

	//$t=@shell_exec("D:/Notepad++/BC9.exe");
	//echo $t."  ffffffffffffffffff<br>";
	
echo 'Today is '.date("Y-m-d");
echo "<br />";
//$tomorrow=mktime(0,0,0,date("m"),date("d")+1,date("Y"));
$tomorrow = mktime(0,0,0,date("m"),date("d")+1,date("Y"));
echo "Tomorrow is ".date("Y-m-d",$tomorrow);
echo "<br><br><br><br>"
?>

<center><a href="acmTemp/dinic.txt">最大流dinic模板</a></center>
<a href="picture/picIndex.html"> 福州图片</a>

<br>
<br>

<center>
<p style="color: #800">随意上传一个文件,小于20M哦</p>
</center>

<form action="upload_file.php" method="post"
	enctype="multipart/form-data"><label for="file">Filename:</label> <input
	type="file" name="userfile" id="file" /> <input type="submit" name="submit"
	value="点击上传文件" /></form>

<form action="mailto:zjut_DD@163.com" method="post">name: <input
	type="text" name="name"> <input type="submit" value="ddd"></form>

<br>
where are come from?
<select name="where">
<option value="HK">HongKong</option>
<option value="USA">United States</option>
<option value="RU">Russia</option>
</select> <br>

<br>
<br>
Give your comments:<br>
<textarea name="comments" rows="4" cols="40"></textarea>
<br>
<?php include("hello1000.php");?>


<marquee  behavior=alternate>撞来撞去，啊！我昏啦</marquee>




注意以下几点:<br>
<ol> <!-- ordered list 有序列表-->
<li>不要迟到</li>  <!-- list item 列表项-->
<li>不要早退</li>
<li>不要说话</li>
</ol>

注意以下几点:<br>
<ul> <!-- unordered list 无序列表-->
<li>不要迟到</li> 
<li>不要早退</li>
<li>不要说话</li>
</ul>
<br>



<b>字体加粗</b>  <!-- bold -->
<i>斜体字</i>  <!-- inclined倾斜的 -->
<u>下划线</u>  <!-- underline -->
<strike>删除线</strike>

<table width="60%" border="2" align="center">
	<tr align="center" bgcolor="red">
		<td>(1,1)</td>
		<td>(1,2)</td>
	</tr>
	<tr bgcolor="white">
		<td><b><strike>(2,1)</strike></b></td>
		<td bgcolor="gray">(2,2)</td>
	</tr>
	<tr bgcolor="yellow">
		<td>(3,1)</td>
		<td>(3,2)</td>
	</tr>
</table>

<img alt="this is daodao's head portrait" src="upload/gg.jpg" width=120 height=120>

<pre>
struct LinkedList{
	struct Node{ T val; Node *p, *x, *ps, *xs; }dd[MAXN],*head; //pre next  pre_seg  next_seg
	int e, size;
	LinkedList(){ clear(); }
	void clear(){ size=e=0; }
};
int main(){
	printf("hello world!\n";
}
</pre>

</body>
</html>
