
<?php session_start(); ?>

<html>

<head>
	<title>User Login</title>
	<script type="text/javascript">
		function checkform(form){
			if( form.username.value=="" ){
				alert("empty username!");
				return false;
			}
			if( form.password.value=="" ){
				alert("empty password!");
				return false;
			}
			return true;
		}
	</script>
	
	<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>
</head>

<body>

<br>
<br>
<center><h2>User Login</h2></center>
<?php 
	for($i=0;$i<5;$i++) echo "</br>";
?>

<?php 
	function check($username,$password){

		$con=mysql_connect("127.0.0.1","ojadmin","ojadmin123456") or die("failed to connect mysql!");
		if( !$con ){
			echo "failed to connect to mysql!<br>";
		}
		mysql_select_db("onlinejudgedb");
		$str="select password from userinfo where username='".$username."';";
		$result=mysql_query($str);

		if( mysql_num_rows($result)==0 ){
			return "false";
		}
		$arr=mysql_fetch_array($result);
		if( $arr[0]!=$password ) {
			return "false";
		}
		return "true";
	}
	if( $_GET['action']=="login" ){
		$username=$_POST['username'];
		$password=$_POST['password'];
		
		$ret=check($username, $password);
		if( $ret=="false" ){
			echo "<center><b><h3 class=\"redtext\">"
				."Wrong Username and Password Combination!</h3></b></center>";
		}else{
			//echo "login successfully! <br>";
			//header("location: manage.php");
			$_SESSION['login_success']=1;
			$_SESSION['username']=$username;
			header("location: index.php");
		}
	}
?>

<center><form action="login.php?action=login" method="post" onsubmit="return checkform(this);">
	Username:<input type="text" name="username" value=""></input> <br>
	Password:<input type="password" name="password" value=""></input> <br>
	<input type="submit" name="submit" value="login"></input>
</form> </center>


</body>

</html>