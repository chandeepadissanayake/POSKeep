# POSKeep

# Compilation Instructions for Debian Based Distributions of Linux

  1. Clone the repository.
  2. You should have MySQL Database Server and C libraries for MySQL installed. Execute the following commands to get them installed.
      ```
        sudo apt-get install mysql-server -y
        sudo apt-get install libmysqlclient-dev libssl-dev
      ```
  3. Create a database with the name "db_poskeep" and use (source) the file db_poskeep.sql provided in the root of the repository folder to create the necessary tables. You may use the following commands in order for this purpose.
      ```
        cd /path/to/the/cloned/repository
        mysql -u username -p
        mysql> create database db_poskeep
        mysql> use db_poskeep
        mysql> source db_poskeep.sql
        mysql> exit
      ```
  4. Change the required fields in the src/config/db.h to suit your MySQL Server Credentials.
  5. In the same terminal opened above, run the following command to compile the project and run POSKeep.
      ```
        ([ ! -d "bin" ] && mkdir bin); gcc -Isrc src/cmdimpl/poskeepexit.c -Isrc src/cmdimpl/poskeepinvexport.c src/cmdimpl/poskeepinvsearch.c src/cmdimpl/poskeeptransactions.c src/db/connection.c src/model/modelcommands.c src/utils/mdarrutils.c src/utils/strutils.c src/commands.c src/databases.c src/main.c src/welcome.c -o "bin/poskeep" `mysql_config --cflags --libs`; bin/poskeep;
      ```

