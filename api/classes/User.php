
<?php
require_once 'Database.php';

class User {
    private $db;
    private $res = [];

    public function __construct() {
        $this->db = new Database;
    }

    public function getUsers() {
        $sql = "SELECT * FROM users ORDER BY id DESC";
        $this->db->query($sql);
        return $this->db->resultSet();
    }

    public function doLogin($user) {
        $sql = "SELECT * FROM users WHERE username = :username AND password = :password";
        $this->db->query($sql);
        $this->db->bind(':username', $user['username']);
        $this->db->bind(':password', $user['password']);
        $row = $this->db->single();
        if ($row) {
            $this->res['status'] = true;
            $this->res['info'] = 'Giriş başarılı!';
            $this->res['user'] = $row;
            $this->res['token'] = 'CfDJ8OW5OI0CPGJBgSNlGwO0x4YF7qbYKVv7KOO-N0eFtDUzXOrL7F9Xd9W1otVi4ueJOkAmAhuoHFWNkqRaFD7zvAMHMSKncl6Vo5QXKmpvy6vqxOKxSURdIey8aZPRi3Nnhp2p9la-Al5xrVKz0lignRdcCHf3O7pF9zv_sNx_c_T7pUe3WsxaJEPX3t_9FO2Wjw';
        } else {
            $this->res['status'] = false;
            $this->res['info'] = 'Giriş başarısız!';
            $this->res['user'] = $user;
        }
        return $this->res;
    }
}