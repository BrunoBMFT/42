#!/bin/bash
echo "CREATE DATABASE IF NOT EXISTS $DB_NAME;" > /etc/mysql/init.sql
echo "CREATE USER IF NOT EXISTS '$DB_USER'@'%' IDENTIFIED BY '$DB_PASSWORD';" >> /etc/mysql/init.sql
echo "GRANT ALL PRIVILEGES ON *.* TO '$DB_USER'@'%' WITH GRANT OPTION;" >> /etc/mysql/init.sql
echo "FLUSH PRIVILEGES;" >> /etc/mysql/init.sql
sleep 5
mysqld_safe --init-file="/etc/mysql/init.sql" &
sleep 10
mysql_upgrade -u root
mysqladmin -u root shutdown
exec mysqld
