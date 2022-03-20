<?php
    $result = array();
    header('Cache-Control: no-cache');
    header('Content-type: application/json');

    require_once 'inc/config.php';   
    require_once 'classes/Student.php';
    require_once 'inc/cors.inc.php';
    cors();
    $student = new Student;

    if($_SERVER['REQUEST_METHOD'] == 'POST') {
        $post = json_decode(file_get_contents('php://input'), true);
        $result = $student->deleteRecycling($post);
    } else {
        $result['status'] = false;
        $result['info'] = 'Veri hatası!';
        $result['post'] = $_POST;
    }
    
    echo json_encode($result);

