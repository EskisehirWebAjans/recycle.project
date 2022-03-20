<?php
    $result = array();
    header('Cache-Control: no-cache');
    header('Content-type: application/json');

    require_once 'inc/config.php';   
    require_once 'classes/User.php';
    require_once 'inc/cors.inc.php';
    cors();
    $user = new User;

    if($_SERVER['REQUEST_METHOD'] == 'POST') {
        $post = json_decode(file_get_contents('php://input'), true);
        $result = $user->doLogin($post);
    } else {
        $result['status'] = false;
        $result['info'] = 'Veri hatası!';
        $result['post'] = $_POST;
    }
    
    echo json_encode($result);

