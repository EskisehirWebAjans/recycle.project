<?php
    $result = array();
    header('Cache-Control: no-cache');
    header('Content-type: application/json');

    require_once 'inc/config.php';   
    require_once 'classes/Student.php';
    require_once 'inc/cors.inc.php';
    cors();

    $student = new Student;
    // $post = json_decode($_POST['data'], true);

    $result = $student->getStudents();
    echo json_encode($result);

