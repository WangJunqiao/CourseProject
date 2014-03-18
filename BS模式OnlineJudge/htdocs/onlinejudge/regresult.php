<?php session_start(); ?>

<html>
<head>
	<title>Register Result Page</title>
	<link rel="stylesheet" type="text/css" href="globalstyle.css">
</head>


<body>

<?php 
	for($i=0;$i<5;$i++) echo "<br>\n";
	function insertUser($username,$password){
		$con=mysql_connect("127.0.0.1","ojadmin","ojadmin123456") or die("failed to connect mysql!");
		if( !$con ){
			echo "failed to connect to mysql!<br>";
		}
		mysql_select_db("onlinejudgedb");
		$str="select * from userinfo where username='".$username."';";
		$result=mysql_query($str);

		if( mysql_num_rows($result)!=0 ){
			return "no"; //用户名已存在!
		}
		$str="insert into userinfo values ('".$username."','".$password."');";
		$result=mysql_query($str);
		return "yes";
	}
	$username=$_POST['username'];
	$password=$_POST['password'];
	$ret=insertUser($username, $password);
	if( $ret=="no" ){
		echo "<center><h2 class=\"redtext\">Register failed! Username has already exsit!"
			."</h2></center>"; 
	}else{
		echo "<center><h2 class=\"redtext\">Register Successfully!"
			."</h2></center>"; 
	}
?>

</body>

</html>