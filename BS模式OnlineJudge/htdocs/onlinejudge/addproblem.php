<html>

<head>
	<title>Add Problem</title>
	<link rel="stylesheet" type="text/css" href="globalstyle.css"></link>

	<script>
		function check(form){
			var reg=new RegExp("^[0-9]+$");
			if( !reg.test(form.timelimit.value) || form.timelimit.value.length>9){
				alert("TimeLimit must be non negtive integer and less than 10^9!");
				form.timelimit.focus();
				return false;
			}
			if( !reg.test(form.memorylimit.value) || form.memorylimit.value.length>9){
				alert("MemoryLimit must be non negtive integer and less than 10^9!");
				form.memorylimit.focus();
				return false;
			}	
		}
	</script>
</head>


<body>



<form action="submit-problem.php" method="post" onsubmit="return check(this);"
	enctype="multipart/form-data">



<center>Problem&nbsp;Title: <textarea name="title" rows="1" cols="50"></textarea> </center>
<center>
	TimeLimit:<input type="text" name="timelimit" value="1000"></input> ms &nbsp; &nbsp;&nbsp;
	MemoryLimit: <input type="text" name="memorylimit" value="32768"></input> kb
</center>

<input type="checkbox" name="htmlformmat" value="htmlformmat">htmlformmat <br>
Description:<br>
<textarea name="description" rows="15" cols="150"></textarea> <br>

Input:<br>
<textarea name="input" rows="3" cols="150"></textarea> <br>

Output:<br>
<textarea name="output" rows="3" cols="150"></textarea> <br>

SampleInput:<br>
<textarea name="sampleinput" rows="4" cols="150"></textarea> <br>

SampleOutput:<br>
<textarea name="sampleoutput" rows="4" cols="150"></textarea> <br>


Hint:<br>
<textarea name="hint" rows="2" cols="150"></textarea> <br>

Input file: <input type="file" name="inputfile"></input>
Output file <input type="file" name="outputfile"></input> <br>

Author:<input type="text" name="author" value=""></input> <br>

<input type="submit" name="submit" value="submit"></input>
</form>



</body>

</html>