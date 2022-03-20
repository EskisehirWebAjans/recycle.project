<?php
require_once 'Database.php';

class Student {
    private $db;
    private $res = [];

    public function __construct() {
        $this->db = new Database;
    }

    public function getStudents() {
        $sql = "SELECT * FROM students ORDER BY id DESC";
        $this->db->query($sql);
        return $this->db->resultSet();
    }

    public function getStudentByNumber($number) {
        $this->db->query('SELECT * FROM students WHERE number = :number');
        $this->db->bind(':number', $number);
        $row = $this->db->single();
        if ($row) {
            $this->res['status'] = true;
            $this->res['info'] = 'Student Listed!';
            $this->res['student'] = $row;
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Student not Found!';
            $this->res['student'] = $number;
        }
        return $this->res;
    }

    public function saveStudentRecycle($data) {
        $sql = "INSERT INTO student_recyclings (student, item) VALUES(:student, :item)";
        $this->db->query($sql);
        
        $this->db->bind(':student', $data['student']);
        $this->db->bind(':item', $data['product']);
        $result = $this->db->execute();

        if($result) {
            $this->res['status'] = true;
            $this->res['info'] = 'Recycle Saved!';
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Recycle not Saved!';
            $this->res['student'] = $data['student'];
            $this->res['product'] = $data['product'];
            $this->res['error'] = $result;
        }

        return $this->res;
    }

    public function listRecyclings() {
        $sql = "SELECT sr.id AS id, s.number AS number, s.class AS class, s.name AS name, s.surname AS surname, p.barcode AS barcode, p.title AS pTitle, r.title AS rTitle, r.reward AS reward, sr.inserted AS inserted 
                FROM student_recyclings sr 
                LEFT JOIN students s
                ON (sr.student = s.id) 
                LEFT JOIN products p 
                ON(sr.item = p.id) 
                LEFT JOIN recycle_types r 
                ON(p.recycle_type = r.id)
                ORDER BY sr.inserted DESC";
        $this->db->query($sql);
        return $this->db->resultSet();
    }

    public function deleteRecycling($recycling) {
        $sql = "DELETE FROM student_recyclings WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $recycling['id']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'İşlem silindi!';
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'İşlem silinemedi!';
            $this->res['recycling'] = $recycling;
        }
        return $this->res;
    }

    public function getStudentById($id) {
        $sql = "SELECT * FROM students WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $id);
        return $this->db->single();
    }

    public function addStudent($student) {
        $sql = "INSERT INTO students (id, name, surname, number, class) VALUES(NULL, :name, :surname, :number, :class)";
        $this->db->query($sql);
        $this->db->bind(':name', $student['name']);
        $this->db->bind(':surname', $student['surname']);
        $this->db->bind(':number', $student['number']);
        $this->db->bind(':class', $student['class']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Öğrenci eklendi!';
            $this->res['student'] = $this->getStudentById($this->db->getInsertId());
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Öğrenci eklenemedi!';
            $this->res['student'] = $student;
        }
        return $this->res;
    }

    public function updateStudent($student) {
        $sql = "UPDATE students SET name = :name, surname = :surname, number = :number, class = :class WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $student['id']);
        $this->db->bind(':name', $student['name']);
        $this->db->bind(':surname', $student['surname']);
        $this->db->bind(':number', $student['number']);
        $this->db->bind(':class', $student['class']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Öğrenci güncellendi!';
            $this->res['student'] = $this->getStudentById($student['id']);
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Öğrenci güncellenemedi!';
            $this->res['student'] = $student;
        }
        return $this->res;
    }

    public function deleteStudent($student) {
        $sql = "DELETE FROM students WHERE id = :id";
        $this->db->query($sql);
        $this->db->bind(':id', $student['id']);
        $this->db->execute();
        if($this->db->rowCount()) {
            $this->res['status'] = true;
            $this->res['info'] = 'Öğrenci silindi!';
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Öğrenci silinemedi!';
            $this->res['student'] = $student;
        }
        return $this->res;
    }
}