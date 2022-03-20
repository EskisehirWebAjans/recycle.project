<?php

require_once 'Database.php';

class Stat {
    private $db;
    private $res = [];

    public function __construct() {
        $this->db = new Database;
    }

    public function getTotalRecyclesByType($type) {
        $sql = "SELECT *
                FROM student_recyclings r
                LEFT JOIN products p
                ON(r.item = p.id) 
                LEFT JOIN recycle_types t 
                ON(p.recycle_type = t.id)
                WHERE t.id = :type";
        $this->db->query($sql);
        $this->db->bind(':type', $type);
        $this->db->execute();
        $this->res['status'] = true;
        $this->res['info'] = 'Atık sayısı hesaplandı!';
        $this->res['total'] = $this->db->rowCount();
        return $this->res;
    }

    public function topList() {
        $sql = "SELECT s.name AS name, s.surname AS surname, s.number AS number, s.class AS class,
                SUM(t.reward) AS point 
                FROM students s
                LEFT JOIN student_recyclings r 
                ON(s.id = r.student) 
                LEFT JOIN products p 
                ON(r.item = p.id) 
                LEFT JOIN recycle_types t 
                ON(p.recycle_type = t.id)
                GROUP BY r.student
                HAVING point > 0 
                ORDER BY SUM(t.reward) DESC 
                LIMIT 10";
        $this->db->query($sql);
        $this->res['status'] = true;
        $this->res['info'] = 'Öğrenciler listelendi!';
        $this->res['students'] = $this->db->resultSet();
        return $this->res;
    }
}