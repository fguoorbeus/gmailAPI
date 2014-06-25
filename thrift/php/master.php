<?php

function SendGmailAnalysisRequest ($ip, $port, $email, $access_token) {
  try {
    $GLOBALS['THRIFT_ROOT'] = '/home/orbeus/Downloads/thrift-0.8.0/lib/php/src';
    require_once( $GLOBALS['THRIFT_ROOT'].'/Thrift.php' );
    require_once( $GLOBALS['THRIFT_ROOT'].'/transport/TSocket.php' );
    require_once( $GLOBALS['THRIFT_ROOT'].'/transport/TFramedTransport.php' );
    require_once( $GLOBALS['THRIFT_ROOT'].'/protocol/TBinaryProtocol.php' );
    require_once( $GLOBALS['THRIFT_ROOT'].'/packages/gmail/GmailService.php' );

    $socket = new TSocket( $ip, $port );
    $socket->setSendTimeout( 10000 ); // Ten seconds (too long for production, but this is just a demo ;)
    $socket->setRecvTimeout( 20000 ); // Twenty seconds
    
    $transport = new TFramedTransport( $socket );
    $protocol = new TBinaryProtocol( $transport );
    $client = new GmailServiceClient( $protocol );
    $transport->open();

    $req = new GmailRequest();
    $req->email = $email;
    $req->access_token = $access_token;

    $client->analyze($req);

    $transport->close();
    $socket->close();
  }
  catch (Exception $e) {
    echo $e->getMessage()."<br>";
    return false;
  }
  return true;
}
