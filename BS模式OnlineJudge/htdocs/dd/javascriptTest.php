<html>

<head>
<title>javascript Test</title>

<script type="text/javascript">
		function showmessage(){
			alert("showmessage function: xixi");
		}

		function setCookie(c_name,value,expiredays) {
			var exdate=new Date();
			exdate.setDate(exdate.getDate()+expiredays);
			document.cookie=c_name+ "=" +escape(value)+
				((expiredays==null) ? "" : ";expires="+exdate.toGMTString());
		}
		function getCookie(c_name){
			if (document.cookie.length>0){
		  		c_start=document.cookie.indexOf(c_name + "=");
		  		if (c_start!=-1) { 
		    		c_start=c_start + c_name.length+1 ;
		    		c_end=document.cookie.indexOf(";",c_start);
		    		if (c_end==-1) c_end=document.cookie.length;
		    		return unescape(document.cookie.substring(c_start,c_end));
		    	} 
		  	}
			return "";
		}
		function checkCookie(){
			username=getCookie('username');
			if (username!=null && username!=""){
			  	alert('Welcome again '+username+'!');
			} else {
		  		username=prompt('Please enter your name:',"");
		  		if (username!=null && username!="") {
		    		setCookie('username',username,365);
		    	}
		  	}
		}

		function change1(){
			document.b1.src="upload/1.jpg";
		}
		function change2(){
			document.b1.src="upload/2.jpg";
		}

		var clock;
		function countTime(){
			date=new Date();
			document.getElementById("current-time").innerHTML="<center><p color=\"red\">当前时间: "+date.getHours()+":" 
				+ date.getMinutes() + ":"+ date.getSeconds() + "</p></center>";
			clock=setTimeout("countTime()", 1000);
		}
	</script>
</head>


<body onload="checkCookie();countTime();">

<script type="text/javascript">
	document.write("hello world!<br>");

	browser=navigator.appName;
	version=navigator.appVersion;
	//version=parseFloat(b_version)
	document.writeln(browser+"<br>");
	document.writeln(version+"<br>");
	try{
		for(i=1;i<=5;i++) document.write("43553525<br>");
		//adddlert("Welcome guest!");
		//throw("fuck");
	}catch(err){
		alert("网页有错误!\n\n"+err);
	}
	//alert("haha");
	//confirm("xixi");
	
	
</script>

<div id="current-time"></div>



<img alt="this is a picture!" src="upload/1.jpg" 
	width="100" height="100"
	name="b1" onmouseover="change2()" onmouseout="change1()">


</body>

</html>
