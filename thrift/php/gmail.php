<?php
$ch = curl_init();

$data = array('fb_id' => "1120637269",
              'uid' => 0,
              'access_token' => 'D');              
curl_setopt($ch, CURLOPT_URL, 'http://cp.reko.me/app/api/gmail/sync.php?email=fguo@orbe.us&access_token=ya29.LgBvIbx8ADnYCBoAAAB0evFfwtIHKNWK--QyUTE8O2Moavu5nofqnp5pZOVvVw');
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
$resp = curl_exec($ch);
echo $resp;
?>
