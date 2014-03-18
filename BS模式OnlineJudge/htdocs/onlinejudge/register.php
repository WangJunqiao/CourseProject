<?php session_start(); ?>

<html>

<head>
	<title>Register Page</title>
	<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>
	<script type="text/javascript">
		function check(form){
			username=form.username.value;
			password=form.password.value;
			if( username=="" ){
				alert("empty username");
				return false;
			}
			if( password=="" ){
				alert("empty password");
				return false;
			}
			return true;
		}
	</script>
</head>

<body>
<br>
<br>
	<center><h1>User Register</h1></center>
	
<?php 
	for($i=0;$i<5;$i++) echo "<br>";
?>
	<center><form action="regresult.php" method="post" onsubmit="return check(this)">
		Username:<input type="text" name="username" value=""></input><br>
		Password:<input type="password" name="password" value=""></input><br>
		<input type="submit" name="submit" value="register now!"></input>
	</form></center>
	
</body>
</html>