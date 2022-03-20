<?php
    $result = array();
    header('Cache-Control: no-cache');
    header('Content-type: application/json');

    require_once 'inc/config.php';   
    require_once 'classes/Stat.php';
    require_once 'inc/cors.inc.php';
    cors();

    $stat = new Stat;
    // $post = json_decode($_POST['data'], true);
    
    $result = $stat->topList();
    echo json_encode($result);

