#!/bin/bash
# Скрипт логирования действий оператора в ОС

# logged_user=$(who | grep :0 | awk '{print $1}')

while true; do
   cur_time=$(date +%s) # текущая дата
   let "last_time=$(date +%s) - 60" # дата на N минтут раньше текущей
   cur_date=$(date --date=@$cur_time +%y%m%d%H%M%S) # смена формата времени
   last_date=$(date --date=@$last_time +%y%m%d%H%M%S)
   # Форматированное чтение бинарного лога. Фильтры: %N, %t %A %u, описаны в man parselog в разделе флага -o
   #output=$(parselog /var/log/parsec/kernel.mlog -t $last_date-$cur_date -o '%N %t %A %u %s &' | egrep -w 'chmod|rmdir|create|chown|setacl')
   #parse=1
 

   
   echo "22222222222222222222222222"
   
   while read line; 
   do
      #if [[ $(expr length "$output") > 1  &&  "$output" == *"&"* ]];then
      #str=${output:0:$(expr index "$output" "&")}
      str=$line
      #output=${output:$(expr index "$output" "&")}

      # Парсинг захваченной строки
      util=${str:0:$(expr index "$str" " ")} # Название вызванной утилиты
      str=${str:$(expr index "$str" " ")}
      
      if [[ $(date +"%Y-%m-%d") == $(date --date="${str:0:$(expr index "$str" "\(")}" +"%Y-%m-%d") ]] 
      then
      #    log_str=$(date --date="${str:0:$(expr index "$str" "\(")}" +"%Y-%m-%d_%H:%M:%S|Администратор КТСКУ|Пользователь ") # Форматированная запись времени в конечную строку (пока только дата)
         log_str="|Администратор КТСКУ|Пользователь " # Форматированная запись времени в конечную строку (пока только дата)
         str=${str:$(expr index "$str" "\(")}
         user=${str:$(expr index "$str" "\)")+1} # Здесь по итогу будет хранится имя пользователя, выполнившего дейтсиве в ОС
         args=${str:0:$(expr index "$str" "\)")-1} # Аргументы, используемые при выполнении команды
         str=${str:$(expr index "$str" "\)")+1}
         user=${user:0:$(expr index "$user" " ")}
         user=$(grep $user /etc/passwd)
         user=${user:0:$(expr index "$user" ":")-1}
         str=${str:$(expr index "$str" " ")}
         str=${str:0:$(expr index "$str" " ")}
         
         if [[ "$user" != "drweb"  ]]
         then
           
            
            if [[ "$user" != "root" && "$util" != "create" ]]
            then
                echo "33333 user = "$user
                echo "33333 util = "$util
            
               log_str="nsd&"$log_str$user" выполнил команду "$util" со следующими аргументами "$args
               log_str=$(echo $log_str | tr -s '\n' ' ' | tr -s '\r' ' ')
            #    echo $log_str >> /var/log/ktsku/nsd/journal_$(date +%y%m%d.log)
            
            echo "33333 log_str = "$log_str
               nping --udp 127.0.0.1 -p 48053 -c 1 --data-string "${log_str}" > /dev/null 2>&1
            fi 
         fi
      fi
      #else
      #  parse=0
      #fi
   done < <(parselog /var/log/parsec/kernel.mlog -t $last_date-$cur_date -o '%N %t %A %u %s &' | egrep -w 'chmod|rmdir|create|chown|setacl')
   
   sleep 60
done
