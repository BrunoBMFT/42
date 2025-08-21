#!/bin/bash
cd /var/www/html
curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
chmod +x wp-cli.phar
sleep 5

if [ ! -f wp-load.php ]; then
	./wp-cli.phar core download --allow-root
fi

if [ ! -f wp-config.php ]; then
	./wp-cli.phar config create \
	--dbname=${DB_NAME} \
	--dbuser=${DB_USER} \
	--dbpass=${DB_PASSWORD} \
	--dbhost=${DB_HOST} \
	--allow-root
fi

if ! ./wp-cli.phar core is-installed --allow-root ; then
	./wp-cli.phar core install \
	--url=${WP_DOMAIN} \
	--title=${WP_TITLE} \
	--admin_user=${WP_ADMIN_USER} \
	--admin_password=${WP_ADMIN_PASSWORD} \
	--admin_email=${WP_ADMIN_EMAIL} \
	--allow-root
fi

if ! ./wp-cli.phar user get ${WP_GUEST_USER} --allow-root > /dev/null 2>&1 ; then
	./wp-cli.phar user create \
	${WP_GUEST_USER} \
	${WP_GUEST_EMAIL} \
	--role=subscriber \
	--user_pass=${WP_GUEST_PASSWORD} \
	--allow-root
fi
php-fpm8.2 -F
