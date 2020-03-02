<?php
$servername="localhost";
$username="root";
$password="";
$dbname="sign_up";

$name=$_POST['name'];
$email=$_POST['email'];
$pwd=$_POST['password'];
$conn=new mysqli($servername,$username,$password,$dbname);
if($conn->connect_error)
{
die("CONNECTION FAILED".$conn->connect_error);
}
$sql="INSERT INTO signup(name,email,password)values('$name','$email','$pwd')";

if($conn->query($sql)==true)
{
print("REGISTRATION SUCCESSFUL");
}
?>