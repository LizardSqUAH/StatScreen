sudo apt-get install libmysqlclient-dev

Finally some separation of credentials, no longer will I look stupid for putting a password in my git. Now I am free to find other ways to look stupid :D.

##Make a file in the same directory as stat_screen named credentials.txt. Inside write the following
IPAddress
Port
User
Pass
##

IPAddress will be of the mariadb server
Port will be the mariadb port (probably 3306)
User will be the username of an account that has access to the TextGuiDB database and its tables
Pass will be the password for that account
