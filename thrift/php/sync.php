<?php
include_once "../config.php";
include_once "master.php";

$ip="192.168.1.148";
$port=28999;
$ret = array();

if (isset($_GET['email']) && isset($_GET['access_token'])) {
  $email = $_GET['email'];
  $access_token = $_GET['access_token'];
  SendGmailAnalysisRequest ($ip, $port, $email, $access_token);
  $ret['status']=true;
}
else {
  $ret['status']=false;
  $ret['message']="Insufficient parameters!";
}
echo json_encode($ret);
